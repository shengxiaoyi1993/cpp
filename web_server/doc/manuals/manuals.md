# manuals
>说明手册


## 0. 功能的实现

> 进行这一步前，确保网页已能正常访问，假设服务器IP为`192.168.0.124`

### 0.0 静态网页访问

- 服务器端

  ```
  见上
  ```

- 浏览器输入

  ```
  http://192.168.0.124/index.html
  ```

### 0.1 客户端与服务器信息交互

- 服务器端
```html
<html>
<body>
<h1>It works!</h1>
<h2>I am here!</h2>

<FORM ACTION="./cgi-bin/getpost.cgi" METHOD="get">
<INPUT TYPE="text" NAME="Text" VALUE="This is get operation">
<INPUT TYPE="submit" VALUE="Get">request will have response !</INPUT>
</FORM>
<BR>

<FORM ACTION="./cgi-bin/getpost.cgi" METHOD="post">
<INPUT TYPE="text" NAME="Text" VALUE="This is post operation">
<INPUT TYPE="submit" VALUE="Post"> post data will be saved !</INPUT>
</FORM>
<BR>

</body>
</html>

```


- cgi源文件
```c++
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#define MAXLEN 80

int main(void)
{
    long len;
    char *lenstr, poststr[80];
    printf("Content-Type:text/html\n\n");

    char *pRequestMethod;
    setvbuf(stdin, NULL, _IONBF, 0);     /*turn off stdin's cache*/

    pRequestMethod = getenv("REQUEST_METHOD");

    if (strcmp(pRequestMethod, "POST") == 0)
    {
        printf("<TITLE>This is Post operation</TITLE>\n");
        int i=0;

        lenstr = getenv("CONTENT_LENGTH");
        //if(lenstr == NULL || len > MAXLEN)

        if(lenstr == NULL)
        {
            printf("<P>Post form error");
        }
        else
        {
                len = atoi(lenstr);
                fgets(poststr, len + 1, stdin);
        }

        FILE *fp = NULL;
        fp = fopen("postdata.txt", "w+");
        if(fp==NULL){
          printf("%s","post data has not been saved !");
          return 0;
        }
        fprintf(fp, poststr);
        fclose(fp);
        printf("post data has been saved :%s",poststr);


    }
    if (strcmp(pRequestMethod, "GET") == 0)
    {
        printf("<TITLE>This is Get operation</TITLE>\n");
        char *qa;
        printf("<TITLE>The reault of Get is:\n</TITLE>\n");
        qa = getenv("QUERY_STRING");

        printf("server has received the request:%s",qa);

    }
    return 0;
}

```
- 浏览器输入
```
http://192.168.0.124/getpost.html
```


### 0.2 客户端调用服务端的cgi
- 见0.1
- cgi使用时需要进行编译,然后复制到cgi-bin目录下



### 0.3 浏览器部分数据更新
- 服务器端
```
<html>

<head>
  <script type="text/javascript" src="js/jquery-3.4.1.min.js"></script>
  <style>
    body {

      width: 100%;
    }

    p {
      width: 200;
      height: 200;
    }
  </style>
</head>

<body>
  <h1>Test update part of data~</h1>
  <input type="button" onclick="update()" value="updata" />
  push the button to update the data!
  </input>
  <br>
  <input id="ouput" type="text" value="old data" />
  </input>
</body>

<script language=javascript>
  function update() {
    $.ajax({
      type: "POST",
      url: "./cgi-bin/getdata.cgi",
      data: "hello world",
      dataType: "text",
      ContentType: "application/text; charset=utf-8",
      success: function(returnedData, status) {
        if (status == "success") {
          document.getElementById('ouput').value = returnedData;
          // alert(returnedData);
        }
      },
      error: function(msg) {
        // alert("访问失败："+ msg);
      }
    });
  }
</script>

</html>
```

- cgi源文件
```
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
 #include <unistd.h>
#define MAXLEN 80

int main(void)
{
    printf("%s","new data from server");
    return 0;
}

```
- 浏览器输入
```
http://192.168.0.124/test_ajax.html
```

### 0.4 浏览器显示图片流
- 服务器端
```
<html>

<head>
  <script type="text/javascript" src="js/jquery-3.4.1.min.js"></script>
</head>

<body>
  <h1>Test transport image </h1>
  <input type="button" onclick="start_stream(this)" value="start" />
  </input>
<br>
  <p id="demo">push the up button to start image stream</p>
</body>

<script language=javascript>
  function start_stream(obj) {
    var myvar = setInterval(testcgi, 20);
    obj.value = "get stream..."
  }

  function testcgi() {
    $.ajax({
      type: "POST",
      url: "./cgi-bin/getrandomimage.cgi",
      data: "hello world",
      dataType: "text",
      ContentType: "application/text; charset=utf-8",
      success: function(returnedData, status) {
        if (status == "success") {

          document.getElementById('demo').innerHTML = returnedData;
          // alert(returnedData);
        }
      },
      error: function(msg) {
        // alert("访问失败："+ msg);
      }
    });
  }
</script>

</html>

```
- cgi源文件
```
//gcc getrandomimage.c -o getrandomimage.cgi

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include<time.h>


int main(void)
{

    int i=0;
    time_t timer = time(NULL);
    int s=50;
    srand(timer);
    i=random();

    i%=4;

    if(i==0){
      printf(" <img id=\"imgframe\"  src=\"../1-1-0-0.jpg\" height=\"400\" width=\"400\"  />");

    }
    else  if(i==1){
      printf(" <img id=\"imgframe\"  src=\"../1-1-0-3.jpg\" height=\"400\" width=\"400\" />");

    }
    else  if(i==2){
      printf(" <img id=\"imgframe\"  src=\"../1-1-0-1.jpg\" height=\"400\" width=\"400\" />");

    }
    else  if(i==3){
    printf(" <img id=\"imgframe\"  src=\"../1-1-0-2.jpg\" height=\"400\" width=\"400\" />");

    }
    return 0;

}

```

