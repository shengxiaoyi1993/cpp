# build

> 本文档用于说明onvif代码的构建编译
>
> 对于一般使用，在`../src/onvif/`文件夹下已有编译好的代码，可以直接用于c/c++编程，在Windows下编译运行正常，在centos下安装必要的库后编译运行正常

## onvif代码框架生成

> 本文档中叙述用脚本生成代码框架的方法，详细方法见`../design/design.md`

```
//以本文档所在目录作为起点
cd ../../resources/
chmod +x build_onvif.sh
./build_onvif.sh start
// 1、修改onvif.h头文件，加入#import "wsse.h"
// 2、将 OnvifFramework\gsoap-2.8\gsoap\import路径下的wsa5.h中的SOAP_ENV__Fault结构体注释掉或改为其他名字，如SOAP_ENV__Fault_alex
./build_onvif.sh continue
// 至此onvif框架代码保存在：OnvifFrameWork/level1/level2/FrameworkSource/
```

## onvif 封装接口编译及测试

```
//本文档所在目录作为起点
cp ../../resources/OnvifFrameWork/level1/level2/FrameworkSource* ../../src/onvif
cd ../../build/
mkdir build
cd build 
cmake ../
make
//至此：测试demo运行，并逐个输出监测到的设备地址
```

## onvif 封装接口

- 相关内容见`../manuals/manuals.md`