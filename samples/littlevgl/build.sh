#
# Copyright (C) 2019 Intel Corporation.  All rights reserved.
# SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
#

#!/bin/bash

PROJECT_DIR=$PWD
WAMR_DIR=${PWD}/../../deps/wasm-micro-runtime
WAMR_APP_FRAMEWORK_DIR=${PWD}/../..
OUT_DIR=${PWD}/out
BUILD_DIR=${PWD}/build
LV_CFG_PATH=${PROJECT_DIR}/lv_config

if [ -z $KW_BUILD ] || [ -z $KW_OUT_FILE ];then
    echo "Local Build Env"
    cmakewrap="cmake"
    makewrap="make -j$(nproc)"
else
    echo "Klocwork Build Env"
    cmakewrap="cmake -DCMAKE_BUILD_TYPE=Debug"
    makewrap="kwinject -o $KW_OUT_FILE make -j$(nproc)"
fi

if [ ! -d $BUILD_DIR ]; then
    mkdir ${BUILD_DIR}
fi

######################################################################
# wasm-micro-runtime 다운로드 시작
######################################################################

echo "#####################clone dependent projects"
cd ${WAMR_APP_FRAMEWORK_DIR}/deps
if [ ! -d "wasm-micro-runtime" ] && [ "$WAMR" != "0" ]; then
        echo "git pull wasm-micro-runtime..."
        git clone https://github.com/wjdrud2532/wasm-micro-runtime.git
        [ $? -eq 0 ] || exit $?
fi
if [ ! -d "lvgl" ] && [ "$LVGL" != "0" ]; then
        echo "git pull lvgl..."
        git clone https://github.com/lvgl/lvgl.git --branch v6.0.1
        [ $? -eq 0 ] || exit $?

        ../app-framework/wgl/app/prepare_headers.sh
fi
if [ ! -d "lv_drivers" ] && [ "$LV_DRIVERS" != "0" ]; then
        echo "git pull lv_drivers..."
        git clone https://github.com/lvgl/lv_drivers.git --branch v6.0.1
        [ $? -eq 0 ] || exit $?
fi
# ./download.sh

rm -rf ${OUT_DIR}
mkdir ${OUT_DIR}

cd ${BUILD_DIR}
if [ ! -d "lvgl" ]; then
        echo "starting download lvgl for v5.3 ..."
        git clone https://github.com/lvgl/lvgl.git --branch v5.3
        if [ $? != 0 ];then
            echo "download lvgl repo failed: $?\n"
            exit 2
        fi
fi
######################################################################
# wasm-micro-runtime 다운로드 완료

# 아키텍처에 필요한 패키지 다운로드 시작
######################################################################

sudo apt update

architecture=$(uname -m)

if [ "$architecture" = "aarch64" ]; then
    echo "aarch64 architecture detected. Performing aarch64-specific tasks..."
    
    #install packages
    sudo apt update && \
    sudo add-apt-repository -y main universe restricted multiverse && \
    sudo apt update && sudo apt install -y build-essential libssl-dev make pkg-config \
     ninja-build python3-pip vim libsdl2-dev

    if ! command -v cmake &> /dev/null; then
        #install cmake 3.30.0 (because need cmake 3.29 or higher)
        wget https://github.com/Kitware/CMake/releases/download/v3.30.0/cmake-3.30.0.tar.gz
        tar -zxvf cmake-3.30.0.tar.gz
        cd cmake-3.30.0
        ./bootstrap
        make -j$(nproc)
        sudo make install
    fi

    if [ ! -d "/opt/wasi-sdk" ]; then
        #install wasi-sdk
        sudo wget https://github.com/WebAssembly/wasi-sdk/releases/download/wasi-sdk-23/wasi-sdk-23.0-arm64-linux.tar.gz
        sudo tar -xf wasi-sdk-23.0-arm64-linux.tar.gz -C /opt/
        sudo mv /opt/wasi-sdk-23.0-arm64-linux /opt/wasi-sdk
    fi
    
