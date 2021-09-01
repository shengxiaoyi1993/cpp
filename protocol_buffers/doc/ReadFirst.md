# readme 

## from release 
```
wget https://github.com/protocolbuffers/protobuf/archive/refs/tags/v3.17.3.zip
```

## from clone 

 1007  [2021-08-31 20:14:32]$ git clone https://github.com/protocolbuffers/protobuf.git
 1008  [2021-08-31 20:18:19]$ cd protobuf
 1009  [2021-08-31 20:18:28]$ git submodule update --init --recursive
 1010  [2021-08-31 20:20:09]$ ./autogen.sh
 1017  [2021-08-31 20:41:22]$ ./configure --prefix=/home/sxy/Software/protobuf
 1018  [2021-08-31 20:41:39]$ make
 1019  [2021-08-31 20:41:44]$ make install

```
[sxy@DESKTOP-SXY protobuf]$ tree -L 3
.
├── bin
│   └── protoc
├── include
│   └── google
│       └── protobuf
└── lib
    ├── libprotobuf.a
    ├── libprotobuf.la
    ├── libprotobuf-lite.a
    ├── libprotobuf-lite.la
    ├── libprotobuf-lite.so -> libprotobuf-lite.so.28.0.3
    ├── libprotobuf-lite.so.28 -> libprotobuf-lite.so.28.0.3
    ├── libprotobuf-lite.so.28.0.3
    ├── libprotobuf.so -> libprotobuf.so.28.0.3
    ├── libprotobuf.so.28 -> libprotobuf.so.28.0.3
    ├── libprotobuf.so.28.0.3
    ├── libprotoc.a
    ├── libprotoc.la
    ├── libprotoc.so -> libprotoc.so.28.0.3
    ├── libprotoc.so.28 -> libprotoc.so.28.0.3
    ├── libprotoc.so.28.0.3
    └── pkgconfig
        ├── protobuf-lite.pc
        └── protobuf.pc

6 directories, 18 files


- build up project according to this project 

```
 1063  [2021-09-01 09:14:36]$ cd ../build/
 1064  [2021-09-01 09:14:38]$ mkdir build
 1065  [2021-09-01 09:14:41]$ cd build/
 1066  [2021-09-01 09:14:43]$ cmake ../
 1067  [2021-09-01 09:14:46]$ make
 1068  [2021-09-01 09:14:59]$ ./myproj myaddr_book.bin
 1069  [2021-09-01 09:15:18]$ ls
 1070  [2021-09-01 09:15:31]$ cat myaddr_book.bin 
 1071  [2021-09-01 09:15:36]$ history
```