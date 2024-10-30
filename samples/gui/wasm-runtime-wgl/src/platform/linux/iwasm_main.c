

#ifndef CONNECTION_UART
#include <arpa/inet.h>
#include <netdb.h>
#include <netinet/in.h>
#include <sys/socket.h>
#else
#include <termios.h>
#endif

#include <arpa/inet.h>
#include <fcntl.h>
#include <getopt.h>
#include <pthread.h>
#include <signal.h>
#include <stdlib.h>
#include <strings.h>
#include <sys/types.h>
#include <unistd.h>

#include "app_manager_export.h"
#include "bh_platform.h"
#include "bi-inc/attr_container.h"
#include "module_wasm_app.h"
#include "native_interface.h"
#include "runtime_lib.h"
#include "runtime_sensor.h"
#include "runtime_timer.h"
#include "wasm_export.h"
#include "wgl.h"

#include "lv_drivers/display/monitor.h"
#include "lv_drivers/indev/mouse.h"
#define MAX 2048

#ifndef CONNECTION_UART
#define SA struct sockaddr
static char *host_address = "127.0.0.1";
static int port = 8888;
#else
static char *uart_device = "/dev/ttyS2";
static int baudrate = B115200;
#endif

#include <dlfcn.h>

// this 001 #################################################################

// typedef struct
// {
//   const char *name;
//   const char *signature;
// } func_info;

const char *funcinfo_filename = NULL; // 허용할 함수의 정보가 담긴 파일이름, 경로
func_info *infos = NULL;              // 허용하고자 하는 함수의 정보가 담긴 구조체
int func_count = 1;                   // 허용하고자 하는 함수의 총 개수
bool load_import_func = false;

void wasm_add_func_info(func_info *infos, int func_count);

const char *native_lib_list[8] = {NULL};
uint32 native_lib_count = 0;
struct native_lib *native_lib_loaded_list[8];
uint32 native_lib_loaded_count = 0;

// 파일에서 func_info를 읽어오는 함수
func_info *read_func_info(const char *filename, int *count)
{
  FILE *file = fopen(filename, "r");
  if (!file)
  {
    perror("파일 열기 실패");
    return NULL;
  }

  char line[256];
  int capacity = 10; // 초기 용량
  *count = 0;
  infos = malloc(capacity * sizeof(func_info));
  if (!infos)
  {
    perror("메모리 할당 실패");
    fclose(file);
    return NULL;
  }

  while (fgets(line, sizeof(line), file))
  {
    // 줄에서 함수 이름과 시그니처 파싱
    char name[128];
    char signature[128];
    if (sscanf(line, "%s %s", name, signature) != 2)
    {
      printf("잘못된 형식의 데이터 건너뜀: %s", line);
      continue; // 잘못된 데이터는 건너뜀
    }

    // 배열의 용량이 부족하면 확장
    if (*count >= capacity)
    {
      capacity *= 2;
      func_info *temp = realloc(infos, capacity * sizeof(func_info));
      if (!temp)
      {
        perror("메모리 재할당 실패");
        free(infos);
        fclose(file);
        return NULL;
      }
      infos = temp;
    }

    // 동적 메모리에 문자열 저장
    infos[*count].name = strdup(name);
    infos[*count].signature = strdup(signature);
    if (!infos[*count].name || !infos[*count].signature)
    {
      perror("문자열 복제 실패");
      // 메모리 해제
      for (int i = 0; i < *count; i++)
      {
        free((void *)infos[i].name);
        free((void *)infos[i].signature);
      }
      free(infos);
      fclose(file);
      return NULL;
    }

    (*count)++;
  }

  fclose(file);
  return infos;
}

NativeSymbol *native_symbols_my = NULL;
// NativeSymbol native_symbols_my[3] = {
//     // REG_NATIVE_FUNC_my(add, "(ii)i"),
//     // REG_NATIVE_FUNC_my(func222, "(ii)i"),
// };