elif [ "$architecture" = "x86_64" ]; then
    echo "x86_64 architecture detected. Performing x86_64-specific tasks..."

    #install packages
    sudo apt update && sudo apt install -y apt-transport-https apt-utils build-essential \
     ca-certificates curl g++-multilib git gnupg libgcc-9-dev lib32gcc-9-dev lsb-release \
     ninja-build ocaml ocamlbuild python2.7 python3-pip software-properties-common tree \
     tzdata unzip valgrind vim wget zip cmake pkg-config \
     libsdl2-dev --no-install-recommends

    #install wasi-sdk
    if [ ! -d "/opt/wasi-sdk" ]; then
        sudo wget https://github.com/WebAssembly/wasi-sdk/releases/download/wasi-sdk-16/wasi-sdk-16.0-linux.tar.gz 
        sudo tar -xf wasi-sdk-16.0-linux.tar.gz -C /opt/
        sudo mv /opt/wasi-sdk-16.0 /opt/wasi-sdk
    fi

else
    echo "Unknown architecture detected. Exiting..."
    exit 1
fi
######################################################################
# 아키텍처에 필요한 패키지 다운로드 완료

# JIT 실행여부 확인 및 LLVM 빌드 시작
######################################################################

config_file="${PWD}/../wamr_config_littlevgl.cmake"
target_value=$(grep 'WAMR_BUILD_TARGET' "$config_file" | sed -E 's/.*\s+([^\)]+)\).*/\1/')
jit_value=$(grep 'WAMR_BUILD_JIT' "$config_file" | sed -E 's/.*\s+([^\)]+)\).*/\1/')

if [ "$jit_value" -eq 1 ]; then
    echo "JIT is enbled, need llvm build!"
    echo ""##################### LLVM build start! "#####################"
    echo " WAMR_BUILD_TARGET:$target_value";
        cd ${WAMR_DIR}/wamr-compiler
        ./build_llvm.sh
    echo ""##################### LLVM build complete "#####################"
fi

######################################################################
# LLVM 빌드 완료

# wamk-sdk 빌드 시작
######################################################################

echo "##################### 0. build wamr-sdk littlevgl start#####################"

cd ${WAMR_APP_FRAMEWORK_DIR}/wamr-sdk
./build_sdk.sh -n littlevgl -x ${PROJECT_DIR}/wamr_config_littlevgl.cmake -e ${LV_CFG_PATH} -c
[ $? -eq 0 ] || exit $?
echo "#####################build wamr-sdk littlevgl success"

echo -e "\n\n"
echo "##################### 1. build native-ui-app start#####################"
cd $BUILD_DIR
mkdir -p vgl-native-ui-app
cd vgl-native-ui-app
$cmakewrap ${PROJECT_DIR}/vgl-native-ui-app
$makewrap
if [ $? != 0 ];then
    echo "BUILD_FAIL native-ui-app $?\n"
    exit 2
fi
echo $PWD
cp  vgl_native_ui_app ${OUT_DIR}
echo "#####################build native-ui-app success"

echo -e "\n\n"
echo "##################### 2. build littlevgl wasm runtime start#####################"
cd $BUILD_DIR
mkdir -p vgl-wasm-runtime
cd vgl-wasm-runtime
$cmakewrap ${PROJECT_DIR}/vgl-wasm-runtime
$makewrap
[ $? -eq 0 ] || exit $?
cp vgl_wasm_runtime ${OUT_DIR}/

echo "##################### build littlevgl wasm runtime end#####################"

echo -e "\n\n"
echo "#####################build host-tool"
cd $BUILD_DIR
mkdir -p host-tool
cd host-tool
$cmakewrap ${PROJECT_DIR}/../../test-tools/host-tool
$makewrap
if [ $? != 0 ];then
        echo "BUILD_FAIL host tool exit as $?\n"
        exit 2
fi
cp host_tool ${OUT_DIR}
echo "#####################build host-tool success"

echo -e "\n\n"
echo "##################### 3. build wasm ui app start#####################"
cd ${PROJECT_DIR}/wasm-apps
if [ ! -d "${PROJECT_DIR}/wasm-apps/lvgl" ]; then
    if [ -d "$BUILD_DIR/vgl-native-ui-app/lvgl" ]; then
        cp -fr $BUILD_DIR/vgl-native-ui-app/lvgl ${PROJECT_DIR}/wasm-apps
    fi
fi
./build_wasm_app.sh
mv *.wasm ${OUT_DIR}/

echo "#####################  build wasm ui app end#####################"
