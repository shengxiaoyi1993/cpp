# build

>本文档用于说明组播代码的编译和使用

## server编译及使用
```
cd ../../build/build_server/
mkdir build
cmake ../
make
./server_multibroadcast
```

## client编译及使用
```
cd ../../build/build_client/
mkdir build
cmake ../
make
./client_multibroadcast
```


## 测试
- server一开始启动就会向某一组播地址发送本地IP
- client会接受到向该组播地址发送的数据
  - 打开pc防火墙端口
  - 本地IP根据某一固定设备名获取，不同电脑可能不一样
  - 接收数据的 client应与server位于同一vlan(虚拟局域网)，但可不在同一子网；两个设备都必须连上路由器；一设备连上另一设备的wifi无法接收组播消息
  - 组播地址：224.0.0.0～224.0.0.255，224.0.0.0不做分配
