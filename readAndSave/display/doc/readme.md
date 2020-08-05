# readme

## 说明
- 硬件环境：嵌入式系统
- 该程序在嵌入式设备中使用，请确保设备中预安装了gtk/gtk-devel库
- 该程序用于读取内存固定物理地址中的图片数据（raw格式），并显示出来


## 目标
- 15帧/s，需要查看trd的设计
- 等比例显示，截取需要显示的部分


## 编译
- 命令行编译

```
[sxy@localhost src]$ gcc getImage.c -o getimage `pkg-config --libs --cflags gtk+-2.0`
```

- cmake编译

```
//如果是非交叉编译可以先注释掉交叉编译的选项
[sxy@localhost build]$ mkdir build
[sxy@localhost build]$ cd build/
[sxy@localhost build]$ cmake ../
[sxy@localhost build]$ make

```

## 程序使用

```

please input params as below:
./showImageInMem  [addr] [height] [width] [interval] [screen_width*screen_height]
interval  get image per interval ms  
note:     please run as root  
e.g.:     ./showImageInMem 0x60000000 4096 4096 100 1024*1024


```

## 结论
- 由于将原始的图片数据进行显示会耗费大量的资源，若想达到15frame/s的播放速度，`内存中获取的图片就应该是rgb的图片，且大小恰好是1920\*1080`
