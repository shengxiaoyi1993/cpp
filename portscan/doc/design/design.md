# design

>本项目目的是为了解决程序启动时对防火墙允许的端口进行配置
## 目标
- 发现本机中防火墙开放的端口
- 控制防火墙对某个端口进行开放或禁止
- win和linux环境下均可以进行设置

## 控制
>- 由于没有找到可用的库，因此采用命令行操作的方式进行端口的配置，该项目对命令行进行了封装，使之方便被调用
>- 由于windows和linux下的命令有所不同，因此各写了一组接口.
>- 编写跨平台的软件可参照`main.cpp`和`CMakeLists.txt`进行设置

### win
- 检测一个端口是否被防火墙允许
- 使一个端口被防火墙允许
- 使一个端口不被防火墙允许
- 重启防火墙（每次进行设置后，需要重启防火墙使之生效）

### linux
- 将一个端口添加到防火墙规则列表（加入默认开启）
- 将一个防火墙规则列表中的端口开启/或者关闭
- 删除防火墙规则列表中的端口
