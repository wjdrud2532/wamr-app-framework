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

############### set JIT settings  ###############
include("../wamr_config_littlevgl.cmake")

if(WAMR_BUILD_JIT EQUAL 1)
    set(LLVM_DIR "${WAMR_ROOT_DIR}/core/deps/llvm/build/lib/cmake/llvm")
    
    if(EXISTS ${LLVM_DIR})
        find_package(LLVM REQUIRED CONFIG)
        include_directories(${LLVM_INCLUDE_DIRS})
        add_definitions(${LLVM_DEFINITIONS})

        message(STATUS " LLVM version must be 15 ")
        message(STATUS " Found LLVM ${LLVM_PACKAGE_VERSION}")
        message(STATUS " LLVM include directories: ${LLVM_INCLUDE_DIRS}")
        message(STATUS " LLVM libraries: ${LLVM_LIBRARY_DIRS}")


        if(WAMR_BUILD_TARGET STREQUAL "AARCH64")
            message(STATUS " LLVMAArch64CodeGen ")
            set(LLVM_LINK_OPTION LLVMOrcJIT LLVMAArch64CodeGen)

        elseif(WAMR_BUILD_TARGET STREQUAL "X86_64")
            message(STATUS " LLVMX86CodeGen ")
            set(LLVM_LINK_OPTION LLVMOrcJIT LLVMX86CodeGen)

        else()
            message(STATUS " WIP, can't find target ")
            set(LLVM_LINK_OPTION )
        endif()
    else()
        message(STATUS "LLVM Not Found")
    endif()

    MESSAGE(STATUS " **************** C_COMPILER: ${CMAKE_C_COMPILER}")
    MESSAGE(STATUS " **************** CXX_COMPILER: ${CMAKE_CXX_COMPILER}")
    MESSAGE(STATUS " **************** ARM_A7_COMPILER_DIR is set to $ENV{ARM_A7_COMPILER_DIR}")
    MESSAGE(STATUS " **************** ARM_A7_SDKTARGETSYSROOT is set to $ENV{ARM_A7_SDKTARGETSYSROOT}")
endif()

add_executable (vgl_wasm_runtime src/platform/${WAMR_BUILD_PLATFORM}/main.c
                src/platform/${WAMR_BUILD_PLATFORM}/iwasm_main.c
                src/platform/${WAMR_BUILD_PLATFORM}/display_indev.c
                src/platform/${WAMR_BUILD_PLATFORM}/mouse.c)

if(CMAKE_SYSTEM_PROCESSOR STREQUAL "x86_64" AND WAMR_BUILD_TARGET STREQUAL "AARCH64")
       
    #크로스 컴파일을 하는 경우 아래와 같이 설정
    include_directories(/mnt/d/wamr/SDL/include/)
    set(SDL2_PATH "/usr/local/include/SDL2")
    find_package(SDL2 REQUIRED)
    include_directories(${SDL2_INCLUDE_DIRS})
        
    target_link_libraries (vgl_wasm_runtime vmlib -lm -ldl -lpthread 
    ${SDL2_LIBRARIES} 
    ${LLVM_LINK_OPTION})
    
else()
    target_link_libraries (vgl_wasm_runtime vmlib -lm -ldl -lpthread -lSDL2 
    ${LLVM_LINK_OPTION})

endif()


