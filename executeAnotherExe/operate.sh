#! /bin/bash
# Author: sxy                                  // 指定作者
# Date：2020-5-15                              // 指定日期
# Version：0.0.0                               // 指定版本
# Description：some operations of project      // 描述脚本的功能
echo "para number:"$#

# to clean the dir of compilation
OPERATE_CLEAN="clean"
# to genarate executable file
OPERATE_BUILD="build"
# to genarate executable file and run
OPERATE_TEST="test"



if [[ $# -lt 1 ]]; then
  echo " Too few parameters "
elif [[ $# -gt 1 ]]; then
  echo " Too many parameters "
else
  echo "parameters:"$1
  echo "start to conclude..."
  echo "........."
fi

if [[ $1 == ${OPERATE_CLEAN} ]]; then
  echo "no " ${OPERATE_CLEAN}
elif [[ $1 == ${OPERATE_BUILD} ]]; then
  cd build
  chmod +x build.sh
  ./build.sh
  cd ../
  echo "succeed to" ${OPERATE_BUILD}

elif [[ $1 == ${OPERATE_TEST} ]]; then
  cd build
  chmod +x build.sh
  ./build.sh
  cd ../
  echo "..."
  echo "test output :"
  echo "<<"
  cd bin/
  ./normalapp
  ./cycleapp
  echo ">>"
  echo "test output "

  echo "succeed to " ${OPERATE_TEST}
else
  echo ">>error:parameters wrong!"
fi



unset OPERATE_CLEAN
unset OPERATE_BUILD
unset OPERATE_TEST
echo "........."
echo "conclude end."
