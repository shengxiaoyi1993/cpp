# env-setup
## 已安装docker和docker中已安装mysql时，启动mysql
```
[sxy@localhost ~]$ sudo systemctl start docker

# 初次启动
(base) [sxy@localhost-localdomain ~]$ sudo docker run -itd --name mysql-test -p 3306:3306 -e MYSQL_ROOT_PASSWORD=123456 mysql:5.6.48


# 有使用记录
[sxy@localhost ~]$ sudo docker ps
CONTAINER ID        IMAGE               COMMAND             CREATED             STATUS              PORTS               NAMES
[sxy@localhost ~]$ sudo docker ps -l
CONTAINER ID        IMAGE               COMMAND                  CREATED             STATUS                     PORTS               NAMES
dc83dafd5c42        mysql:5.6.48        "docker-entrypoint.s…"   4 weeks ago         Exited (255) 3 hours ago                       mysql-test
[sxy@localhost ~]$ sudo docker restart dc83dafd5c42
dc83dafd5c42



//LOGIN AS CLIENT
[sxy@localhost ~]$sudo mysql -h 127.0.0.1 -u root -p
//123456
```


## 编译和运行程序
```
# 项目中携带了一个centos7下编译的静态库;脚本未做周全的检测，若有错误自行修改
sh init.sh 
cd build 
mkdir build 
cmake ../
make
 ./mysqlcpp_warpper 
```