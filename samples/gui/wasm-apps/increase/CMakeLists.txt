cmake_minimum_required(VERSION 2.8)

project(wgl)

set (WAMR_ROOT_DIR ${CMAKE_CURRENT_LIST_DIR}/../../../../deps/wasm-micro-runtime)
set (WAMR_APP_FRAMEWORK_ROOT_DIR ${CMAKE_CURRENT_LIST_DIR}/../../../..)

include_directories(
    ${WAMR_APP_FRAMEWORK_ROOT_DIR}/wamr-sdk/out/gui/app-sdk/wamr-app-framework/include
    ${CMAKE_CURRENT_LIST_DIR}/../../../../deps
    
)

set (CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS},-L${WAMR_APP_FRAMEWORK_ROOT_DIR}/wamr-sdk/out/gui/app-sdk/wamr-app-framework/lib")
set (CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS},--export=on_init,--export=on_timer_callback,--export=on_widget_event,--export=__heap_base,--export=__data_end,--allow-undefined")
# set (CMAKE_C_FLAGS          "${CMAKE_C_FLAGS} -O0 -Wno-unused-command-line-argument")
set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -g -O0 -fno-inline -fno-omit-frame-pointer -Wno-unused-command-line-argument")




# # SDL2 헤더 파일 경로 추가
# include_directories(/usr/local/include/SDL2)

# # # SDL2 라이브러리 경로 추가
# link_directories(/usr/local/lib)

# -I/usr/local/include/SDL2 -D_REENTRANT -L/usr/local/lib -lSDL2

add_executable(ui_increase.wasm
    ${CMAKE_CURRENT_LIST_DIR}/src/main.c
)



target_link_libraries(ui_increase.wasm  app_framework  ) #-lSDL2
# -lm -ldl -lpthread 
