#! /bin/bash
# Author: sxy                                  // 指定作者
# Date：2020-7-20                               // 指定日期
# Version：0.0.0                               // 指定版本
# Description：some operations of project      // 描述脚本的功能
echo "para number:"$#

# to clean the dir of compilation
OPERATE_CLEAN="clean"
# to genarate executable file
OPERATE_BUILD="build"
# to genarate executable file and run
OPERATE_TEST="test"
# to genarate executable file and run
OPERATE_REPLACE="replace"

NUMBER_PARA=3

if [[ $# -eq ${NUMBER_PARA} ]]; then
  echo "parameters:"$1
  echo "start to conclude..."
  echo "........."
else
  echo "failed"
  echo "parameters not match!"
  echo "usage: "$0" [option] [name_executable] [root_tftp]"
  echo "e.g. "

fi

name_executable="driver"
root_tftp="$3"
echo "root_tftp: "${root_tftp}


if [[ $1 == ${OPERATE_CLEAN} ]]; then
  rm build/ -rf
  echo "[succeed] to " ${OPERATE_CLEAN}

elif [[ $1 == ${OPERATE_BUILD} ]]; then
  rm build/ -rf
  mkdir build
  cd build/
  cmake ../ -G "Unix Makefiles"
  make
  echo "[succeed] to " ${OPERATE_BUILD}

elif [[ $1 == ${OPERATE_TEST} ]]; then
  rm build/ -rf
  mkdir build
  cd build/
  cmake ../ -G "Unix Makefiles"
  make
  echo "..."
  echo "test output :"
  echo "<<"
  `./${name_executable}`
  echo ">>"
  echo "test output "
  echo "[succeed] to " ${OPERATE_TEST}

elif [[ $1 == ${OPERATE_REPLACE} ]]; then
  rm build/ -rf
  mkdir build
  cd build/
  cmake ../ -G "Unix Makefiles"
  make
  `cp ${name_executable} ${root_tftp}`
  rm build/ -rf
  echo "[succeed] ${name_executable} copy to ${root_tftp}"
  cd ../

else
  echo ">>error:parameters wrong!"
fi



unset OPERATE_CLEAN
unset OPERATE_BUILD
unset OPERATE_TEST
echo "........."
echo "conclude end."
