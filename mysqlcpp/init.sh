#! /bin/bash
# Author: sxy                                  // 指定作者
# Date：2020-8-21                               // 指定日期
# Version：0.0.0                               // 指定版本
# Description： init project of image_converter ,copy basic lib to lib // 描述脚本的功能
# usage: bash -e init.sh

echo "//=======================INIT  START=========================//"

LIB_COPY="lib_copy"
LIB_COPY_LOG=${LIB_COPY}/log
LIB_COPY_CJSON=${LIB_COPY}/cjson


rm ${LIB_COPY} -rf
mkdir ${LIB_COPY}


mkdir ${LIB_COPY_LOG}
cp ../log/src/syslogger/syslogger.* ${LIB_COPY_LOG}
echo "[succeed]:copy ${LIB_COPY_LOG}"

mkdir ${LIB_COPY_CJSON}
cp ../cjson/src/cjson/cJSON.* ${LIB_COPY_CJSON}
echo "[succeed]:copy ${LIB_COPY_CJSON}"


echo "[tree]   :"
tree ${LIB_COPY}



echo "//=======================INIT  END=========================//"

mkdr lib 
cp resources/mysql-connector-c++-8.0.20-lib.tar.gz lib
tar -vxf mysql-connector-c++-8.0.20-lib.tar.gz
rm mysql-connector-c++-8.0.20-lib.tar.gz
