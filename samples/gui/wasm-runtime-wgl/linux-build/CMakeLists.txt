# Copyright (C) 2019 Intel Corporation.  All rights reserved.
# SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception

cmake_minimum_required (VERSION 2.9)

project (wasm_runtime_wgl)

set (WAMR_BUILD_PLATFORM "linux")

# Reset default linker flags
set (CMAKE_SHARED_LIBRARY_LINK_C_FLAGS "")
set (CMAKE_SHARED_LIBRARY_LINK_CXX_FLAGS "")

################  wamr runtime settings  ################

set (WAMR_ROOT_DIR  ${CMAKE_CURRENT_LIST_DIR}/../../../../deps/wasm-micro-runtime)
set (DEPS_DIR       ${CMAKE_CURRENT_LIST_DIR}/../../../../deps)
set (WAMR_APP_FRAMEWORK_DIR       ${CMAKE_CURRENT_LIST_DIR}/../../../..)


add_definitions(-DLV_CONF_INCLUDE_SIMPLE)

## use library and headers in the SDK
link_directories(${WAMR_APP_FRAMEWORK_DIR}/wamr-sdk/out/gui/runtime-sdk/lib)
include_directories(
    ${WAMR_APP_FRAMEWORK_DIR}/wamr-sdk/out/gui/runtime-sdk/include
    ${WAMR_APP_FRAMEWORK_DIR}/wamr-sdk/out/gui/runtime-sdk/include/bi-inc/deps
    ${WAMR_ROOT_DIR}/core/shared/utils
    ${WAMR_ROOT_DIR}/core/shared/platform/${WAMR_BUILD_PLATFORM}
)

################  application related  ################

set (LV_DRIVERS_DIR ${DEPS_DIR}/lv_drivers)
file (GLOB_RECURSE LV_DRIVERS_SOURCES "${LV_DRIVERS_DIR}/*.c")

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

add_executable (wasm_runtime_wgl ${SOURCES})

include_directories(/mnt/d/wamr/SDL/include/)

#include </usr/local/include/SDL2/SDL.h>
set(SDL2_PATH "/usr/local/include/SDL2")
find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})
# target_link_libraries(your_target_name ${SDL2_LIBRARIES})


target_link_libraries (wasm_runtime_wgl vmlib -lm -ldl -lpthread ${SDL2_LIBRARIES})
# target_link_libraries(wasm_runtime_wgl PRIVATE SDL2 )