uint32_t get_native_lib_my(char **p_module_name,
                           NativeSymbol **p_native_symbols)
{

  // 이건 전역으로 선언해서, 입력으로 func_info = ./func_info.txt 로 주어졌을 때
  //                파일명 받을 수 있도록 하기
  // const char *filename = "./func_info.txt";

  infos = read_func_info(funcinfo_filename, &func_count);

  // native_symbols_my 동적으로 할당
  native_symbols_my = (NativeSymbol *)malloc(func_count * sizeof(NativeSymbol));

  // 허용하고자 하는 함수의 개수만큼, infos 구조체에 정보를 추가
  for (int i = 0; i < func_count; i++)
  {
    printf("func_info[%d].name : %s", i, infos[i].name);
    printf("  func_info[%d].signature : %s\n", i, infos[i].signature);
  }

  void *shared_library_handle = NULL;

  // 여기서 argv의 값을 확인하고 so를 반복해서 열고 함수 포인터를 가져오기

  for (int i = 0; i < native_lib_count; i++)
  {
    printf("%s 열기 시도 -> ", native_lib_list[i]);

    // shared_library_handle = dlopen("./libexample.so", RTLD_NOW | RTLD_GLOBAL);
    shared_library_handle = dlopen(native_lib_list[i], RTLD_NOW | RTLD_GLOBAL);

    if (!shared_library_handle)
    {

      fprintf(stderr, "공유 라이브러리 로드 실패: %s\n", dlerror());
      // 메모리 해제
    }
    else
    {
      printf("성공적으로 %s 열림\n", native_lib_list[i]);
    }

    // 함수 포인터 가져오기 및 native_symbols_my 배열 채우기
    for (int j = 0; j < func_count; j++)
    {
      void *func_ptr = dlsym(shared_library_handle, infos[j].name);

      char *error = dlerror();
      if (error != NULL)
      {
        // native_symbols_my[i].symbol = infos[i].name;
        // native_symbols_my[i].func_ptr = NULL;
        // native_symbols_my[i].signature = infos[i].signature;
        continue;
      }
      printf("           라이브러리에서 추가된 함수 %s\n", infos[j].name);
      native_symbols_my[j].symbol = infos[j].name;
      native_symbols_my[j].func_ptr = func_ptr;
      native_symbols_my[j].signature = infos[j].signature;
    }
    printf("\n");
  }

  // 결과 출력
  printf("native_symbols_my 배열 내용:\n");
  for (int i = 0; i < func_count; i++)
  {
    if (native_symbols_my[i].symbol == NULL)
      continue;

    printf("Symbol: %s, Func Ptr: %p, Signature: %s\n",
           native_symbols_my[i].symbol,
           native_symbols_my[i].func_ptr,
           native_symbols_my[i].signature);
  }
  printf("\n");

  // printf("%s sssssssssssssssssss\n", native_symbols_my);

  *p_module_name = "env";
  *p_native_symbols = native_symbols_my;

  // printf("%d ggggggggggggggggggggg\n", sizeof(native_symbols_my) / sizeof(NativeSymbol));
  // 총 개수를 반환
  // return sizeof(native_symbols_my) / sizeof(NativeSymbol);
  return func_count;
}

// this 001 #################################################################

#if BH_HAS_DLFCN
struct native_lib
{

  bool is_extend;

  void *handle;

  uint32 (*get_native_lib)(char **p_module_name,
                           NativeSymbol **p_native_symbols);
  int (*init_native_lib)(void);
  void (*deinit_native_lib)(void);

  char *module_name;
  NativeSymbol *native_symbols;
  uint32 n_native_symbols;
};

struct native_lib *load_native_lib(const char *name)
{
  struct native_lib *lib = wasm_runtime_malloc(sizeof(*lib));
  if (lib == NULL)
  {
    LOG_WARNING("warning: failed to load native library %s because of "
                "allocation failure",
                name);
    goto fail;
  }
  memset(lib, 0, sizeof(*lib));

  printf(" native lib: %s\n", name);

  /* open the native library */
  if (!(lib->handle = dlopen(name, RTLD_NOW | RTLD_GLOBAL)) &&
      !(lib->handle = dlopen(name, RTLD_LAZY)))
  {
    LOG_WARNING("warning: failed to load native library %s. %s", name,
                dlerror());
    goto fail;
  }

  // 함수 포인터 가져옴
  lib->init_native_lib = dlsym(lib->handle, "init_native_lib");
  lib->get_native_lib = dlsym(lib->handle, "get_native_lib");
  lib->deinit_native_lib = dlsym(lib->handle, "deinit_native_lib");

