/*
 * Copyright (C) 2019 Intel Corporation.  All rights reserved.
 * SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
 */

// #include "/usr/local/include/SDL2/SDL.h"
// #include "/usr/include/SDL2/SDL.h" // SDL 관련 함수

#include "wa-inc/lvgl/lvgl.h"
#include "wa-inc/timer_wasm_app.h"
#include "wasm_app.h"
#include <stdlib.h>

// #include "./zlib.h"
// #include "./zlog.h"


// #define MONITOR_SDL_INCLUDE_PATH <SDL2/SDL.h>
// #include <SDL2/SDL.h>
// #include "./SDL2/SDL.h"
// #include </usr/include/SDL2/SDL_ttf.h>  // SDL_ttf를 사용하는 경우
#include <stdio.h>         // 입출력 함수 사용을 위해
#include <stdint.h>





extern char g_widget_text[];

int test_add(int x, int y);

int test_add2(float x, int y);

float halfff(float x);

float halfff2(float x);

int test_sqrt(int x, int y);

int test_hello(const char *name, char *buf, size_t buflen);

int test_hello2(const char *name, char *buf, size_t buflen);

int add(int x, int y);

int func222(int x, int y);

int testtest(int x, int y);

static void btn_event_cb(lv_obj_t *btn, lv_event_t event);


typedef uint8_t Uint8;
typedef uint16_t Uint16;
typedef uint32_t Uint32;
typedef int SDL_bool;

typedef struct SDL_BlitMap SDL_BlitMap;
typedef struct SDL_Window SDL_Window;
typedef struct SDL_Renderer SDL_Renderer;
typedef struct SDL_Surface SDL_Surface;

// typedef struct SDL_Color
// {
//     Uint8 r;
//     Uint8 g;
//     Uint8 b;
//     Uint8 a;
// } SDL_Color;

// typedef struct SDL_Palette
// {
//     int ncolors;
//     SDL_Color *colors;
//     Uint32 version;
//     int refcount;
// } SDL_Palette;



// typedef struct SDL_DisplayMode
// {
//     Uint32 format;              /**< pixel format */
//     int w;                      /**< width, in screen coordinates */
//     int h;                      /**< height, in screen coordinates */
//     int refresh_rate;           /**< refresh rate (or zero for unspecified) */
//     void *driverdata;           /**< driver-specific data, initialize to 0 */
// } SDL_DisplayMode;

// typedef struct SDL_PixelFormat
// {
//     Uint32 format;
//     SDL_Palette *palette;
//     Uint8 BitsPerPixel;
//     Uint8 BytesPerPixel;
//     Uint8 padding[2];
//     Uint32 Rmask;
//     Uint32 Gmask;
//     Uint32 Bmask;
//     Uint32 Amask;
//     Uint8 Rloss;
//     Uint8 Gloss;
//     Uint8 Bloss;
//     Uint8 Aloss;
//     Uint8 Rshift;
//     Uint8 Gshift;
//     Uint8 Bshift;
//     Uint8 Ashift;
//     int refcount;
//     struct SDL_PixelFormat *next;
// } SDL_PixelFormat;

// typedef struct SDL_Rect
// {
//     int x, y;
//     int w, h;
// } SDL_Rect;

// typedef struct SDL_Surface
// {
//     Uint32 flags;               /**< Read-only */
//     SDL_PixelFormat *format;    /**< Read-only */
//     int w, h;                   /**< Read-only */
//     int pitch;                  /**< Read-only */
//     void *pixels;               /**< Read-write */

//     /** Application data associated with the surface */
//     void *userdata;             /**< Read-write */

//     /** information needed for surfaces requiring locks */
//     int locked;                 /**< Read-only */

//     /** list of BlitMap that hold a reference to this surface */
//     void *list_blitmap;         /**< Private */

//     /** clipping information */
//     SDL_Rect clip_rect;         /**< Read-only */

//     /** info for fast blit mapping to other surfaces */
//     SDL_BlitMap *map;           /**< Private */

//     /** Reference count -- used when freeing surface */
//     int refcount;               /**< Read-mostly */
// } SDL_Surface;

// struct SDL_Window
// {
//     const void *magic;
//     Uint32 id;
//     char *title;
//     SDL_Surface *icon;
//     int x, y;
//     int w, h;
//     int min_w, min_h;
//     int max_w, max_h;
//     Uint32 flags;
//     Uint32 last_fullscreen_flags;

//     /* Stored position and size for windowed mode */
//     SDL_Rect windowed;

//     SDL_DisplayMode fullscreen_mode;

//     float brightness;
//     Uint16 *gamma;
//     Uint16 *saved_gamma;        /* (just offset into gamma) */

//     SDL_Surface *surface;
//     SDL_bool surface_valid;

//     SDL_bool is_hiding;
//     SDL_bool is_destroying;

//     // SDL_WindowShaper *shaper;

//     // SDL_HitTest hit_test;
//     // void *hit_test_data;

//     // SDL_WindowUserData *data;

//     void *driverdata;

//     SDL_Window *prev;
//     SDL_Window *next;
// };



