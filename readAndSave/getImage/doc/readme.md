# readme

## 说明
- 该程序用于读取本地数据(raw格式)，并将图片转换成jpg格式，保存成本地文件
- 该程序在本机使用

## 编译

```
[sxy@localhost src]$ gcc getImage.c -o getimage `pkg-config --libs --cflags gtk+-2.0`
```

## 程序使用


```
[sxy@localhost src]$ ./getimage

>>Error:param not match

please input params as below:
./readmem  [inputfile] [height] [width] [outputfile]
inputfile: inputfile of raw data
e.g.:      ./getimage ~/Share/tftp/imagebuffer.txt 4096 4096 devimage.jpg

```

```
//获取设备中的raw数据文件
[sxy@localhost src]$ ./getimage ~/Share/tftp/imagebuffer.txt 4096 4096 devimage.jpg
```