  // get_native_lib로 받은 것이 아닐 때(유저 함수일 때)
  if (!lib->get_native_lib)
  {

    // lib->get_native_lib2 = dlsym(lib->handle, "add");
    // lib->get_native_lib2 = dlsym(lib->handle, "func222");
    // // 이 부분을 파일로
    // NativeSymbol native_symbols[] = {
    // REG_NATIVE_FUNC(add, "(ii)i"),
    // REG_NATIVE_FUNC(func222, "(ii)i"),
    //                                     };
    // lib->module_name = "env";
    // lib->native_symbols = native_symbols;
    // lib->n_native_symbols = 2;

    // 여기서 dlsym으로 get_native_lib_my를 사용하는 것이 아니라
    //  module_name, native_symbols 값을 받아서 사용해야 함

    // typedef int (*FunctionPointer)(int **, NativeSymbol **);
    // FunctionPointer fp = &get_native_lib_my;
    // uint32_t result = fp(p_module_name, p_native_symbols);

    // wasm_exec_env_t exec_env = 0;
    if (load_import_func == false)
    {
      // printf(" ddddddddddddddd   this is start \n");
      lib->get_native_lib = &get_native_lib_my;
      load_import_func = true;
      // printf(" ddddddddddddddd   this is ennnnnnnndd \n");
    }
  }

  if (!lib->get_native_lib)
  {
    LOG_WARNING("warning: failed to lookup `get_native_lib` function "
                "from native lib %s",
                name);
    goto fail;
  }

  if (lib->init_native_lib)
  {
    int ret = lib->init_native_lib();
    if (ret != 0)
    {
      LOG_WARNING("warning: `init_native_lib` function from native "
                  "lib %s failed with %d",
                  name, ret);
      goto fail;
    }
  }

  lib->n_native_symbols =
      lib->get_native_lib(&lib->module_name, &lib->native_symbols);

  /* register native symbols */
  if (!(lib->n_native_symbols > 0 && lib->module_name && lib->native_symbols &&
        wasm_runtime_register_natives(lib->module_name, lib->native_symbols,
                                      lib->n_native_symbols)))
  {
    LOG_WARNING("warning: failed to register native lib %s", name);
    if (lib->deinit_native_lib)
    {
      lib->deinit_native_lib();
    }

    goto fail;
  }

  return lib;
fail:
  if (lib != NULL)
  {
    if (lib->handle != NULL)
    {
      dlclose(lib->handle);
    }
    wasm_runtime_free(lib);
  }
  return NULL;
}

static uint32
load_and_register_native_libs(const char **native_lib_list,
                              uint32 native_lib_count,
                              struct native_lib **native_lib_loaded_list)
{
  uint32 i, native_lib_loaded_count = 0;

  for (i = 0; i < native_lib_count; i++)
  {
    struct native_lib *lib = load_native_lib(native_lib_list[i]);
    if (lib == NULL)
    {
      continue;
    }
    native_lib_loaded_list[native_lib_loaded_count++] = lib;
  }

  for (int i = 0; i < native_lib_loaded_count; i++)
  {
    printf("native_lib_loaded_list[%d] : %s\n", i,
           native_lib_loaded_list[i]->module_name);

    for (int j = 0; j < native_lib_loaded_list[i]->n_native_symbols; j++)
    {
      printf("    loaded_func_list[%d] : %s\n", i,
             native_lib_loaded_list[i]->native_symbols[j].symbol);
    }
    printf("\n");
  }

  return native_lib_loaded_count;
}

static void
unregister_and_unload_native_libs(uint32 native_lib_count,
                                  struct native_lib **native_lib_loaded_list)
{
  uint32 i;

  for (i = 0; i < native_lib_count; i++)
  {
    struct native_lib *lib = native_lib_loaded_list[i];

    /* unregister native symbols */
    if (!wasm_runtime_unregister_natives(lib->module_name,
                                         lib->native_symbols))
    {
      LOG_WARNING("warning: failed to unregister native lib %p", lib->handle);
      continue;
    }

    if (lib->deinit_native_lib)
    {
      lib->deinit_native_lib();
    }

    dlclose(lib->handle);
    wasm_runtime_free(lib);
  }
}
#endif /* BH_HAS_DLFCN */

// this 001 #################################################################
// this 001 #################################################################

extern bool init_sensor_framework();
extern void exit_sensor_framework();
extern void exit_connection_framework();
extern int aee_host_msg_callback(void *msg, uint32_t msg_len);
extern bool init_connection_framework();

