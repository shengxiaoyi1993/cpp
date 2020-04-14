# build
>本文档用于说明服务器的部署过程及简单交互功能的实现

## 0. 部署lighttpd 

### 0.0 准备
- 下载 lighttpd-1.4.55.tar.gz 到resource目录下
```
内网：ftp://pub:9900@192.168.1.238/lib/lighttpd-1.4.55.tar.gz
```
### 0.1 编译过程
```
//假设文档所在路径为起始路径
cd ../../resources/
//编译服务器
./build_lighttpd.sh build 
```
### 0.2 修改配置

- 修改`web_server/resources/lighttpd_bin/config/ighttpd.conf`

1）将16行至20行修改为如下褐色加粗字体所示：
```
var.log_root    = "/opt/web/lighttpd-1.4.30-x86/log"
var.server_root = "/opt/web/lighttpd-1.4.30-x86"
var.state_dir   = "/opt/web/lighttpd-1.4.30-x86"
var.home_dir    = "/opt/web/lighttpd-1.4.30-x86"
var.conf_dir    = "/opt/web/lighttpd-1.4.30-x86/config"
```
 2）将61行和93行修改为如下褐色加粗字体所示：
 ```
var.cache_dir   = server_root + "/cache"
server.use-ipv6 = "disable"
 ```
3）将104和105行注释掉，如下所示：
```
#server.username  = "lighttpd"
#server.groupname = "lighttpd"
```
4）将115行修改为如下褐色加粗字体所示：
```
server.document-root = server_root + "/webpages"
```
5）将127行注释掉，如下所示：
```
#server.pid-file = state_dir + "/lighttpd.pid"
```
6）如果不需要查看错误日志文件，可以将141行注释掉，如下所示：
```
#server.errorlog             = log_root + "/error.log"
```
7）将152行、158行、191行注释掉，如下所示：
```
#include "conf.d/access_log.conf"
#include "conf.d/debug.conf"
#server.network-backend = "linux-sendfile"
```
8）根据系统资源设置207行和225行的数值，本系统的设置分别如下褐色加粗字体所示：
```
server.max-fds = 256
server.max-connections = 128
```
9）将314至316行注释掉，如下所示：
```
#$HTTP["url"] =~ "\.pdf$" {
#  server.range-requests = "disable"
#}
```
10）将373行修改为如下褐色加粗字体所示：
```
server.upload-dirs = ( "/opt/web/lighttpd-1.4.30-x86/upload" )
```
- 修改`web_server/resources/lighttpd_bin/config/modules.conf`


1）找到43行，将光标定位到逗号后面，回车，插入如下内容：
```
"mod_alias",
```
2）使能CGI模块，将138行的注释符去掉，如下所示：
```
include "conf.d/cgi.conf"
```

- 修改`web_server/resources/lighttpd_bin/config/conf.d/cgi.conf`文件

1）将15至19行这一段配置修改如下：
原文内容：
```
cgi.assign                 = ( ".pl"  => "/usr/bin/perl",
                               ".cgi" => "/usr/bin/perl",
                               ".rb"  => "/usr/bin/ruby",
                               ".erb" => "/usr/bin/eruby",
                               ".py"  => "/usr/bin/python" )
```
更改后：
```
cgi.assign = (".cgi" => "")
#cgi.assign                 = ( ".pl"  => "/usr/bin/perl",
#                               ".cgi" => "/usr/bin/perl",
#                               ".rb"  => "/usr/bin/ruby",
#                               ".erb" => "/usr/bin/eruby",
#                               ".py"  => "/usr/bin/python" )
```
2）将28行的注释符去掉，如下所示：
```
alias.url += ( "/cgi-bin" => server_root + "/cgi-bin" )
```

### 0.3 运行服务器
- 启动服务器
```
cd web_server/resources
./build_lighttpd.sh launch
//此时服务器已正常启动
```
- 测试服务器
  - 创建一空白文档，在文档中输入如下HTML代码,将文档保存为index.html，并复制到安装目录中的webpages文件夹里面
  - 在浏览器中输入本机的IP即能访问到该网页，注意不同电脑访问时注意关闭防火墙


```

<html>
<head>
<meta http-equiv="Content-Type" content="text/html; charset=UTF-8">
<title>lighttpd测试</title>
</head>
<body>
<p>轻量级web服务器lighttpd的编译及配置（for x86-linux）</p>
<hr>
<p>测试页面</p>
</body>
</html>
```



### 0.4 注

- 编译websocket，有与之配套的websocket在github上下载，同时包含了一个lighttpd源码，但是版本比较旧1.4.33(现在1.5.55)，六年前就停止更新了。