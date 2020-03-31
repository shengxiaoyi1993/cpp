# build

## 编译及使用

```
cd ../../build/
mkdir build
cd build
cmake ../
make
./portscan
```

## 说明
- cmake文件及main.cpp已对不同平台的编译进行了设置
- 运行可执行文件时
  - linux 平台会自动要求输入用户名密码
  - 但是windows平台需要以administer权限运行命令行，否则相关设置不会成功


- linux执行结果
```
port is not allowed
add port succeed
restart firewall succeed
port allow
port del succeed
restart firewall succeed
port is not allowed

```

- windows执行结果
```
addPortToFirewall succeed                                                                        setPortToFirewall able succeed                                                                        setPortToFirewall disable succeed                                                                        delPortToFirewall succeed 
```