#ifndef CONNECTION_UART
int listenfd = -1;
int sockfd = -1;
static pthread_mutex_t sock_lock = PTHREAD_MUTEX_INITIALIZER;
#else
int uartfd = -1;
#endif

#ifndef CONNECTION_UART
static bool server_mode = false;

// Function designed for chat between client and server.
void *func(void *arg)
{
  char buff[MAX];
  int n;
  struct sockaddr_in servaddr;

  while (1)
  {
    if (sockfd != -1)
      close(sockfd);
    // socket create and verification
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == -1)
    {
      printf("socket creation failed...\n");
      return NULL;
    }
    else
      printf("Socket successfully created..\n");
    bzero(&servaddr, sizeof(servaddr));
    // assign IP, PORT
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = inet_addr(host_address);
    servaddr.sin_port = htons(port);

    // connect the client socket to server socket
    if (connect(sockfd, (SA *)&servaddr, sizeof(servaddr)) != 0)
    {
      printf("connection with the server failed...\n");
      sleep(10);
      continue;
    }
    else
    {
      printf("connected to the server..\n");
    }

    // infinite loop for chat
    for (;;)
    {
      bzero(buff, MAX);

      // read the message from client and copy it in buffer
      n = read(sockfd, buff, sizeof(buff));
      // print buffer which contains the client contents
      // fprintf(stderr, "recieved %d bytes from host: %s", n, buff);

      // socket disconnected
      if (n <= 0)
        break;

      aee_host_msg_callback(buff, n);
    }
  }

  // After chatting close the socket
  close(sockfd);
}

static bool host_init() { return true; }

int host_send(void *ctx, const char *buf, int size)
{
  int ret;

  if (pthread_mutex_trylock(&sock_lock) == 0)
  {
    if (sockfd == -1)
    {
      pthread_mutex_unlock(&sock_lock);
      return 0;
    }

    ret = write(sockfd, buf, size);

    pthread_mutex_unlock(&sock_lock);
    return ret;
  }

  return -1;
}

void host_destroy()
{
  if (server_mode)
    close(listenfd);

  pthread_mutex_lock(&sock_lock);
  close(sockfd);
  pthread_mutex_unlock(&sock_lock);
}

/* clang-format off */
host_interface interface = {
    .init = host_init,
    .send = host_send,
    .destroy = host_destroy
};
/* clang-format on */

