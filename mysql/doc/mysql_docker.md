

# launch_mysql_in_docker

```
[sxy@localhost ~]$ sudo systemctl start docker

[sxy@localhost ~]$ sudo docker ps
CONTAINER ID        IMAGE               COMMAND             CREATED             STATUS              PORTS               NAMES
[sxy@localhost ~]$ sudo docker ps -l
CONTAINER ID        IMAGE               COMMAND                  CREATED             STATUS                     PORTS               NAMES
dc83dafd5c42        mysql:5.6.48        "docker-entrypoint.s…"   4 weeks ago         Exited (255) 3 hours ago                       mysql-test
[sxy@localhost ~]$ sudo docker restart dc83dafd5c42
dc83dafd5c42


//LOGIN AS CLIENT
[sxy@localhost ~]$ 3
//123456


<!-- Create Table: CREATE TABLE `tb_uvsslabel` (
  `id` int(11) unsigned NOT NULL AUTO_INCREMENT,
  `dir` char(128) DEFAULT NULL,
  `big` char(128) DEFAULT NULL,
  `small` char(128) DEFAULT NULL, -->

  SELECT id,small
  FROM
  	tb_uvsslabel
  WHERE
  	id NOT IN (
  		SELECT
  			dt.minno
  		FROM
  			(
  				SELECT
  					MIN(id) AS minno
  				FROM
  					tb_uvsslabel
  				GROUP BY
  					small
  			) dt
  	)help

  ORDER BY
    small
```


## change language config 
- mysql 默认不支持中文，需要进行设置
- linux下的mysql 若在docker 下运行，需要对docker中的配置文件进行修改
```
https://blog.csdn.net/zhaoyajie1011/article/details/98623666

docker ps
docker exec -it [1383f2e49cb7] /bin/bash
more /etc/mysql/mysql.conf.d/mysqld.cnf
apt-get update
apt-get install vim
vim /etc/mysql/mysql.conf.d/mysqld.cnf
docker restart 1383f2e49cb7 
```

- 修改后的mysql文件配置
```
# Copyright (c) 2014, 2016, Oracle and/or its affiliates. All rights reserved.
#
# This program is free software; you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation; version 2 of the License.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program; if not, write to the Free Software
# Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301 USA

#
# The MySQL  Server configuration file.
#
# For explanations see
# http://dev.mysql.com/doc/mysql/en/server-system-variables.html

[mysqld]
pid-file        = /var/run/mysqld/mysqld.pid
socket          = /var/run/mysqld/mysqld.sock
datadir         = /var/lib/mysql
#log-error      = /var/log/mysql/error.log
# By default we only accept connections from localhost
#bind-address   = 127.0.0.1
# Disabling symbolic-links is recommended to prevent assorted security risks
symbolic-links=0
character_set_server=utf8
init_connect='SET NAMES utf8'
max_allowed_packet = 20M

[mysql]
default-character-set = utf8

[mysql.server]
default-character-set = utf8

[mysqld_safe]
default-character-set = utf8

[client]
default-character-set = utf8

```
 - 设置后重启docker中的mysql，仍无法使用

- 解决外部访问的乱码问题
```
SET NAMES 'utf8';
# 仍无效
```

- 建立数据表时，设置语言
```
# 加上"DEFAULT CHARSET=utf8"
# 如
create table  t_product(
pid     varchar(20),
pname    varchar(20),
price    double,
address   varchar(30)
) DEFAULT CHARSET=utf8;

# 设置后命令行与代码接口访问均能看到中文数据
```