- 浏览器输入
```
http://192.168.1.124/test_imagestream.html
```

### 0.5 鉴权功能
- 服务器端
```
<!DOCTYPE html>
<html>
    <head>
        <meta charset="UTF-8">
        <title>标题</title>
        <script type="text/javascript" src="js/jquery-3.4.1.min.js"></script>

        </style>
    </head>

    <body onkeydown="keyLogin()">

            <div class="register-content register-content_j">
                用户名<input id="loginName" type="text" placeholder="请输入用户名">
                密    码<input id="password" type="password" placeholder="请输入密码">
            </div>
            <input id="remember_password" type="checkbox" />记住密码
            <br>
            <input type="button" id="loginbutton" value="登陆" onclick="login()"></div>
            <br>
            <input type="button" id="reverse" value="reverse" onclick="getCookie()"></div>
            <br>

            <div class="reg-btn" id="login">?????</div>

        </div>
    </body>

    <script type="text/javascript">

            getCookie();

        // 回车键登陆
        function keyLogin(){
            if (event.keyCode==13){
                document.getElementById("login").click();
            }
        };

        // 用户名密码登陆
        function login(){

            if($("#loginName").val() == ""){
                alert("请输入用户名");
                return;
            }

            if($("#password").val() == ""){
                alert("请输入密码");
                return;
            }

            $.post("../cgi-bin/login.cgi",
            {
                "account.loginName" : $("#loginName").val(),
                "account.passwd" : $("#password").val()
            },function(data) {
                saveInfo();
                doLogin(data);
            }, "json");
        }

        // 登陆后跳转
        function doLogin(data){

            if (data != null && data.success) {
                location.href = 'login!doIndex.action';
            }
            else {

                if(data.message != null && data.message != ""){
                    alert(data.message);
                    doReset();
                }else if(data.msg != null && data.msg != ""){
                    alert(data.msg);
                    doReset();
                }
            }
        }

         // 保存Cookie
        function saveInfo() {
            try {
                 // 保存按键是否选中
                 var isSave = document.getElementById('remember_password').checked;
                 if (isSave) {
                     var username = $("#loginName").val();
                     var password = $("#password").val();
                     // alert(password);

                     if (username != "" && password != "") {
                         SetCookie(username, password);
                     }
                 } else {
                     SetCookie("", "");
                 }

             } catch (e) {}
         }

         // 保存Cookie
         function SetCookie(username, password) {
             var Then = new Date();
             Then.setTime(Then.getTime() + 1866240000000);
             document.cookie = ("username=" + username + "%%" + password + ";expires=" + Then.toGMTString());
         }

        // 获取登陆的用户名和密码
        function getCookie() {
             var nmpsd;
             var nm;
             var psd;
             var cookieString = new String(document.cookie);
             var cookieHeader = "username=";
             var beginPosition = cookieString.indexOf(cookieHeader);
             cookieString = cookieString.substring(beginPosition);
             var ends = cookieString.indexOf(";");
             if (ends != -1) {
                 cookieString = cookieString.substring(0, ends);
             }
             if (beginPosition > -1) {
                 nmpsd = cookieString.substring(cookieHeader.length);
                 if (nmpsd != "") {
                     beginPosition = nmpsd.indexOf("%%");
                     nm = nmpsd.substring(0, beginPosition);
                     psd = nmpsd.substring(beginPosition + 2);
                     $("#loginName").val(nm)
                     $("#password").val(psd)

                     if (nm != "" && psd != "") {
                         document.getElementById('remember_password').checked = true;
                     }
                 }
             }
        }

    </script>
</html>

```
- cgi源码
```
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
 #include <unistd.h>
#define MAXLEN 80

int main(void)
{
  // printf("HTTP/1.1 200 OK");
  // printf("success");
  printf("true");

    return 0;
}

```

- 浏览器输入
```
http://192.168.1.124/login.html
```
### 0.6 标签页切换
- 服务器端
```html
<!DOCTYPE html>
<html>
<head>
	<meta charset="utf-8" />
	<title>CSS3代码实现的tab标签切换</title>

<style>
	*{padding:0px;margin:0px;}
	#tab{margin:20px;20px;position:relative;}
	ul{list-style:none;}
	ul li{float:left;}
	ul li a{background:#f90;
			color:#fff;
			font-weight:500;
			height:30px;
			line-height:30px;
			border-bottom:0px;
			display:block;
			text-decoration:none;
			padding:0px 10px;
			margin-right:1px;
	}
	ul li a:hover{background:blue;}
	#div1{clear:left;}
	#tab>div{
			border:1px solid blue;
			width:170px;
			height:100px;
			text-indent:2em;
			padding:5px 5px;
			position:absolute;
			top:31px;
			background:#fff;
			}
	#div1:target,#div2:target,#div3:target{z-index:2;}
</style>

</head>
<body>

	<div id=tab>
		<ul>
			<li><a href="#div1">标签1</a></li>
			<li><a href="#div2">标签2</a></li>
			<li><a href="#div3">标签3</a></li>
		</ul>
			<div id=div1>欢迎来到北京，这是标签1的内容，这里是清华大学信息处理技术国家实验室（筹）</div>
			<div id=div2>欢迎来到杭州，这是标签2的内容，这里是浙江大学计算机图形学国家重点实验室</div>
			<div id=div3>欢迎来到武汉，这是标签3的内容，这里是华中科技大学脉冲强磁场国家重大科技基础设施</div>
	</div>

</body>
</html>

```
- 浏览器输入
```
http://192.168.1.124/changetab.html
```