void *func_server_mode(void *arg)
{
  int clilent;
  struct sockaddr_in serv_addr, cli_addr;
  int n;
  char buff[MAX];
  struct sigaction sa;

  sa.sa_handler = SIG_IGN;
  sa.sa_flags = 0;
  sigemptyset(&sa.sa_mask);
  sigaction(SIGPIPE, &sa, 0);

  /* First call to socket() function */
  listenfd = socket(AF_INET, SOCK_STREAM, 0);

  if (listenfd < 0)
  {
    perror("ERROR opening socket");
    exit(1);
  }

  /* Initialize socket structure */
  bzero((char *)&serv_addr, sizeof(serv_addr));

  serv_addr.sin_family = AF_INET;
  serv_addr.sin_addr.s_addr = INADDR_ANY;
  serv_addr.sin_port = htons(port);

  /* Now bind the host address using bind() call.*/
  if (bind(listenfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
  {
    perror("ERROR on binding");
    exit(1);
  }

  listen(listenfd, 5);
  clilent = sizeof(cli_addr);

  while (1)
  {
    pthread_mutex_lock(&sock_lock);

    sockfd = accept(listenfd, (struct sockaddr *)&cli_addr, &clilent);

    pthread_mutex_unlock(&sock_lock);

    if (sockfd < 0)
    {
      perror("ERROR on accept");
      exit(1);
    }

    printf("connection established!\n");

    for (;;)
    {
      bzero(buff, MAX);

      // read the message from client and copy it in buffer
      n = read(sockfd, buff, sizeof(buff));

      // socket disconnected
      if (n <= 0)
      {
        pthread_mutex_lock(&sock_lock);
        close(sockfd);
        sockfd = -1;
        pthread_mutex_unlock(&sock_lock);

        sleep(2);
        break;
      }

      aee_host_msg_callback(buff, n);
    }
  }
}

#else
static int parse_baudrate(int baud)
{
  switch (baud)
  {
  case 9600:
    return B9600;
  case 19200:
    return B19200;
  case 38400:
    return B38400;
  case 57600:
    return B57600;
  case 115200:
    return B115200;
  case 230400:
    return B230400;
  case 460800:
    return B460800;
  case 500000:
    return B500000;
  case 576000:
    return B576000;
  case 921600:
    return B921600;
  case 1000000:
    return B1000000;
  case 1152000:
    return B1152000;
  case 1500000:
    return B1500000;
  case 2000000:
    return B2000000;
  case 2500000:
    return B2500000;
  case 3000000:
    return B3000000;
  case 3500000:
    return B3500000;
  case 4000000:
    return B4000000;
  default:
    return -1;
  }
}
static bool uart_init(const char *device, int baudrate, int *fd)
{
  int uart_fd;
  struct termios uart_term;

  uart_fd = open(device, O_RDWR | O_NOCTTY);

  if (uart_fd <= 0)
    return false;

  memset(&uart_term, 0, sizeof(uart_term));
  uart_term.c_cflag = baudrate | CS8 | CLOCAL | CREAD;
  uart_term.c_iflag = IGNPAR;
  uart_term.c_oflag = 0;

  /* set noncanonical mode */
  uart_term.c_lflag = 0;
  uart_term.c_cc[VTIME] = 30;
  uart_term.c_cc[VMIN] = 1;
  tcflush(uart_fd, TCIFLUSH);

  if (tcsetattr(uart_fd, TCSANOW, &uart_term) != 0)
  {
    close(uart_fd);
    return false;
  }

  *fd = uart_fd;

  return true;
}

static void *func_uart_mode(void *arg)
{
  int n;
  char buff[MAX];

  if (!uart_init(uart_device, baudrate, &uartfd))
  {
    printf("open uart fail! %s\n", uart_device);
    return NULL;
  }

  for (;;)
  {
    bzero(buff, MAX);

    n = read(uartfd, buff, sizeof(buff));

    if (n <= 0)
    {
      close(uartfd);
      uartfd = -1;
      break;
    }

    aee_host_msg_callback(buff, n);
  }

  return NULL;
}

static int uart_send(void *ctx, const char *buf, int size)
{
  int ret;

  ret = write(uartfd, buf, size);

  return ret;
}

static void uart_destroy() { close(uartfd); }

/* clang-format off */
static host_interface interface = {
    .send = uart_send,
    .destroy = uart_destroy
};
/* clang-format on */

#endif

static char global_heap_buf[270 * 1024] = {0};

/* clang-format off */
static void showUsage()
{
#ifndef CONNECTION_UART
     printf("Usage:\n");
     printf("\nWork as TCP server mode:\n");
     printf("\tvgl_wasm_runtime -s|--server_mode -p|--port <Port>\n");
     printf("where\n");
     printf("\t<Port> represents the port that would be listened on and the default is 8888\n");
     printf("\nWork as TCP client mode:\n");
     printf("\tvgl_wasm_runtime -a|--host_address <Host Address> -p|--port <Port>\n");
     printf("where\n");
     printf("\t<Host Address> represents the network address of host and the default is 127.0.0.1\n");
     printf("\t<Port> represents the listen port of host and the default is 8888\n");
#else
     printf("Usage:\n");
     printf("\tvgl_wasm_runtime -u <Uart Device> -b <Baudrate>\n\n");
     printf("where\n");
     printf("\t<Uart Device> represents the UART device name and the default is /dev/ttyS2\n");
     printf("\t<Baudrate> represents the UART device baudrate and the default is 115200\n");
#endif

#if BH_HAS_DLFCN
    printf("  --native-lib=<lib>       Register native libraries to the WASM module, which\n");
    printf("                           are shared object (.so) files, for example:\n");
    printf("                             --native-lib=test1.so --native-lib=test2.so\n");
#endif
}
/* clang-format on */

static bool parse_args(int argc, char *argv[])
{
  int c;

  while (1)
  {
    int optIndex = 0;
    static struct option longOpts[] = {
#ifndef CONNECTION_UART
        {"server_mode", no_argument, NULL, 's'},
        {"host_address", required_argument, NULL, 'a'},
        {"port", required_argument, NULL, 'p'},
#else
        {"uart", required_argument, NULL, 'u'},
        {"baudrate", required_argument, NULL, 'b'},
#endif
        {"help", required_argument, NULL, 'h'},
        {0, 0, 0, 0}};

    c = getopt_long(argc, argv, "sa:p:u:b:h", longOpts, &optIndex);
    if (c == -1)
      break;

    switch (c)
    {
#ifndef CONNECTION_UART
    case 's':
      server_mode = true;
      break;
    case 'a':
      host_address = optarg;
      printf("host address: %s\n", host_address);
      break;
    case 'p':
      port = atoi(optarg);
      printf("port: %d\n", port);
      break;
#else
    case 'u':
      uart_device = optarg;
      printf("uart device: %s\n", uart_device);
      break;
    case 'b':
      baudrate = parse_baudrate(atoi(optarg));
      printf("uart baudrate: %s\n", optarg);
      break;
#endif
    case 'h':
      showUsage();
      return false;
    default:
      showUsage();
      return false;
    }
  }

  return true;
}

/**
 * Initialize the Hardware Abstraction Layer (HAL) for the Littlev graphics
 * library
 */
static void hal_init(void)
{
  /* Use the 'monitor' driver which creates window on PC's monitor to simulate
   * a display*/
  monitor_init();

  /*Create a display buffer*/
  static lv_disp_buf_t disp_buf1;
  static lv_color_t buf1_1[480 * 10];
  lv_disp_buf_init(&disp_buf1, buf1_1, NULL, 480 * 10);

  /*Create a display*/
  lv_disp_drv_t disp_drv;

  /*Basic initialization*/
  memset(&disp_drv, 0, sizeof(disp_drv));
  lv_disp_drv_init(&disp_drv);
  disp_drv.buffer = &disp_buf1;
  disp_drv.flush_cb = monitor_flush;
  //    disp_drv.hor_res = 200;
  //    disp_drv.ver_res = 100;
  lv_disp_drv_register(&disp_drv);

  /* Add the mouse as input device
   * Use the 'mouse' driver which reads the PC's mouse*/
  mouse_init();
  lv_indev_drv_t indev_drv;
  lv_indev_drv_init(&indev_drv); /*Basic initialization*/
  indev_drv.type = LV_INDEV_TYPE_POINTER;
  indev_drv.read_cb =
      mouse_read; /*This function will be called periodically (by the library)
                     to get the mouse position and state*/
  lv_indev_drv_register(&indev_drv);
}

// Driver function
int iwasm_main(int argc, char *argv[])
{

  int32 ret = -1;
  char *wasm_file = NULL;
  const char *func_name = NULL;
  uint8 *wasm_file_buf = NULL;
  uint32 wasm_file_size;
  uint32 stack_size = 64 * 1024;
#if WASM_ENABLE_LIBC_WASI != 0
  uint32 heap_size = 0;
#else
  uint32 heap_size = 16 * 1024;
#endif
#if WASM_ENABLE_FAST_JIT != 0
  uint32 jit_code_cache_size = FAST_JIT_DEFAULT_CODE_CACHE_SIZE;
#endif
#if WASM_ENABLE_GC != 0
  uint32 gc_heap_size = GC_HEAP_SIZE_DEFAULT;
#endif
#if WASM_ENABLE_JIT != 0
  uint32 llvm_jit_size_level = 3;
  uint32 llvm_jit_opt_level = 3;
  uint32 segue_flags = 0;
#endif
#if WASM_ENABLE_LINUX_PERF != 0
  bool enable_linux_perf = false;
#endif
  wasm_module_t wasm_module = NULL;
  wasm_module_inst_t wasm_module_inst = NULL;
  RunningMode running_mode = 0;
  RuntimeInitArgs init_args;
  char error_buf[128] = {0};
#if WASM_ENABLE_LOG != 0
  int log_verbose_level = 2;
#endif
  bool is_repl_mode = false;
  bool is_xip_file = false;
#if WASM_CONFIGURABLE_BOUNDS_CHECKS != 0
  bool disable_bounds_checks = false;
#endif
#if WASM_ENABLE_LIBC_WASI != 0
  libc_wasi_parse_context_t wasi_parse_ctx;
#endif
#if BH_HAS_DLFCN
  // 전역으로 변경
  // const char *native_lib_list[8] = {NULL};
  // uint32 native_lib_count = 0;
  // struct native_lib *native_lib_loaded_list[8];
  // uint32 native_lib_loaded_count = 0;
#endif
#if WASM_ENABLE_DEBUG_INTERP != 0
  char *ip_addr = NULL;
  int instance_port = 0;
#endif
#if WASM_ENABLE_STATIC_PGO != 0
  const char *gen_prof_file = NULL;
#endif
#if WASM_ENABLE_THREAD_MGR != 0
  int timeout_ms = -1;
#endif

#if WASM_ENABLE_LIBC_WASI != 0
  memset(&wasi_parse_ctx, 0, sizeof(wasi_parse_ctx));
#endif

  for (argc--, argv++; argc > 0 && argv[0][0] == '-'; argc--, argv++)
  {

    if (!strcmp(argv[0], "-f") || !strcmp(argv[0], "--function"))
    {
      argc--, argv++;
      if (argc < 2)
      {
        return parse_args(argc, argv);
      }
      func_name = argv[0];
    }

    else if (!strncmp(argv[0], "--funcinfo=", 11))
    {
      // printf("funcinfo ^^^^^^^^^^^^^^^^^\n  ");
      const char *value = argv[0] + 11;
      if (value[0] == '\0')
      { // "--funcinfo=" 다음에 값이 없는 경우
        if (0 + 1 < argc)
        {
          funcinfo_filename = argv[0];
        }
        else
        {
          fprintf(stderr, "Error: --funcinfo requires a filename\n");
          return 1;
        }
      }
      else
      {
        // "--funcinfo=file.txt" 형식
        funcinfo_filename = value;
      }
    }

    else if (!strncmp(argv[0], "--native-lib=", 13))
    {
      if (argv[0][13] == '\0')
        return parse_args(argc, argv);
      if (native_lib_count >= sizeof(native_lib_list) / sizeof(char *))
      {
        printf("Only allow max native lib number %d\n",
               (int)(sizeof(native_lib_list) / sizeof(char *)));
        return 1;
      }
      native_lib_list[native_lib_count++] = argv[0] + 13;
    }

    // else if (!strncmp(argv[0], "--stack-size=", 13)) {
    //         if (argv[0][13] == '\0')
    //             return parse_args(argc, argv);
    //         stack_size = atoi(argv[0] + 13);
    //     }
    // else if (!strncmp(argv[0], "--heap-size=", 12)) {
    //         if (argv[0][12] == '\0')
    //             return parse_args(argc, argv);
    //         heap_size = atoi(argv[0] + 12);
    //     }

  }

  // RuntimeInitArgs init_args;
  korp_tid tid;

  argc = 2;
  argv[1] = "-s";

  if (!parse_args(argc, argv))
    return -1;

  memset(&init_args, 0, sizeof(RuntimeInitArgs));

  init_args.mem_alloc_type = Alloc_With_Pool;
  init_args.mem_alloc_option.pool.heap_buf = global_heap_buf;
  init_args.mem_alloc_option.pool.heap_size = sizeof(global_heap_buf);

  if (!wasm_runtime_full_init(&init_args))
  {
    printf("Init runtime environment failed.\n");
    return -1;
  }

  native_lib_loaded_count = load_and_register_native_libs(

      native_lib_list, native_lib_count, native_lib_loaded_list);

  wasm_add_func_info(infos, func_count);

  /* initialize runtime environment */

  if (!wasm_runtime_full_init(&init_args))
  {
    printf("Init runtime environment failed.\n");
    return -1;
  }

  if (!init_connection_framework())
  {
    goto fail1;
  }

  wgl_init();

  hal_init();

  if (!init_sensor_framework())
  {
    goto fail2;
  }

  /* timer manager */
  if (!init_wasm_timer())
  {
    goto fail3;
  }

#ifndef CONNECTION_UART
  if (server_mode)
    os_thread_create(&tid, func_server_mode, NULL,
                     BH_APPLET_PRESERVED_STACK_SIZE);
  else
    os_thread_create(&tid, func, NULL, BH_APPLET_PRESERVED_STACK_SIZE);
#else
  os_thread_create(&tid, func_uart_mode, NULL, BH_APPLET_PRESERVED_STACK_SIZE);
#endif

  app_manager_startup(&interface);

  exit_wasm_timer();

fail3:
  exit_sensor_framework();

fail2:
  wgl_exit();
  exit_connection_framework();

fail1:
  wasm_runtime_destroy();
  return -1;
}