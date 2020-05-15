# refer

## 三种调用方式
```
https://www.cnblogs.com/52php/p/5813117.html
```

## exec函数族辨析

```
https://blog.csdn.net/wenchao126/article/details/7956168?utm_medium=distribute.pc_relevant.none-task-blog-BlogCommendFromMachineLearnPai2-1.nonecase&depth_1-utm_source=distribute.pc_relevant.none-task-blog-BlogCommendFromMachineLearnPai2-1.nonecase
```
要记住这六个函数之间的区别，就要搞清楚 “l” 、“v”、“p”、“e”代表的含义

    “l”表示参数以列表的形式表示；

    “v”表示参数以数组的形式表示；

    “p”表示在PATH中搜索执行文件；

    “e”表示可附加环境参数。

     execlp、execvp这两个函数第一个形参是名为file表示可以只列出文件名就可以了，不用指出它的路径。

     注意的地方有：

     1、参数以NULL结尾；

     2、exec函数族执行成功后不会返回，执行失败会返回 -1，错误代码存放在errno中

     3、可能的几种错误有，找不到文件或路径，errno为ENOENT；数组argv或envp没有以NULL结尾，errno为EFAULT；没有对执行文件的执行权限，errno为EACCESS；
