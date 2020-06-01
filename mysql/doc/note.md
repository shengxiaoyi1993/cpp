# note
## change the restore root
```
[sxy@localhost mysql]$ ps -ef | grep mysqld
mysql     2395     1  0 14:23 ?        00:00:00 /bin/sh /usr/bin/mysqld_safe --basedir=/usr
mysql     2592  2395  0 14:23 ?        00:00:00 /usr/sbin/mysqld --basedir=/usr --datadir=/var/lib/mysql --plugin-dir=/usr/lib64/mysql/plugin --log-error=/var/log/mysqld.log --pid-file=/var/run/mysqld/mysqld.pid --socket=/var/lib/mysql/mysql.sock
sxy       6485  5556  0 14:44 pts/2    00:00:00 grep --color=auto mysqld


[sxy@localhost Content]$ sudo mv /var/lib/mysql /home/sxy/Content
[sxy@localhost Content]$ ls
mysql  tftproot


[sxy@localhost etc]$ sudo vim  /etc/my.cnf

---
datadir=/home/mysql
socket=/home/mysql/mysql.sock


# add entry
[client]
socket=/home/mysql/mysql.sock

---


[sxy@localhost home]$ sudo atom /usr/bin/mysqld_safe
---
...
else
  DATADIR=/home/mysql   //479
fi
...
safe_mysql_unix_port=${mysql_unix_port:-${MYSQL_UNIX_PORT:-/home/sxy/mysql.sock}}  //679
...

---

[sxy@localhost home]$ ps -ef | grep mysqld
mysql     7305     1  0 16:16 ?        00:00:00 /bin/sh /usr/bin/mysqld_safe --basedir=/usr
mysql     7470  7305  0 16:16 ?        00:00:00 /usr/sbin/mysqld --basedir=/usr --datadir=/home/mysql --plugin-dir=/usr/lib64/mysql/plugin --log-error=/var/log/mysqld.log --pid-file=/var/run/mysqld/mysqld.pid --socket=/home/mysql/mysql.sock
root      7758     1  0 16:17 pts/1    00:00:00 /bin/bash /usr/bin/atom /usr/bin/mysqld_safe
root      7760  7758  2 16:17 pts/1    00:00:04 /usr/share/atom/atom --executed-from=/home --pid=7747 /usr/bin/mysqld_safe
sxy       8259  4497  0 16:21 pts/1    00:00:00 grep --color=auto mysqld



```
- 歧途：曾经mysql路径放到/home/sxy/Content/sql/ 路径下，但是启动是总是出错，问题在于mysql启动服务器，虽然mysql账户对于/home/sxy/Content/sql/设置了权限，但对于/home/sxy/Content/是没有权限的。将/home/sxy/Content/sql/移动到/home/mysql路径下，工作正常
