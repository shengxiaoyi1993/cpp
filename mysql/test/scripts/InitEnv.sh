#!/usr/bin/bash
#author:sxy
#func  :init the environment of this project
#      include copy log lib. to this project

echo -e "\usage: bash -e InitEnv.sh\n"
read -p "continue (y/n)" val_continue
if [ ${val_continue} == "n" ]; then
  exit 1
fi

#copy the log file to this project from cpp/clog/src/
echo -e "\n--------------------copy clog--------------------\n"
mkdir ../lib/clog -p && cp ../../../clog/src/log.* ../lib/clog/
echo -e "\n------------------copy clog end------------------\n"
