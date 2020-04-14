# web_server

> 本文用于说明web_server的应用场景，原理，实现过程等



## 简介

- Web服务器接收到一个HTTP请求(request)，会返回一个HTTP响应(response)
- 响应(response)一个静态页面或图片，进行页面跳转(redirect)，或者把动态响应(dynamic response)的产生委托(delegate)给一些其它的程序例如CGI脚本，JSP(JavaServer Pages)脚本，servlets，ASP(Active Server Pages)脚本，服务器端(server-side)JavaScript，或者一些其它的服务器端(server-side)技术



## 举例

- Boa 
- Thttpd
- lighttpd 
- shttpd

## 技术

### 静态

### 动态

#### CGI及SSI

- 将预先编译好的 CGI/SGI 程序保存到服务器端，当服务器响应客户端请求时可以被调用以处理 HTML 文档
- 每当客户端程序有一个请求时，Web 服务器都需要创建一个新的 CGI 进程，并通过环境变量和标准输入来将生成响应报文所必须的信息传递 CGI 程序。这样的操作是很耗费时间的，同样也很耗费资源
- CGI 进程和 Web 服务器是不同的进程，所以二者就很难进行交互

#### 服务器端动态语言（PHP）

- 由 C 写成的 CGI 二进制库集合
- 将 PHP 程序嵌入到 HTML 文档中去执行，执行效率比完全生成 HTML 标记的 CGI 程序要高

#### Active Server Pages（ASP）

- Web 服务器上的HTML页面可以包含嵌入代码的片段（通常是VBScript或JScript-尽管几乎可以使用任何语言）。在将页面发送到客户端之前，Web服务器将读取并执行此代码

#### Server-side JavaScript（SSJS）

- 允许将代码片段嵌入到 HTML 页面中以生成动态 Web 内容
- 使用 JavaScript 作为脚本语言
- 可以预编译网页以提高性能

#### Java Server pages（JSP）

- 允许在 HTML 中嵌入 Java 代码





```
https://www.cnblogs.com/backwords/p/9376578.html
```

