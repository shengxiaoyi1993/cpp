# design

## Introdoce

- image to buffer
- buffer to image

- imagetype
  - ppm
  - pgm(输出单通道数据)
  - jpeg（8位）
  - raw（可输出）
  - output_file

- buffertype
  - rgb
  - yuv

## module
- PortableP


## process
- 从PGM获取R，G，B分量，输入的数据可能是8位，10位，12位
- 从rgb数据获取图片，8位，10位，12位

```
- getInfo magic_number rows cols bits
- getData from ascii or binary
```
