"gui" sample introduction
==============
This sample demonstrates that a graphic user interface application in WebAssembly programming with WAMR graphic library(WGL)  which is part of WAMR app-framework.

Compared with the [littlevgl](../littlevgl) sample, WGL compiles LittlevGL source code into the WAMR runtime and defines a set of wrapper API's for exporting to Webassembly application.

Below picture shows the WASM application is running on an STM board with an LCD touch panel.

![WAMR UI SAMPLE](../../doc/pics/vgl_demo2.png "WAMR UI DEMO")

 When user clicks the blue button, the WASM application increases the counter, and the latest counter value is displayed on the top banner of the touch panel. The number on top will plus one each second, and the number on the bottom will plus one when clicked.

# Test on Linux

Install required SDK and libraries

- 64 bit SDL(simple directmedia layer) (Note: only necessary when `WAMR_BUILD_TARGET` is set to `X86_64` when building WAMR runtime)
Use apt-get:

  ```bash
  sudo apt-get install libsdl2-dev
  ```


./build.sh 실행 전

필수 패키지 다운로드
```
sudo apt-get install build-essential git make \
pkg-config cmake ninja-build gnome-desktop-testing libasound2-dev libpulse-dev \
libaudio-dev libjack-dev libsndio-dev libx11-dev libxext-dev \
libxrandr-dev libxcursor-dev libxfixes-dev libxi-dev libxss-dev \
libxkbcommon-dev libdrm-dev libgbm-dev libgl1-mesa-dev libgles2-mesa-dev \
libegl1-mesa-dev libdbus-1-dev libibus-1.0-dev libudev-dev fcitx-libs-dev
```

크로스컴파일러 2016 다운로드
```
wget https://releases.linaro.org/components/toolchain/binaries/4.9-2016.02/aarch64-linux-gnu/gcc-linaro-4.9-2016.02-x86_64_aarch64-linux-gnu.tar.xz
```

/home 경로에 압축 해제
```
tar -xf gcc-linaro-4.9-2016.02-x86_64_aarch64-linux-gnu.tar.xz -C /home
```
.bashrc 파일 작성
```
sudo vi ~/.bashrc

 export ARM_A7_COMPILER_DIR="/home/gcc-linaro-4.9-2016.02-x86_64_aarch64-linux-gnu/bin"
export ARM_A7_SDKTARGETSYSROOT="/home/gcc-linaro-4.9-2016.02-x86_64_aarch64-linux-gnu/aarch64-linux-gnu/libc"
export CC="/home/gcc-linaro-4.9-2016.02-x86_64_aarch64-linux-gnu/bin/aarch64-linux-gnu-gcc"
export CXX="/home/gcc-linaro-4.9-2016.02-x86_64_aarch64-linux-gnu/bin/aarch64-linux-gnu-g++"

source ~/.bashrc
```

wamr-app-framework/deps 에서 ./download.sh 실행
lv_drivers와 lvgl 다운로드 후
lv_drivers/indev의 mouse.h mousewheel.h keyboard.h
lv_drivers/display의 monitor.c 에서 
```
#ifndef MONITOR_SDL_INCLUDE_PATH
#  define MONITOR_SDL_INCLUDE_PATH <SDL2/SDL.h>
#endif
#include MONITOR_SDL_INCLUDE_PATH
```
부분을 주석 처리하고 

아래의 그림과 같이 SDL2의 경로를 헤더에 추가
```
// #ifndef MONITOR_SDL_INCLUDE_PATH
// #define MONITOR_SDL_INCLUDE_PATH <SDL2/SDL.h>
// #endif
// #include MONITOR_SDL_INCLUDE_PATH
#include </usr/local/include/SDL2/SDL.h>
```


/gui/wasm-runtime-wgl/linux-build/ 의 CMakeList.txt의
마지막 라인 target_link_libraries를 수정
```
include_directories(/mnt/d/wamr/SDL/include/)
set(SDL2_PATH "/usr/local/include/SDL2")
find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})
# target_link_libraries(your_target_name ${SDL2_LIBRARIES})

target_link_libraries (wasm_runtime_wgl vmlib -lm -ldl -lpthread ${SDL2_LIBRARIES})
# target_link_libraries(wasm_runtime_wgl PRIVATE SDL2 )

```

./build.sh 실행


Build and Run
--------------

- Build
  ```bash
  ./build.sh
  ```
    All binaries are in "out", which contains "host_tool", "ui_decrease.wasm", "ui_increase.wasm" and "wasm_runtime_wgl".

- Run WASM VM Linux applicaton & install WASM APP
 First start wasm_runtime_wgl in server mode.
  ```bash
  ./wasm_runtime_wgl -s
  ```
 Then install wasm APP by using host tool.
  ```bash
  ./host_tool -i inc -f ui_increase.wasm
  # or
  ./host_tool -i dec -f ui_decrease.wasm
  ```
