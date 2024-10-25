# Copyright (C) 2019 Intel Corporation.  All rights reserved.
# SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception

cmake_minimum_required (VERSION 2.9)

project (wasm_runtime_wgl)

set (WAMR_BUILD_PLATFORM "linux")

set(CMAKE_BUILD_TYPE Debug)

set(USER_TEST_SIGNAL 1)


# Reset default linker flags
set (CMAKE_SHARED_LIBRARY_LINK_C_FLAGS "")
set (CMAKE_SHARED_LIBRARY_LINK_CXX_FLAGS "")

################  wamr runtime settings  ################

if(USER_TEST_SIGNAL)
  message("USER_TEST_SIGNAL = 1 로 설정됨, 추가 옵션")
  set (WAMR_ROOT_DIR  ${CMAKE_CURRENT_LIST_DIR}/../../../../deps/wasm-micro-runtime)
  set (DEPS_DIR       ${CMAKE_CURRENT_LIST_DIR}/../../../../deps)
  set (WAMR_APP_FRAMEWORK_DIR       ${CMAKE_CURRENT_LIST_DIR}/../../../..)
else()
  message("USER_TEST_SIGNAL = 0 으로 설정됨, 기본 설정")
  set (WAMR_ROOT_DIR  ${CMAKE_CURRENT_LIST_DIR}/../../../../deps-original/wasm-micro-runtime)
  set (DEPS_DIR       ${CMAKE_CURRENT_LIST_DIR}/../../../../deps-original)
  set (WAMR_APP_FRAMEWORK_DIR       ${CMAKE_CURRENT_LIST_DIR}/../../../..)
endif()


add_definitions(-DLV_CONF_INCLUDE_SIMPLE)

## use library and headers in the SDK

if(USER_TEST_SIGNAL)
  message("USER_TEST_SIGNAL = 1 로 설정됨, 추가 옵션")
  link_directories(${WAMR_APP_FRAMEWORK_DIR}/wamr-sdk/out/gui/runtime-sdk/lib)
  include_directories(
    ${WAMR_APP_FRAMEWORK_DIR}/wamr-sdk/out/gui/runtime-sdk/include
    ${WAMR_APP_FRAMEWORK_DIR}/wamr-sdk/out/gui/runtime-sdk/include/bi-inc/deps
    ${WAMR_ROOT_DIR}/core/shared/utils
    ${WAMR_ROOT_DIR}/core/shared/platform/${WAMR_BUILD_PLATFORM}
  )
else()
  message("USER_TEST_SIGNAL = 0 으로 설정됨, 기본 설정")
  link_directories(${WAMR_APP_FRAMEWORK_DIR}/wamr-sdk-original/out/gui/runtime-sdk/lib)
  include_directories(
    ${WAMR_APP_FRAMEWORK_DIR}/wamr-sdk-original/out/gui/runtime-sdk/include
    ${WAMR_APP_FRAMEWORK_DIR}/wamr-sdk-original/out/gui/runtime-sdk/include/bi-inc/deps
    ${WAMR_ROOT_DIR}/core/shared/utils
    ${WAMR_ROOT_DIR}/core/shared/platform/${WAMR_BUILD_PLATFORM}
  )
endif()




################  application related  ################

set (LV_DRIVERS_DIR ${DEPS_DIR}/lv_drivers)
file (GLOB_RECURSE LV_DRIVERS_SOURCES "${LV_DRIVERS_DIR}/*.c")


# # nitive lib 를 사용하기 위해 추가한 include 경로
# set (WAMR_BUILD_SHARED 1)
# if (NOT DEFINED WAMR_BUILD_SHARED)
# set (WAMR_BUILD_SHARED 0)
# elseif (WAMR_BUILD_SHARED EQUAL 1)
# message ("build WAMR as shared libraries")
# endif ()

# include (/root/wamr-app-framework_debug/deps/wasm-micro-runtime/core/shared/utils/uncommon/shared_uncommon.cmake)
# set (RUNTIME_SOURCE_ALL
#     # ${WAMR_ROOT_DIR}/product-mini/platforms/posix/main.c
#     ${UNCOMMON_SHARED_SOURCE}
# )
# # add_executable (wasm_runtime_wgl ${RUNTIME_SOURCE_ALL})




if (NOT (CMAKE_C_COMPILER MATCHES ".*clang.*" OR CMAKE_C_COMPILER_ID MATCHES ".*Clang"))
  set (CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -Wl,--gc-sections")
endif ()
set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wextra -Wformat -Wformat-security")

set (WAMR_BUILD_INTERP 1)
set (WAMR_BUILD_LIBC_BUILTIN 1)
set (WAMR_BUILD_FAST_INTERP 1)

# add_library(vmlib ${WAMR_RUNTIME_LIB_SOURCE})
if(USER_TEST_SIGNAL)
  message("USER_TEST_SIGNAL = 1 로 설정됨, 추가 옵션")
  set (WAMR_ROOT_DIR ${CMAKE_CURRENT_LIST_DIR}/../../../../deps/wasm-micro-runtime)
else()
  message("USER_TEST_SIGNAL = 0 으로 설정됨, 기본 설정")
  set (WAMR_ROOT_DIR ${CMAKE_CURRENT_LIST_DIR}/../../../../deps-original/wasm-micro-runtime)
endif()



include (${WAMR_ROOT_DIR}/build-scripts/runtime_lib.cmake)
add_library(libiwasm SHARED ${WAMR_RUNTIME_LIB_SOURCE})
set_target_properties (libiwasm PROPERTIES OUTPUT_NAME iwasm)


set (PROJECT_SRC_DIR ${CMAKE_CURRENT_LIST_DIR}/../src/platform/${WAMR_BUILD_PLATFORM})
include_directories(
    ${PROJECT_SRC_DIR}
    ${DEPS_DIR}
    ${DEPS_DIR}/lvgl
    ${DEPS_DIR}/lvgl/src
)

set (SOURCES
     ${PROJECT_SRC_DIR}/main.c
     ${PROJECT_SRC_DIR}/iwasm_main.c
     ${LV_DRIVERS_SOURCES}
     )

  
     

add_executable (wasm_runtime_wgl ${SOURCES} ${RUNTIME_SOURCE_ALL})

target_link_libraries (wasm_runtime_wgl 

# libiwasm
# ${WAMR_BUILD_SHARED}

vmlib 

-lm -ldl -lpthread -lSDL2

)
#target_link_libraries(wasm_runtime_wgl PRIVATE SDL2 )