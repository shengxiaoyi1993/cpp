# manuals

> 本文档用于说明onvif接口文档的使用

- 使用范围：
  - 本项目使用纯c编写，已在windows x64和centos 7.5测试通过
  - 接口仅封装了设备发现、视频流获取、截图获取、请求设备的网关等基础功能\
  - onvif框架代码未经裁剪，所以需要的功能可以相应拓展，但编译成的库文件较大

## 文件结构

  ```
src/
├── main.c
├── onvif
│   ├── dom.c
│   ├── dom.h
│   ├── duration.c
│   ├── duration.h
│   ├── mecevp.c
│   ├── mecevp.h
│   ├── smdevp.c
│   ├── smdevp.h
│   ├── soapC.c
│   ├── soapClient.c
│   ├── soapH.h
│   ├── soapStub.h
│   ├── stdsoap2.c
│   ├── stdsoap2.h
│   ├── threads.c
│   ├── threads.h
│   ├── wsa5.h
│   ├── wsaapi.c
│   ├── wsaapi.h
│   ├── wsdd.nsmap
│   ├── wsseapi.c
│   └── wsseapi.h
├── onvif_export.c
└── onvif_export.h

  ```

- onvif_export.h和onvif_export.c是封装后的onvif功能接口，每个接口都有详细的描述和使用方法
- src/onvif中是onvif仅soap转换生成的框架代码
- main.c中包含几个接口的测试代码，使用时可以参考