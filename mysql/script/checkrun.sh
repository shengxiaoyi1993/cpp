#!/bin/bash
#ps -ef |grep zookeeper 这个就是看zookeeper的启动情况
#grep -v "grep" 是为了去掉查询 grep的那一条
#wc -l 是计数的

if [ $# -ne 1 ]; then
  echo "error:para not match!"
  echo "usage:$0 app"
  exit 1
fi


COUNT=`ps -ef |grep $1 |grep -v "grep"|grep -v $0 |wc -l`
if [ $COUNT -eq 0 ]; then
        echo no
else
        echo yes
fi
