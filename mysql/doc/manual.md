# Manual



## 1. centos

### 1.1. status


```
[sxy@localhost ~]$ ps -ef | grep mysqld
mysql     2970     1  0 09:28 ?        00:00:00 /bin/sh /usr/bin/mysqld_safe --basedir=/usr
mysql     3135  2970  0 09:28 ?        00:00:00 /usr/sbin/mysqld --basedir=/usr --datadir=/var/lib/mysql --plugin-dir=/usr/lib64/mysql/plugin --log-error=/var/log/mysqld.log --pid-file=/var/run/mysqld/mysqld.pid --socket=/var/lib/mysql/mysql.sock
sxy       5789  4832  0 09:46 pts/2    00:00:00 grep --color=auto mysqld

```

### 1.2. change_password
```
mysqladmin -u root password "new_password";
```

### 1.3. login
```
[root@host]# mysql -u root -p
Enter password:*******
```

### 1.4. shutdown   (测试失败)
```
root@host# cd /usr/bin
./mysqladmin -u root -p shutdown
Enter password: ******
```

### 1.5. 插入用户
```
mysql> create user 'joey'@'localhost' identified by 'joey';
Query OK, 0 rows affected (0.00 sec)

mysql> GRANT SELECT,INSERT,UPDATE,DELETE,CREATE,DROP
    -> ON TUTORIALS.*
    -> TO 'zara'@'localhost'
    ->  IDENTIFIED BY 'zara123';
Query OK, 0 rows affected (0.00 sec)

mysql> grant all privileges on joey.* to 'joey'@'localhost' identified by 'joey';
Query OK, 0 rows affected (0.00 sec)

#重新载入授权表
mysql>  flush privileges;
Query OK, 0 rows affected (0.01 sec)

mysql>  SELECT host, user, password FROM user WHERE user = 'joey';
+-----------+------+-------------------------------------------+
| host      | user | password                                  |
+-----------+------+-------------------------------------------+
| localhost | joey | *DF83341D2DC42D7B18DF2C4EAEC13AABE2516614 |
+-----------+------+-------------------------------------------+
1 row in set (0.00 sec)

```
### 1.6. operation
```
mysql> use mysql
Database changed

mysql> show databases;
+--------------------+
| Database           |
+--------------------+
| information_schema |
| mysql              |
| performance_schema |
+--------------------+
3 rows in set (0.00 sec)

mysql> show tables;
+---------------------------+
| Tables_in_mysql           |
+---------------------------+
| columns_priv              |
| db                        |
| event                     |
| func                      |
| general_log               |
| help_category             |
| help_keyword              |
| help_relation             |
| help_topic                |
| innodb_index_stats        |
| innodb_table_stats        |
| ndb_binlog_index          |
| plugin                    |
| proc                      |
| procs_priv                |
| proxies_priv              |
| servers                   |
| slave_master_info         |
| slave_relay_log_info      |
| slave_worker_info         |
| slow_log                  |
| tables_priv               |
| time_zone                 |
| time_zone_leap_second     |
| time_zone_name            |
| time_zone_transition      |
| time_zone_transition_type |
| user                      |
+---------------------------+
28 rows in set (0.00 sec)

# 显示数据表的属性，属性类型，主键信息 ，是否为 NULL，默认值等其他信息。
mysql> show columns from columns_priv;
+-------------+----------------------------------------------+------+-----+-------------------+-----------------------------+
| Field       | Type                                         | Null | Key | Default           | Extra                       |
+-------------+----------------------------------------------+------+-----+-------------------+-----------------------------+
| Host        | char(60)                                     | NO   | PRI |                   |                             |
| Db          | char(64)                                     | NO   | PRI |                   |                             |
| User        | char(16)                                     | NO   | PRI |                   |                             |
| Table_name  | char(64)                                     | NO   | PRI |                   |                             |
| Column_name | char(64)                                     | NO   | PRI |                   |                             |
| Timestamp   | timestamp                                    | NO   |     | CURRENT_TIMESTAMP | on update CURRENT_TIMESTAMP |
| Column_priv | set('Select','Insert','Update','References') | NO   |     |                   |                             |
+-------------+----------------------------------------------+------+-----+-------------------+-----------------------------+
7 rows in set (0.00 sec)

#详细索引信息
mysql> SHOW INDEX FROM columns_priv;
+--------------+------------+----------+--------------+-------------+-----------+-------------+----------+--------+------+------------+---------+---------------+
| Table        | Non_unique | Key_name | Seq_in_index | Column_name | Collation | Cardinality | Sub_part | Packed | Null | Index_type | Comment | Index_comment |
+--------------+------------+----------+--------------+-------------+-----------+-------------+----------+--------+------+------------+---------+---------------+
| columns_priv |          0 | PRIMARY  |            1 | Host        | A         |        NULL |     NULL | NULL   |      | BTREE      |         |               |
| columns_priv |          0 | PRIMARY  |            2 | Db          | A         |        NULL |     NULL | NULL   |      | BTREE      |         |               |
| columns_priv |          0 | PRIMARY  |            3 | User        | A         |        NULL |     NULL | NULL   |      | BTREE      |         |               |
| columns_priv |          0 | PRIMARY  |            4 | Table_name  | A         |        NULL |     NULL | NULL   |      | BTREE      |         |               |
| columns_priv |          0 | PRIMARY  |            5 | Column_name | A         |           0 |     NULL | NULL   |      | BTREE      |         |               |
+--------------+------------+----------+--------------+-------------+-----------+-------------+----------+--------+------+------------+---------+---------------+
5 rows in set (0.00 sec)



mysql> SHOW TABLE STATUS  FROM mysql;
+---------------------------+--------+---------+------------+------+----------------+-------------+--------------------+--------------+-----------+----------------+---------------------+---------------------+---------------------+-------------------+----------+--------------------+-----------------------------------------+
| Name                      | Engine | Version | Row_format | Rows | Avg_row_length | Data_length | Max_data_length    | Index_length | Data_free | Auto_increment | Create_time         | Update_time         | Check_time          | Collation         | Checksum | Create_options     | Comment                                 |
+---------------------------+--------+---------+------------+------+----------------+-------------+--------------------+--------------+-----------+----------------+---------------------+---------------------+---------------------+-------------------+----------+--------------------+-----------------------------------------+
| columns_priv              | MyISAM |      10 | Fixed      |    0 |              0 |           0 | 227994731135631359 |         4096 |         0 |           NULL | 2020-05-26 09:28:48 | 2020-05-26 09:28:48 | NULL                | utf8_bin          |     NULL |                    | Column privileges                       |
| db                        | MyISAM |      10 | Fixed      |    4 |            440 |        1760 | 123848989752688639 |         5120 |         0 |           NULL | 2020-05-26 09:28:48 | 2020-05-26 10:07:05 | 2020-05-26 09:28:49 | utf8_bin          |     NULL |                    | Database privileges                     |
| event                     | MyISAM |      10 | Dynamic    |    0 |              0 |           0 |    281474976710655 |         2048 |         0 |           NULL | 2020-05-26 09:28:48 | 2020-05-26 09:28:48 | NULL                | utf8_general_ci   |     NULL |                    | Events                                  |
| func                      | MyISAM |      10 | Fixed      |    0 |              0 |           0 | 162974011515469823 |         1024 |         0 |           NULL | 2020-05-26 09:28:48 | 2020-05-26 09:28:48 | NULL                | utf8_bin          |     NULL |                    | User defined functions                  |
| general_log               | CSV    |      10 | Dynamic    |    2 |              0 |           0 |                  0 |            0 |         0 |           NULL | NULL                | NULL                | NULL                | utf8_general_ci   |     NULL |                    | General log                             |
| help_category             | MyISAM |      10 | Dynamic    |   43 |             28 |        1228 |    281474976710655 |         5120 |         0 |           NULL | 2020-05-26 09:28:50 | 2020-05-26 09:28:50 | NULL                | utf8_general_ci   |     NULL |                    | help categories                         |
| help_keyword              | MyISAM |      10 | Fixed      |  620 |            197 |      122140 |  55450570411999231 |        23552 |         0 |           NULL | 2020-05-26 09:28:50 | 2020-05-26 09:28:50 | NULL                | utf8_general_ci   |     NULL |                    | help keywords                           |
| help_relation             | MyISAM |      10 | Fixed      | 1412 |              9 |       12708 |   2533274790395903 |        22528 |         0 |           NULL | 2020-05-26 09:28:50 | 2020-05-26 09:28:50 | NULL                | utf8_general_ci   |     NULL |                    | keyword-topic relation                  |
| help_topic                | MyISAM |      10 | Dynamic    |  603 |           1019 |      614696 |    281474976710655 |        21504 |         0 |           NULL | 2020-05-26 09:28:50 | 2020-05-26 09:28:50 | NULL                | utf8_general_ci   |     NULL |                    | help topics                             |
| innodb_index_stats        | InnoDB |      10 | Compact    |    0 |              0 |       16384 |                  0 |            0 |         0 |           NULL | 2020-05-26 09:28:48 | NULL                | NULL                | utf8_bin          |     NULL | stats_persistent=0 |                                         |
| innodb_table_stats        | InnoDB |      10 | Compact    |    0 |              0 |       16384 |                  0 |            0 |         0 |           NULL | 2020-05-26 09:28:48 | NULL                | NULL                | utf8_bin          |     NULL | stats_persistent=0 |                                         |
| ndb_binlog_index          | MyISAM |      10 | Dynamic    |    0 |              0 |           0 |    281474976710655 |         1024 |         0 |           NULL | 2020-05-26 09:28:48 | 2020-05-26 09:28:48 | NULL                | latin1_swedish_ci |     NULL |                    |                                         |
| plugin                    | MyISAM |      10 | Dynamic    |    0 |              0 |           0 |    281474976710655 |         1024 |         0 |           NULL | 2020-05-26 09:28:48 | 2020-05-26 09:28:48 | NULL                | utf8_general_ci   |     NULL |                    | MySQL plugins                           |
| proc                      | MyISAM |      10 | Dynamic    |    0 |              0 |           0 |    281474976710655 |         2048 |         0 |           NULL | 2020-05-26 09:28:48 | 2020-05-26 09:28:48 | NULL                | utf8_general_ci   |     NULL |                    | Stored Procedures                       |
| procs_priv                | MyISAM |      10 | Fixed      |    0 |              0 |           0 | 239253730204057599 |         4096 |         0 |           NULL | 2020-05-26 09:28:48 | 2020-05-26 09:28:48 | NULL                | utf8_bin          |     NULL |                    | Procedure privileges                    |
| proxies_priv              | MyISAM |      10 | Fixed      |    2 |            693 |        1386 | 195062158860484607 |         5120 |         0 |           NULL | 2020-05-26 09:28:49 | 2020-05-26 09:28:49 | 2020-05-26 09:28:49 | utf8_bin          |     NULL |                    | User proxy privileges                   |
| servers                   | MyISAM |      10 | Fixed      |    0 |              0 |           0 | 433752939111120895 |         1024 |         0 |           NULL | 2020-05-26 09:28:48 | 2020-05-26 09:28:48 | NULL                | utf8_general_ci   |     NULL |                    | MySQL Foreign Servers table             |
| slave_master_info         | InnoDB |      10 | Compact    |    0 |              0 |       16384 |                  0 |            0 |         0 |           NULL | 2020-05-26 09:28:48 | NULL                | NULL                | utf8_general_ci   |     NULL | stats_persistent=0 | Master Information                      |
| slave_relay_log_info      | InnoDB |      10 | Compact    |    0 |              0 |       16384 |                  0 |            0 |         0 |           NULL | 2020-05-26 09:28:48 | NULL                | NULL                | utf8_general_ci   |     NULL | stats_persistent=0 | Relay Log Information                   |
| slave_worker_info         | InnoDB |      10 | Compact    |    0 |              0 |       16384 |                  0 |            0 |         0 |           NULL | 2020-05-26 09:28:49 | NULL                | NULL                | utf8_general_ci   |     NULL | stats_persistent=0 | Worker Information                      |
| slow_log                  | CSV    |      10 | Dynamic    |    2 |              0 |           0 |                  0 |            0 |         0 |           NULL | NULL                | NULL                | NULL                | utf8_general_ci   |     NULL |                    | Slow log                                |
| tables_priv               | MyISAM |      10 | Fixed      |    0 |              0 |           0 | 239535205180768255 |         4096 |         0 |           NULL | 2020-05-26 09:28:48 | 2020-05-26 09:28:48 | NULL                | utf8_bin          |     NULL |                    | Table privileges                        |
| time_zone                 | MyISAM |      10 | Fixed      |    0 |              0 |           0 |   1970324836974591 |         1024 |         0 |              1 | 2020-05-26 09:28:48 | 2020-05-26 09:28:48 | NULL                | utf8_general_ci   |     NULL |                    | Time zones                              |
| time_zone_leap_second     | MyISAM |      10 | Fixed      |    0 |              0 |           0 |   3659174697238527 |         1024 |         0 |           NULL | 2020-05-26 09:28:48 | 2020-05-26 09:28:48 | NULL                | utf8_general_ci   |     NULL |                    | Leap seconds information for time zones |
| time_zone_name            | MyISAM |      10 | Fixed      |    0 |              0 |           0 |  55450570411999231 |         1024 |         0 |           NULL | 2020-05-26 09:28:48 | 2020-05-26 09:28:48 | NULL                | utf8_general_ci   |     NULL |                    | Time zone names                         |
| time_zone_transition      | MyISAM |      10 | Fixed      |    0 |              0 |           0 |   4785074604081151 |         1024 |         0 |           NULL | 2020-05-26 09:28:48 | 2020-05-26 09:28:48 | NULL                | utf8_general_ci   |     NULL |                    | Time zone transitions                   |
| time_zone_transition_type | MyISAM |      10 | Fixed      |    0 |              0 |           0 |  10696049115004927 |         1024 |         0 |           NULL | 2020-05-26 09:28:48 | 2020-05-26 09:28:48 | NULL                | utf8_general_ci   |     NULL |                    | Time zone transition types              |
| user                      | MyISAM |      10 | Dynamic    |    8 |             94 |         752 |    281474976710655 |         2048 |         0 |           NULL | 2020-05-26 09:28:48 | 2020-05-26 10:07:05 | NULL                | utf8_bin          |     NULL |                    | Users and global privileges             |
+---------------------------+--------+---------+------------+------+----------------+-------------+--------------------+--------------+-----------+----------------+---------------------+---------------------+---------------------+-------------------+----------+--------------------+-----------------------------------------+
28 rows in set (0.00 sec)
# print in row
mysql> SHOW TABLE STATUS from mysql LIKE 'column%'\G;
*************************** 1. row ***************************
           Name: columns_priv
         Engine: MyISAM
        Version: 10
     Row_format: Fixed
           Rows: 0
 Avg_row_length: 0
    Data_length: 0
Max_data_length: 227994731135631359
   Index_length: 4096
      Data_free: 0
 Auto_increment: NULL
    Create_time: 2020-05-26 09:28:48
    Update_time: 2020-05-26 09:28:48
     Check_time: NULL
      Collation: utf8_bin
       Checksum: NULL
 Create_options:
        Comment: Column privileges
1 row in set (0.01 sec)

ERROR:
No query specified

mysql> SHOW TABLE STATUS from mysql LIKE 'column%';
+--------------+--------+---------+------------+------+----------------+-------------+--------------------+--------------+-----------+----------------+---------------------+---------------------+------------+-----------+----------+----------------+-------------------+
| Name         | Engine | Version | Row_format | Rows | Avg_row_length | Data_length | Max_data_length    | Index_length | Data_free | Auto_increment | Create_time         | Update_time         | Check_time | Collation | Checksum | Create_options | Comment           |
+--------------+--------+---------+------------+------+----------------+-------------+--------------------+--------------+-----------+----------------+---------------------+---------------------+------------+-----------+----------+----------------+-------------------+
| columns_priv | MyISAM |      10 | Fixed      |    0 |              0 |           0 | 227994731135631359 |         4096 |         0 |           NULL | 2020-05-26 09:28:48 | 2020-05-26 09:28:48 | NULL       | utf8_bin  |     NULL |                | Column privileges |
+--------------+--------+---------+------------+------+----------------+-------------+--------------------+--------------+-----------+----------------+---------------------+---------------------+------------+-----------+----------+----------------+-------------------+
1 row in set (0.00 sec)

```