// // #   define DECLSPEC __attribute__ ((visibility("default")))

// // #define SDLCALL

// // extern DECLSPEC int SDLCALL SDL_Init(Uint32 flags);






// Uint32 * SDL_CreateWindow(const char *title,
//                               int x, int y, int w,
//                               int h, Uint32 flags);

// SDL_Renderer * SDL_CreateRenderer( SDL_Window  * window,
//                                                int index, Uint32 flags);


uint32_t count = 0;
char count_str[11] = {0};
lv_obj_t *hello_world_label;
lv_obj_t *count_label;
lv_obj_t *btn1;
lv_obj_t *label_count1;
int label_count1_value = 1;
char label_count1_str[11] = {0};

void timer1_update(user_timer_t timer1)
{
  if ((count % 100) == 0)
  {
    snprintf(count_str, sizeof(count_str), "%d", count / 100);
    lv_label_set_text(count_label, count_str);
  }
  ++count;
}

void on_init()
{


//   int x = 10, y = 20, res;

// printf("동작 테스트\n");
// // add 함수 테스트
// x = 9;
// y = 11;
// res = add(x, y);
// printf(" add(%d, %d) = %d\n\n", x, y, res);

// // func222 함수 테스트
// x = 333;
// y = 444;
// res = func222(x, y);
// printf(" %d ++ = %d\n\n", x, res);

// float f = 4.125;
// float ff = 5.875;

// // test_add2 함수 테스트
// // test_add2(f, x);

// // hello 함수 호출
// // hello();

// // 사용자 정의 함수 테스트
// // user_func1(1);
// printf("char *user_func3(char *str) test : ");
// // user_func2("input testtttt\n\n");
// printf("%s\n\n", user_func3("string input output test "));

// // halfff, halfff2, halfff3 함수 테스트
// printf("float type test : ");

// // printf("halfff is : %f   %f\n\n\n", halfff(f), f);

// printf("halfff22 is : %f\n\n\n", halfff2(x));

// // printf("halfff333 is : %f\n\n\n", halfff3(f));

// printf("end\n\n\n");

// // test_sqrt 함수 테스트 (x * x + y * y)
// // res = test_sqrt(1, 2);
// // printf("\n%d TEST_SQRT \n", res);

// // test_boolean 함수 테스트
// printf("char is : %c\n", test_boolean('a', 'b'));


  char *text;

  hello_world_label = lv_label_create(NULL, NULL);
  lv_label_set_text(hello_world_label, " ");
  text = lv_label_get_text(hello_world_label);
  printf("Label text %lu %s \n\n", strlen(text), text);
  lv_obj_align(hello_world_label, NULL, LV_ALIGN_IN_TOP_LEFT, 0, 0);

  count_label = lv_label_create(NULL, NULL);
  lv_obj_align(count_label, NULL, LV_ALIGN_IN_TOP_MID, 0, 0);

  /* Create a button on the current loaded screen */
  btn1 = lv_btn_create(NULL, NULL);
  /* Set function to be called when the button is released */
  lv_obj_set_event_cb(btn1, (lv_event_cb_t)btn_event_cb);
  /* Align below the label */
  lv_obj_align(btn1, NULL, LV_ALIGN_CENTER, 0, 0);

  /* Create a label on the button */
  lv_obj_t *btn_label = lv_label_create(btn1, NULL);
  lv_label_set_text(btn_label, "import test");

  label_count1 = lv_label_create(NULL, NULL);
  lv_label_set_text(label_count1, "1");
  lv_obj_align(label_count1, NULL, LV_ALIGN_IN_BOTTOM_MID, 0, 0);

  /* Set up a timer */
  user_timer_t timer;
  timer = api_timer_create(10, true, false, timer1_update);
  if (timer)
    api_timer_restart(timer, 10);
  else
    printf("Fail to create timer.\n");





// create_window();
// create_window2();

// create_window3();
// create_dashboard();
// create_dashboard2();

// // sdl_color_example();

// rectangle();


if (SDL_Init(0x00000020u) != NULL) {
        printf("SDL 초기화 실패: \n");
    }
    else
    {
      printf("SDL 초기화 성공\n");
    }

//     // if (TTF_Init() == -1) {
//     //     printf("TTF 초기화 실패: %s\n", TTF_GetError());
//     //     SDL_Quit();
//     // }
//     // else{
//     //   printf("TTF_Init 초기화 성공\n");
//     // }

// //     // SDL 창 생성
    SDL_Window *window = SDL_CreateWindow("SDL window",
    0x2FFF0000u, 0x2FFF0000u, 640, 480, 0x00000020u);


if (sizeof(void*) == 8) {
        printf("이 프로그램은 64비트로 컴파일되었습니다.\n");
    }
    else if (sizeof(void*) == 4) {
        printf("이 프로그램은 32비트로 컴파일되었습니다.\n");
    }
    else {
        printf("알 수 없는 비트 수입니다.\n");
    }

    printf("window : %d\n", window);
    printf("window pointer: %p\n", (void*)window);
    printf("Size of SDL_Window*: %zu bytes\n", sizeof(SDL_Window*));
    printf("Size of void*: %zu bytes\n", sizeof(void*));

        SDL_Surface* screenSurface = SDL_GetWindowSurface(window);

// Uint32 colors[] = {
//         SDL_MapRGB(screenSurface->format, 0xFF, 0x00, 0x00), // 빨강
//         SDL_MapRGB(screenSurface->format, 0xFF, 0xA5, 0x00), // 주황
//         SDL_MapRGB(screenSurface->format, 0xFF, 0xFF, 0x00), // 노랑
//         SDL_MapRGB(screenSurface->format, 0x00, 0xFF, 0x00), // 초록
//         SDL_MapRGB(screenSurface->format, 0x00, 0x00, 0xFF)  // 파랑
//     };


// //     // 색상을 순차적으로 변경
//     for (int i = 0; i < 5; i++) {
//         SDL_FillRect(screenSurface, NULL, colors[i]); // 현재 색상으로 화면 채우기
//         SDL_UpdateWindowSurface(window); // 화면 업데이트
//         SDL_Delay(1000); // 1초 대기
//     }


  if (window == NULL) {
        printf("창 생성 실패 \n");
  }
  else{
    printf("창 생성 성공\n");
  }  




// //   SDL_DestroyWindow(0);

//   printf("렌더러 선언\n");

  SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, 0x00000002);

