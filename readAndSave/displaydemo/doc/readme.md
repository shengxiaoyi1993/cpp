# readme

## 说明
- 该程序在嵌入式设备中使用，请确保设备中预安装了gtk库
- 该程序用于读取内存固定物理地址中的图片数据（raw格式），并显示出来
- 该程序需要与driver和相应的FPGA处理程序配合使用


## 编译
- cmake编译

```
//如果是非交叉编译可以先注释掉交叉编译的选项
[sxy@localhost build]$ mkdir build
[sxy@localhost build]$ cd build/
[sxy@localhost build]$ cmake ../
[sxy@localhost build]$ make

```

## 程序使用

- 程序运行
```

please input params as below:
./displaydemo [screen_width*screen_height]
note:     please run as root  
e.g.:     ./showImageInMem 1024*1024

```
- 程序将在启动后将FPGA寄存器置为可用状态
- 假设图片是RGB格式，且每个通道是unsigned char,大小与显示界面相同（若不相同仍显示图片的原大小，而不会进行任何缩放和裁剪）
- 图片显示的频率由FPGA上传的频率确定，每次接收到图片并显示后，会向驱动返回该图片已处理，此时相应的物理地址可以被使用
