# Portable



## 1 usage

### 1.1 Fill data
- loadFromFile
- newly generate

### 1.2 Data opertation
- do some operation to data

### 1.3 Output
- share the data to another module
- save class to local file
- save data to pnm image

### 1.4 faq
- correct format of Head
- when magic_number is not power of 2,how to form the Data
- if this is multi picture
- how to save data: pointer of data and type  
- when convert to other type should give src_type and dst_type
  - P1=P4 P2=P5 P3=P6
  - data is saved in (unsigned short*) pointer with type
  - when convert to certain type, from the data with BinaryData ,
  then convert to file

## 2 basic module
- Head
  - magic_number
  - width
  - height
  - size
- Data
  - binary
    - rgbrgb...
  - ascii
    - r g b r g b...


## 3 design
### 3.1 class

```cpp
enum MagicNumber{
  MagicNumber_p1=1,
  MagicNumber_p2,
  MagicNumber_p3,
  MagicNumber_p4,
  MagicNumber_p5,
  MagicNumber_p6
};


class PNM{
  MagicNumber      _magic_number;
  unsigned int     _width;
  unsigned int     _height;
  unsigned short   _bits;
  unsigned short*  _data;
  //===============func================//
  int loadFromFile(const string & v_filepath);
  int saveToFile(const string & v_filepath,MagicNumber v_type);
  static int saveDataToFile(const string & v_filepath,
                            MagicNumber v_type,
                            unsigned short * v_pdata
                            unsigned int _width,
                            unsigned int _height,
                            unsigned int _bits
                          );

};
```


### 3.2 realization

- loadFromFile

```
- readHead
  - read as ascii file
  - search Whitespace (blanks, TABs, CRs, LFs)
  - get Head
  - get next until all info get
    - judge if comments
      - Y:continue;
      - N:get info
- judge data format
  - if next file should be binary file then convert the content to binary file
  - binary:getbinarydata
  - ascii :getasciidata
```
- getbinarydata

```
- get bits per pix(1 or 2)
- load data
- save to _data

```
- getasciidata

```shell
- formatted read data and save to _data
```
- saveToFile

```shell
- get_magic_number
- openFile
- saveHead
- malloc
- convertData
- saveDataToFile
```

## Note
-  ascii Code of blanks(0x20), TABs(0x09), CRs(0x0D), LFs(0x0A),#(0x23)