//     if (renderer == NULL) {
//         printf("렌더러 생성 실패: \n");
//         // SDL_DestroyWindow(window);
//     }
//     else
//     {
//       printf("랜더리 성공\n");
//     }


    

// 사각형의 초기 위치와 크기
    // SDL_Rect rect = { 0, 220, 50, 50 };
    // int speed = 5; // 사각형의 속도

//  // 메인 루프
    // int running = 1;
    // while (running) {
    //     SDL_Event event;
    //     while (SDL_PollEvent(&event)) {
    //         if (event.type == SDL_QUIT) {
    //             running = 0;
    //         }
    //     }

        // // 사각형을 오른쪽으로 이동
        // rect.x += speed;
        // if (rect.x + rect.w > 640 || rect.x < 0) {
        //     speed = -speed; // 벽에 닿으면 방향을 반대로
        // }

        // // 화면을 검은색으로 클리어
        // SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        // SDL_RenderClear(renderer);

        // // 사각형을 빨간색으로 렌더링
        // SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
        // SDL_RenderFillRect(renderer, &rect);

        // // 화면 업데이트
        // SDL_RenderPresent(renderer);

        // // 16ms (약 60fps) 대기
        // SDL_Delay(16);
    // }

    // // 자원 해제
    // SDL_DestroyRenderer(renderer);
    // SDL_DestroyWindow(window);
    // SDL_Quit();







}

static void btn_event_cb(lv_obj_t *btn, lv_event_t event)
{
  if (event == LV_EVENT_RELEASED)
  {
    label_count1_value++;
    snprintf(label_count1_str, sizeof(label_count1_str), "%d",
             label_count1_value);
    lv_label_set_text(label_count1, label_count1_str);
    if (label_count1_value == 100)
      label_count1_value = 0;
  }
}


  // res = test_add(x, y); // 1665
  // printf("test_add %d + %d = %d\n", x, y, res);

  // x = 5, y = 10;
  // res = test_add_error(x, y);
  // printf("test_add_error result is : %d + %d = %d\n", x, y, res);

  // zlogzlogzlogzlogzlogzlogzlogzlogzlogzlogzlogzlogzlogzlogzlogzlogzlogzlog
  // zlogzlogzlogzlogzlogzlogzlogzlogzlogzlogzlogzlogzlogzlogzlogzlogzlogzlog
  // if (zlog_init("zlog.conf"))
  // {
  //   printf("zlog 초기화 실패\n");
  //   // return -1;
  // }
  // else
  // {
  //   printf("zlog 초기화 성공\n");
  // }

  // // 카테고리 가져오기
  // zlog_category_t *my_cat = zlog_get_category("my_category");
  // if (!my_cat)
  // {
  //   printf("카테고리 가져오기 실패\n");
  //   zlog_fini();
  //   // return -2;
  // }
  // else
  // {
  //   printf("카테고리 가져오기 성공\n");
  // }

  // 로그 기록
  // zlog_info(my_cat, "정보 로그 메시지");
  // zlog_warn(my_cat, "경고 로그 메시지");
  // zlog_error(my_cat, "에러 로그 메시지");
  // zlog_debug(my_cat, "디버그 로그 메시지");

  // zlog 종료
  // zlog_fini();

  // zlogzlogzlogzlogzlogzlogzlogzlogzlogzlogzlogzlogzlogzlogzlogzlogzlogzlog
  // zlogzlogzlogzlogzlogzlogzlogzlogzlogzlogzlogzlogzlogzlogzlogzlogzlogzlog
  // zlogzlogzlogzlogzlogzlogzlogzlogzlogzlogzlogzlogzlogzlogzlogzlogzlogzlog
