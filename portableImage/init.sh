#! /bin/bash
# Author: sxy                                  // 指定作者
# Date：2020-8-20                               // 指定日期
# Version：0.0.0                               // 指定版本
# Description： init project of portableimage ,copy basic lib to lib // 描述脚本的功能
# usage: bash -e init.sh


LIB_COPY="lib"
LIB_COPY_COMMON=${LIB_COPY}/common

rm ${LIB_COPY} -rf
mkdir ${LIB_COPY}
mkdir ${LIB_COPY_COMMON}
cp ../common/src/cpp/string_manipulation.* ${LIB_COPY_COMMON}
tree ${LIB_COPY}
