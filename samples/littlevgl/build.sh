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

echo "#####################clone dependent projects"
cd ${WAMR_APP_FRAMEWORK_DIR}/deps
./download.sh

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

echo "##################### 0. build wamr-sdk littlevgl start#####################"
cd ${WAMR_APP_FRAMEWORK_DIR}/wamr-sdk
./build_sdk.sh -n littlevgl -x ${PROJECT_DIR}/wamr_config_littlevgl.cmake -e ${LV_CFG_PATH} -c
[ $? -eq 0 ] || exit $?
echo "#####################build wamr-sdk littlevgl success"



# wamr_config_littlevgl.cmake 파일 경로 설정
config_file="${PWD}/../wamr_config_littlevgl.cmake"

# wamr_config_littlevgl.cmake 파일에서 WAMR_BUILD_TARGET 값을 추출합니다.
target_value=$(grep 'WAMR_BUILD_TARGET' "$config_file" | sed -E 's/.*\s+([^\)]+)\).*/\1/')
jit_value=$(grep 'WAMR_BUILD_JIT' "$config_file" | sed -E 's/.*\s+([^\)]+)\).*/\1/')

if [ "$jit_value" -eq 1 ]; then

    echo "##################### 0.5. build LLVM start#####################"
    echo "JIT is enbled, need llvm build!"
    echo " WAMR_BUILD_TARGET:$target_value";

    # rm -rf ${WAMR_DIR}/core/deps/llvm/build

    #target 확인 
    if [ "$target_value" = "X86_64" ]; then

        echo "##################### X86_64 target is selected, LLVM build start #####################"
        cp ${PROJECT_DIR}/llvm_build_script_aarch64/build_llvm_x86_64.py ${WAMR_DIR}/build-scripts/build_llvm_x86_64.py
        cp ${PROJECT_DIR}/llvm_build_script_aarch64/build_llvm_x86_64.sh ${WAMR_DIR}/build-scripts/build_llvm_x86_64.sh
        cd ${WAMR_DIR}/wamr-compiler
        ./build_llvm_x86_64.sh
    
    elif [ "$target_value" = "AARCH64" ]; then

        echo " ##################### AARCH64 target is selected, LLVM build start #####################"
        file_path="/home/gcc-linaro-14.0.0-2023.06-x86_64_aarch64-linux-gnu.tar.xz"
    
        if [ -f "$file_path" ]; then
            echo " ##################### linaro-14 exists"
        else
            echo " ##################### linaro-14 deos not exists, download linaro-14"
            cd /home
            wget https://snapshots.linaro.org/gnu-toolchain/14.0-2023.06-1/aarch64-linux-gnu/gcc-linaro-14.0.0-2023.06-x86_64_aarch64-linux-gnu.tar.xz
            tar -xvf gcc-linaro-14.0.0-2023.06-x86_64_aarch64-linux-gnu.tar.xz -C /home
            echo " ##################### linaro-14 download complete"
        fi

        cp ${PROJECT_DIR}/llvm_build_script_aarch64/build_llvm_aarch64.py ${WAMR_DIR}/build-scripts/build_llvm_aarch64.py
        cp ${PROJECT_DIR}/llvm_build_script_aarch64/build_llvm_aarch64.sh ${WAMR_DIR}/build-scripts/build_llvm_aarch64.sh
        cd ${WAMR_DIR}/wamr-compiler
        ./build_llvm_aarch64.sh

    else
        echo "WIP, not supported target"
    fi

    echo ""##################### LLVM build complete "#####################"
fi

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
