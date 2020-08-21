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
```shell
- ppm  
  get rgb data
- pgm(输出单通道数据)
  get gray data or single channel of data
- jpeg（8位）
- raw（可输出）
  - get raw data
- output_file
  - get
```

- 从rgb数据获取图片，8位，10位，12位
```
- getInfo magic_number rows cols bits
- getData from ascii or binary
```

## design
- loadfrom file
- all type of data is saved in same pointer(with one flag to identify the type
  ,as for the single type of data )


## plan

- analyse all the import data type
- get inbuild buffer frame to save data
  - some selection
    - same pointer as rgb (when data is gray or binary is different to save)
    - different data type with flag_id
    - dynamic numbrt of types to save ,record all datatype
    - similar method with opencv or Qt, with servel types of flag to fix the ImageType
      - channels
      - type (rgb gray yuv)
      - valid_bits (<=16)
- complete process to output data

```shell
- ImageBufer
  - channels
  - type (rgb gray yuv)
  - valid_bits (<=16)
```
- import support PNM
- export suport PNM
- add test case
- support import raw
- support export raw
- add test case
- support import outputfile
- support export outputfile
- add test case
- support import jpeg
- support export jpeg
- add test case
- complete test
- complete document
- complete debug
