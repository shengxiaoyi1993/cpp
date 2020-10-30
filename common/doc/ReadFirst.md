# ReadFirst

- this project a gather of basic and widely used functions

## list
- basicio (none)
- string_manipulation
  - StringConverter:use to convert string from and to other type of data
  - BinaryData:
    - to append binary data when bits of data are not multiple of 8,and form them to binary buffer
    - two save direction is defined,this means you can fill the buffer from left or right
    - data is appended by a basic data type and number of valid bits



## run the test case
<has been test in centos

```
cd build
mkdir build
cd build
cmake ../
make
./example
```

## manual
- if you want use function in this project ,copy the `*.h`and `*.cpp` to the lib of target project
- It is suggested to modify file in this project and copy to target project again,other than modify in the target project directly
