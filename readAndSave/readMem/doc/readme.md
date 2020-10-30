# readme

## 1. 说明
- 该程序用于读取内存物理地址上的若干数据并保存在指定文件

## 2. 编译

### 2.1. 本地编译

```
[sxy@localhost src]$ gcc readmem.c -o readmem
```

### 2.2. 交叉编译

```
//初始化petalinux编译工具如下，路径需要更换为petalinux的本地安装路径
[sxy@localhost src]$ source ~/Software/petalinux/settings.sh
[sxy@localhost src]$ aarch64-linux-gnu-gcc readmem.c -o readmem

```

## 3. 程序使用

```
please input params as below:
./readmem  [addr] [height] [width] [outputfile]
note:   please run as root
e.g.:   ./readmem 0x60000000 4096 4096 imagebuffer.txt
```

### 3.1. 本地使用

```
//使用root权限运行该程序
[root@localhost src]# sudo ./readmem 0x60000000 4096 4096 imagebuffer.txt
```

### 3.2. 嵌入式设备使用

```
- 交叉编译得到程序，并放到本机的tftp目录下
- telnet至设备
[sxy@localhost ~]$ telnet 192.168.1.136
- tftp从本机获取该程序
root@xilinx-zcu102-2018_3:~# tftp -gr readmem 192.168.1.126
root@xilinx-zcu102-2018_3:~# chmod +x readmem
root@xilinx-zcu102-2018_3:~# ./readmem 0x60000000 4096 4096 imagebuffer.txt

```
