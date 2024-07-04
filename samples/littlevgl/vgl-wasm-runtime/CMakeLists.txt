# Copyright (C) 2019 Intel Corporation.  All rights reserved.
# SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception

cmake_minimum_required (VERSION 2.9)

project (vgl_wasm_runtime)

set (WAMR_BUILD_PLATFORM "linux")

# Reset default linker flags
set (CMAKE_SHARED_LIBRARY_LINK_C_FLAGS "")
set (CMAKE_SHARED_LIBRARY_LINK_CXX_FLAGS "")


################  wamr runtime settings  ################

set (WAMR_ROOT_DIR ${CMAKE_CURRENT_LIST_DIR}/../../../deps/wasm-micro-runtime)
set (WAMR_APP_FRAMEWORK_ROOT_DIR ${CMAKE_CURRENT_LIST_DIR}/../../..)

## use library and headers in the SDK
link_directories(${WAMR_APP_FRAMEWORK_ROOT_DIR}/wamr-sdk/out/littlevgl/runtime-sdk/lib)
include_directories(
    ${WAMR_APP_FRAMEWORK_ROOT_DIR}/wamr-sdk/out/littlevgl/runtime-sdk/include
    ${WAMR_APP_FRAMEWORK_ROOT_DIR}/wamr-sdk/out/littlevgl/runtime-sdk/include/bi-inc/deps
    ${WAMR_ROOT_DIR}/core/shared/utils
    ${WAMR_ROOT_DIR}/core/shared/platform/${WAMR_BUILD_PLATFORM}
)

###############  application related  ###############
include_directories(${CMAKE_CURRENT_LIST_DIR}/src)

add_executable (vgl_wasm_runtime src/platform/${WAMR_BUILD_PLATFORM}/main.c
                src/platform/${WAMR_BUILD_PLATFORM}/iwasm_main.c
                src/platform/${WAMR_BUILD_PLATFORM}/display_indev.c
                src/platform/${WAMR_BUILD_PLATFORM}/mouse.c)

# find SDL2
find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})


# set llvm dir
set(LLVM_DIR "${WAMR_ROOT_DIR}/core/deps/llvm/build/lib/cmake/llvm")
if(EXISTS ${LLVM_DIR})

    find_package(LLVM REQUIRED CONFIG)
    include_directories(${LLVM_INCLUDE_DIRS})
    add_definitions(${LLVM_DEFINITIONS})
    
    message(STATUS " LLVM version must be 15 ")
    message(STATUS " Found LLVM ${LLVM_PACKAGE_VERSION}")
    message(STATUS " LLVM include directories: ${LLVM_INCLUDE_DIRS}")
    message(STATUS " LLVM libraries: ${LLVM_LIBRARY_DIRS}")

    include("../wamr_config_littlevgl.cmake")

    if(WAMR_BUILD_TARGET STREQUAL "AARCH64")
    
        message(STATUS " LLVMAArch64CodeGen ")
        set(LLVM_LINK_OPTION LLVMOrcJIT LLVMAArch64CodeGen)

        set(CMAKE_C_COMPILER /home/gcc-linaro-14.0.0-2023.06-x86_64_aarch64-linux-gnu/bin/aarch64-linux-gnu-gcc)
        set(CMAKE_CXX_COMPILER /home/gcc-linaro-14.0.0-2023.06-x86_64_aarch64-linux-gnu/bin/aarch64-linux-gnu-g++)
        set(ARM_A7_COMPILER_DIR /home/gcc-linaro-14.0.0-2023.06-x86_64_aarch64-linux-gnu/bin)
        set(ARM_A7_SDKTARGETSYSROOT /home/gcc-linaro-14.0.0-2023.06-x86_64_aarch64-linux-gnu/aarch64-linux-gnu/libc)


    elseif(WAMR_BUILD_TARGET STREQUAL "X86_64")
        message(STATUS " LLVMX86CodeGen ")
        set(LLVM_LINK_OPTION LLVMOrcJIT LLVMX86CodeGen)

    else()
        message(STATUS " WIP, can't find target ")
        set(LLVM_LINK_OPTION )
        
    endif()

    MESSAGE(STATUS " **************** C_COMPILER: ${CMAKE_C_COMPILER}")
    MESSAGE(STATUS " **************** CXX_COMPILER: ${CMAKE_CXX_COMPILER}")
    message(STATUS "ARM_A7_COMPILER_DIR is set to $ENV{ARM_A7_COMPILER_DIR}")
    message(STATUS "ARM_A7_SDKTARGETSYSROOT is set to $ENV{ARM_A7_SDKTARGETSYSROOT}")

else()
    message(STATUS "LLVM Not Found")

endif()



target_link_libraries (vgl_wasm_runtime 
    vmlib 
    -lm 
    -ldl 
    -lpthread 

    ${LLVM_LINK_OPTION}

    ${SDL2_LIBRARIES}
)

