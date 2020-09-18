### 1. MySQL 中修改数据表的存储引擎的语法格式如下：
```
ALTER TABLE <表名> ENGINE=<存储引擎名>;
```
### 2. 建表
```
CREATE TABLE <表名> ([表定义选项])[表选项][分区选项];

```

```
mysql> CREATE DATABASE test_db
    -> ;
Query OK, 1 row affected (0.01 sec)

mysql> SHOW DATABASES
    -> ;
+--------------------+
| Database           |
+--------------------+
| information_schema |
| mysql              |
| new_schema         |
| performance_schema |
| sys                |
| test               |
| test_db            |
+--------------------+
7 rows in set (0.00 sec)

mysql> USE test_db
Database changed
mysql> SHOW TABLES
    -> ;
Empty set (0.00 sec)
mysql> CREATE TABLE tb_empl
    -> (
    -> id INT(11),
    -> name VARCHAR(25),
    -> deptId INT(11),
    -> salary FLOAT
    -> );
Query OK, 0 rows affected, 2 warnings (0.04 sec)

mysql> SHOW TABLES
    -> ;
+-------------------+
| Tables_in_test_db |
+-------------------+
| tb_empl           |
+-------------------+
1 row in set (0.00 sec)

mysql> DESC tb_empl
    -> ;
+--------+-------------+------+-----+---------+-------+
| Field  | Type        | Null | Key | Default | Extra |
+--------+-------------+------+-----+---------+-------+
| id     | int         | YES  |     | NULL    |       |
| name   | varchar(25) | YES  |     | NULL    |       |
| deptId | int         | YES  |     | NULL    |       |
| salary | float       | YES  |     | NULL    |       |
+--------+-------------+------+-----+---------+-------+
4 rows in set (0.00 sec)

mysql> SHOW CREATE TABLE tb_empl \G;
*************************** 1. row ***************************
       Table: tb_empl
Create Table: CREATE TABLE `tb_empl` (
  `id` int DEFAULT NULL,
  `name` varchar(25) DEFAULT NULL,
  `deptId` int DEFAULT NULL,
  `salary` float DEFAULT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8
1 row in set (0.00 sec)

```

### change_table_name

```
mysql> ALTER TABLE STUDENT RENAME TO tb_student
    -> ;
Query OK, 0 rows affected (0.03 sec)

mysql> SHOW TABLES
    -> ;
+---------------------------+
| Tables_in_tb_student_info |
+---------------------------+
| tb_student                |
+---------------------------+
1 row in set (0.00 sec)

```

### change_table_segment_name&type

```
mysql> ALTER TABLE tb_student CHANGE name student_name INT(11);
Query OK, 0 rows affected, 1 warning (0.07 sec)
Records: 0  Duplicates: 0  Warnings: 1

mysql> DESC tb_student;
+--------------+------+------+-----+---------+-------+
| Field        | Type | Null | Key | Default | Extra |
+--------------+------+------+-----+---------+-------+
| student_name | int  | YES  |     | NULL    |       |
| grade        | int  | YES  |     | NULL    |       |
+--------------+------+------+-----+---------+-------+
2 rows in set (0.00 sec)
```

### change_table_segment_type

```
mysql> ALTER TABLE tb_student MODIFY  student_name VARCHAR(25);
Query OK, 0 rows affected (0.07 sec)
Records: 0  Duplicates: 0  Warnings: 0

mysql> DESC tb_student
    -> ;
+--------------+-------------+------+-----+---------+-------+
| Field        | Type        | Null | Key | Default | Extra |
+--------------+-------------+------+-----+---------+-------+
| student_name | varchar(25) | YES  |     | NULL    |       |
| grade        | int         | YES  |     | NULL    |       |
+--------------+-------------+------+-----+---------+-------+
2 rows in set (0.00 sec)
```

### delete_table_segment

```
mysql> ALTER TABLE tb_student DROP grade;
Query OK, 0 rows affected (0.06 sec)
Records: 0  Duplicates: 0  Warnings: 0

mysql> DESC tb_student
    -> ;
+--------------+-------------+------+-----+---------+-------+
| Field        | Type        | Null | Key | Default | Extra |
+--------------+-------------+------+-----+---------+-------+
| student_name | varchar(25) | YES  |     | NULL    |       |
+--------------+-------------+------+-----+---------+-------+
1 row in set (0.00 sec)

```

### delete_table

```
mysql> CREATE TABLE tb_delete
    -> (
    -> col INT(11)
    -> );
Query OK, 0 rows affected, 1 warning (0.03 sec)

mysql> SHOW TABLES;
+---------------------------+
| Tables_in_tb_student_info |
+---------------------------+
| tb_delete                 |
| tb_student                |
+---------------------------+
2 rows in set (0.00 sec)

mysql> DROP TABLE tb_delete;
Query OK, 0 rows affected (0.02 sec)

mysql> SHOW TABLES;
+---------------------------+
| Tables_in_tb_student_info |
+---------------------------+
| tb_student                |
+---------------------------+
1 row in set (0.00 sec)
```



### release_key_dependent

```
mysql> DROP TABLE tb_emp4;
ERROR 3730 (HY000): Cannot drop table 'tb_emp4' referenced by a foreign key constraint 'fk_emp4_emp5' on table 'tb_emp5'.
mysql>  ALTER TABLE tb_emp5 DROP FOREIGN KEY fk_emp4_emp5;
Query OK, 0 rows affected (0.02 sec)
Records: 0  Duplicates: 0  Warnings: 0
mysql> DROP TABLE tb_emp4;
Query OK, 0 rows affected (0.02 sec)
```

### add_table_segment_end

```
mysql> ALTER TABLE tb_student ADD sex VARCHAR(11);
Query OK, 0 rows affected (0.03 sec)
Records: 0  Duplicates: 0  Warnings: 0
mysql> DESC tb_student;
+--------------+-------------+------+-----+---------+-------+
| Field        | Type        | Null | Key | Default | Extra |
+--------------+-------------+------+-----+---------+-------+
| student_name | varchar(25) | YES  |     | NULL    |       |
| sex          | varchar(11) | YES  |     | NULL    |       |
+--------------+-------------+------+-----+---------+-------+
2 rows in set (0.00 sec)
```

### add_table_segment_first

```
mysql> ALTER TABLE tb_student ADD age INT(11) FIRST;
Query OK, 0 rows affected, 1 warning (0.07 sec)
Records: 0  Duplicates: 0  Warnings: 1

mysql> DESC tb_student;
+--------------+-------------+------+-----+---------+-------+
| Field        | Type        | Null | Key | Default | Extra |
+--------------+-------------+------+-----+---------+-------+
| age          | int         | YES  |     | NULL    |       |
| student_name | varchar(25) | YES  |     | NULL    |       |
| sex          | varchar(11) | YES  |     | NULL    |       |
+--------------+-------------+------+-----+---------+-------+
3 rows in set (0.00 sec)

```

### add_table_segment_after_segment

```
mysql> ALTER TABLE tb_student ADD birthday DATE AFTER age;
Query OK, 0 rows affected (0.05 sec)
Records: 0  Duplicates: 0  Warnings: 0

mysql> DESC tb_student;
+--------------+-------------+------+-----+---------+-------+
| Field        | Type        | Null | Key | Default | Extra |
+--------------+-------------+------+-----+---------+-------+
| age          | int         | YES  |     | NULL    |       |
| birthday     | date        | YES  |     | NULL    |       |
| student_name | varchar(25) | YES  |     | NULL    |       |
| sex          | varchar(11) | YES  |     | NULL    |       |
+--------------+-------------+------+-----+---------+-------+
4 rows in set (0.00 sec)
```

## 约束

```
- 主键约束:唯一标识表中的每条信息
- 外键约束：数据一致性
- 唯一约束：避免重名，允许空值，但空值不能出现多次
- 检查约束：检查字段是否有效
- 非空约束：为空则无效
- 默认值约束：若未输入，则设置默认值
```

### single_primary_key

```
<字段名> <数据类型> PRIMARY KEY [默认值]
```

```
mysql> CREATE TABLE tb_with_key(
    -> name VARCHAR(25),
    -> age INT(9),
    -> ID INT(9) PRIMARY KEY
    -> );
Query OK, 0 rows affected, 2 warnings (0.05 sec)

mysql> SHOW CREATE TABLE tb_with_key \G;
*************************** 1. row ***************************
       Table: tb_with_key
Create Table: CREATE TABLE `tb_with_key` (
  `name` varchar(25) DEFAULT NULL,
  `age` int DEFAULT NULL,
  `ID` int NOT NULL,
  PRIMARY KEY (`ID`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8
1 row in set (0.00 sec)

ERROR:
No query specified

```

```
mysql> CREATE TABLE tb_with_single_key
    -> (
    -> id INT(9),
    -> name VARCHAR(25),
    -> sex INT(9),
    -> PRIMARY KEY(id)
    -> );
Query OK, 0 rows affected, 2 warnings (0.03 sec)

mysql> SHOW CREATE TABLE tb_with_single_key \G;
*************************** 1. row ***************************
       Table: tb_with_single_key
Create Table: CREATE TABLE `tb_with_single_key` (
  `id` int NOT NULL,
  `name` varchar(25) DEFAULT NULL,
  `sex` int DEFAULT NULL,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8
1 row in set (0.00 sec)

ERROR:
No query specified
mysql> DESC tb_with_single_key
    -> ;
+-------+-------------+------+-----+---------+-------+
| Field | Type        | Null | Key | Default | Extra |
+-------+-------------+------+-----+---------+-------+
| id    | int         | NO   | PRI | NULL    |       |
| name  | varchar(25) | YES  |     | NULL    |       |
| sex   | int         | YES  |     | NULL    |       |
+-------+-------------+------+-----+---------+-------+
3 rows in set (0.00 sec)
```



### table_with_combined_key

```
mysql> CREATE TABLE tb_with_combined_key
    -> (
    -> id INT(9),
    -> name VARCHAR(25),
    -> age INT(9),
    -> sex INT(9)
    -> ,PRIMARY KEY(id,name)
    -> );
Query OK, 0 rows affected, 3 warnings (0.04 sec)

mysql> DESC tb_with_combined_key;
+-------+-------------+------+-----+---------+-------+
| Field | Type        | Null | Key | Default | Extra |
+-------+-------------+------+-----+---------+-------+
| id    | int         | NO   | PRI | NULL    |       |
| name  | varchar(25) | NO   | PRI | NULL    |       |
| age   | int         | YES  |     | NULL    |       |
| sex   | int         | YES  |     | NULL    |       |
+-------+-------------+------+-----+---------+-------+
4 rows in set (0.00 sec)

```

### add_primary_key

```
mysql> DESC tb_student;
+--------------+-------------+------+-----+---------+-------+
| Field        | Type        | Null | Key | Default | Extra |
+--------------+-------------+------+-----+---------+-------+
| age          | int         | YES  |     | NULL    |       |
| birthday     | date        | YES  |     | NULL    |       |
| student_name | varchar(25) | YES  |     | NULL    |       |
| sex          | varchar(11) | YES  |     | NULL    |       |
+--------------+-------------+------+-----+---------+-------+
4 rows in set (0.00 sec)
mysql> ALTER TABLE tb_student
    -> ADD PRIMARY KEY(student_name);
Query OK, 0 rows affected (0.07 sec)
Records: 0  Duplicates: 0  Warnings: 0

mysql> DESC tb_student;
+--------------+-------------+------+-----+---------+-------+
| Field        | Type        | Null | Key | Default | Extra |
+--------------+-------------+------+-----+---------+-------+
| age          | int         | YES  |     | NULL    |       |
| birthday     | date        | YES  |     | NULL    |       |
| student_name | varchar(25) | NO   | PRI | NULL    |       |
| sex          | varchar(11) | YES  |     | NULL    |       |
+--------------+-------------+------+-----+---------+-------+
4 rows in set (0.00 sec)
```



### delete_primary_key

```
mysql> ALTER TABLE tb_with_combined_key DROP PRIMARY KEY;
Query OK, 0 rows affected (0.07 sec)
Records: 0  Duplicates: 0  Warnings: 0

mysql> DESC tb_with_combined_key;
+-------+-------------+------+-----+---------+-------+
| Field | Type        | Null | Key | Default | Extra |
+-------+-------------+------+-----+---------+-------+
| id    | int         | NO   |     | NULL    |       |
| name  | varchar(25) | NO   |     | NULL    |       |
| age   | int         | YES  |     | NULL    |       |
| sex   | int         | YES  |     | NULL    |       |
+-------+-------------+------+-----+---------+-------+
4 rows in set (0.00 sec)
```

### primary_key_auto_increment

```
mysql> CREATE TABLE tb_fruit
    -> (
    -> id INT(4) PRIMARY KEY AUTO_INCREMENT,
    -> name VARCHAR(25) NOT NULL
    -> );
Query OK, 0 rows affected, 1 warning (0.05 sec)

mysql> DESC tb_fruit;
+-------+-------------+------+-----+---------+----------------+
| Field | Type        | Null | Key | Default | Extra          |
+-------+-------------+------+-----+---------+----------------+
| id    | int         | NO   | PRI | NULL    | auto_increment |
| name  | varchar(25) | NO   |     | NULL    |                |
+-------+-------------+------+-----+---------+----------------+
2 rows in set (0.00 sec)

mysql> INSERT INTO tb_fruit(name) VALUES('apple');
Query OK, 1 row affected (0.01 sec)

mysql> INSERT INTO tb_fruit(name) VALUES('banana');
Query OK, 1 row affected (0.00 sec)

mysql> INSERT INTO tb_fruit(name) VALUES('peach');
Query OK, 1 row affected (0.00 sec)

mysql> SELECT * FROM tb_fruit;
+----+--------+
| id | name   |
+----+--------+
|  1 | apple  |
|  2 | banana |
|  3 | peach  |
+----+--------+
3 rows in set (0.00 sec)
```

### add_autoincrement

```
mysql> ALTER TABLE tb_testcheck  CHANGE id id INT AUTO_INCREMENT;
```



### set_autoincrement_init_value

```
mysql> CREATE TABLE tb_flower
    -> (
      -> id INT(9) PRIMARY KEY AUTO_INCREMENT,
    -> name VARCHAR(25),
    -> price INT(9)
    -> )AUTO_INCREMENT=100;
Query OK, 0 rows affected, 2 warnings (0.04 sec)

mysql> DESC tb_flower;
+-------+-------------+------+-----+---------+----------------+
| Field | Type        | Null | Key | Default | Extra          |
+-------+-------------+------+-----+---------+----------------+
| id    | int         | NO   | PRI | NULL    | auto_increment |
| name  | varchar(25) | YES  |     | NULL    |                |
| price | int         | YES  |     | NULL    |                |
+-------+-------------+------+-----+---------+----------------+
3 rows in set (0.00 sec)

mysql> INSERT INTO tb_flower (name)VALUES('rose');
Query OK, 1 row affected (0.00 sec)

mysql> SELECT * FROM tb_flower;
+-----+------+-------+
| id  | name | price |
+-----+------+-------+
| 100 | rose |  NULL |
+-----+------+-------+
1 row in set (0.00 sec)

mysql> SHOW CREATE TABLE tb_flower \G;
*************************** 1. row ***************************
       Table: tb_flower
Create Table: CREATE TABLE `tb_flower` (
  `id` int NOT NULL AUTO_INCREMENT,
  `name` varchar(25) DEFAULT NULL,
  `price` int DEFAULT NULL,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB AUTO_INCREMENT=101 DEFAULT CHARSET=utf8
1 row in set (0.00 sec)

ERROR:
No query specified
```

### set_foreign_key

```
mysql> CREATE TABLE tb_dept1
    -> (
    -> id INT(11) PRIMARY KEY,
    -> name VARCHAR(22) NOT NULL,
    -> location VARCHAR(50)
    -> );
Query OK, 0 rows affected, 1 warning (0.04 sec)

mysql> CREATE TABLE tb_emp6
    -> (
    -> id INT(11) PRIMARY KEY,
    -> name VARCHAR(25),
    -> deptId INT(11),
    -> salary FLOAT,
    -> CONSTRAINT fk_emp_dept
    -> FOREIGN KEY(deptId) REFERENCES tb_dept1(id)
    -> );
Query OK, 0 rows affected, 2 warnings (0.05 sec)

mysql> DESC tb_emp6;
+--------+-------------+------+-----+---------+-------+
| Field  | Type        | Null | Key | Default | Extra |
+--------+-------------+------+-----+---------+-------+
| id     | int         | NO   | PRI | NULL    |       |
| name   | varchar(25) | YES  |     | NULL    |       |
| deptId | int         | YES  | MUL | NULL    |       |
| salary | float       | YES  |     | NULL    |       |
+--------+-------------+------+-----+---------+-------+
4 rows in set (0.00 sec)

```



### add_foreign_key

```
//same type is needed,the foreign key must be primary key
mysql> ALTER TABLE tb_fruit
    -> ADD PRIMARY KEY(name);
Query OK, 0 rows affected (0.09 sec)
Records: 0  Duplicates: 0  Warnings: 0

mysql> ALTER TABLE tb_student ADD CONSTRAINT fk_student_like_fruit
    -> FOREIGN KEY(fruit) REFERENCES tb_fruit(name);
Query OK, 0 rows affected (0.09 sec)
Records: 0  Duplicates: 0  Warnings: 0

```

### del_foreign_key

```
mysql> ALTER TABLE tb_student DROP FOREIGN KEY fk_student_like_fruit;
Query OK, 0 rows affected (0.02 sec)
Records: 0  Duplicates: 0  Warnings: 0

mysql> SHOW CREATE TABLE tb_student\G;
*************************** 1. row ***************************
       Table: tb_student
Create Table: CREATE TABLE `tb_student` (
  `age` int DEFAULT NULL,
  `birthday` date DEFAULT NULL,
  `student_name` varchar(25) NOT NULL,
  `sex` varchar(11) DEFAULT NULL,
  `fruit` varchar(11) DEFAULT NULL,
  PRIMARY KEY (`student_name`),
  KEY `fk_student_like_fruit` (`fruit`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8
1 row in set (0.00 sec)

ERROR:
No query specified
```

### set_unique_key

```
mysql> CREATE TABLE tb_dept2
    -> (
    -> id INT(11) PRIMARY KEY,
    -> name VARCHAR(22) UNIQUE,
    -> location VARCHAR(50)
    -> );
Query OK, 0 rows affected (0.37 sec)

mysql> DESC tb_dept2;
+----------+-------------+------+-----+---------+-------+
| Field    | Type        | Null | Key | Default | Extra |
+----------+-------------+------+-----+---------+-------+
| id       | int(11)     | NO   | PRI | NULL    |       |
| name     | varchar(40) | YES  | UNI | NULL    |       |
| location | varchar(50) | YES  |     | NULL    |       |
+----------+-------------+------+-----+---------+-------+
3 rows in set (0.08 sec)
```

### add_unique_key

```
ALTER TABLE <数据表名> ADD CONSTRAINT <唯一约束名> UNIQUE(<列名>);
```



```
mysql> ALTER TABLE tb_dept1
    -> ADD CONSTRAINT unique_name UNIQUE(name);
Query OK, 0 rows affected (0.63 sec)
Records: 0  Duplicates: 0  Warnings: 0

mysql> DESC tb_dept1;
+----------+-------------+------+-----+---------+-------+
| Field    | Type        | Null | Key | Default | Extra |
+----------+-------------+------+-----+---------+-------+
| id       | int(11)     | NO   | PRI | NULL    |       |
| name     | varchar(22) | NO   | UNI | NULL    |       |
| location | varchar(50) | YES  |     | NULL    |       |
+----------+-------------+------+-----+---------+-------+
3 rows in set (0.00 sec)
```

### delete_unique_key

```
mysql> ALTER TABLE tb_dept1
    -> DROP INDEX unique_name;
Query OK, 0 rows affected (0.20 sec)
Records: 0  Duplicates: 0  Warnings: 0

mysql> DESC tb_dept1;
+----------+-------------+------+-----+---------+-------+
| Field    | Type        | Null | Key | Default | Extra |
+----------+-------------+------+-----+---------+-------+
| id       | int(11)     | NO   | PRI | NULL    |       |
| name     | varchar(22) | NO   |     | NULL    |       |
| location | varchar(50) | YES  |     | NULL    |       |
+----------+-------------+------+-----+---------+-------+
3 rows in set (0.00 sec)
```

### set_check_constraint

```
mysql> CREATE TABLE tb_testcheck
    -> (
    -> id INT(11) PRIMARY KEY,
    -> name VARCHAR(25),
    -> deptId INT(11),
    -> salary FLOAT,
    -> CHECK(salary>0 AND salary <100),
    -> extend VARCHAR(25)
    -> );
Query OK, 0 rows affected, 2 warnings (0.05 sec)

mysql> SHOW CREATE TABLE tb_testcheck \G;
*************************** 1. row ***************************
       Table: tb_testcheck
Create Table: CREATE TABLE `tb_testcheck` (
  `id` int NOT NULL AUTO_INCREMENT,
  `name` varchar(25) DEFAULT NULL,
  `deptId` int DEFAULT NULL,
  `salary` float DEFAULT NULL,
  `extend` varchar(25) DEFAULT NULL,
  PRIMARY KEY (`id`),
  CONSTRAINT `tb_testcheck_chk_1` CHECK (((`salary` > 0) and (`salary` < 100)))
) ENGINE=InnoDB AUTO_INCREMENT=2 DEFAULT CHARSET=utf8
1 row in set (0.00 sec)

ERROR:
No query specified

mysql> ALTER TABLE tb_testcheck  CHANGE id id INT AUTO_INCREMENT
    -> ;
Query OK, 0 rows affected (0.07 sec)
Records: 0  Duplicates: 0  Warnings: 0

mysql> INSERT INTO tb_testcheck(salary) VALUES(4);
Query OK, 1 row affected (0.00 sec)

mysql> INSERT INTO tb_testcheck(salary) VALUES(900);
ERROR 3819 (HY000): Check constraint 'tb_testcheck_chk_1' is violated.
```

### set_default_constraint

```
mysql> CREATE TABLE tb_dept3
    -> (
    -> id INT(11) PRIMARY KEY,
    -> name VARCHAR(22),
    -> location VARCHAR(50) DEFAULT 'Beijing'
    -> );
Query OK, 0 rows affected (0.37 sec)

mysql> DESC tb_dept3;
+----------+-------------+------+-----+---------+-------+
| Field    | Type        | Null | Key | Default | Extra |
+----------+-------------+------+-----+---------+-------+
| id       | int(11)     | NO   | PRI | NULL    |       |
| name     | varchar(22) | YES  |     | NULL    |       |
| location | varchar(50) | YES  |     | Beijing |       |
+----------+-------------+------+-----+---------+-------+
3 rows in set (0.06 sec)
```

### add_default_constraint

```
mysql> ALTER TABLE tb_dept3
    -> CHANGE COLUMN location
    -> location VARCHAR(50) DEFAULT 'Shanghai';
Query OK, 0 rows affected (0.15 sec)
Records: 0  Duplicates: 0  Warnings: 0

mysql> DESC tb_dept3;
+----------+-------------+------+-----+----------+-------+
| Field    | Type        | Null | Key | Default  | Extra |
+----------+-------------+------+-----+----------+-------+
| id       | int(11)     | NO   | PRI | NULL     |       |
| name     | varchar(22) | YES  |     | NULL     |       |
| location | varchar(50) | YES  |     | Shanghai |       |
+----------+-------------+------+-----+----------+-------+
3 rows in set (0.00 sec)
```

### delete_default_constraint

```
ALTER TABLE <数据表名>
CHANGE COLUMN <字段名> <字段名> <数据类型> DEFAULT NULL;
```

### set_notnull_constraint

```
mysql> CREATE TABLE tb_dept4
    -> (
    -> id INT(11) PRIMARY KEY,
    -> name VARCHAR(22) NOT NULL,
    -> location VARCHAR(50)
    -> );
Query OK, 0 rows affected (0.37 sec)

mysql> DESC tb_dept3;
+----------+-------------+------+-----+---------+-------+
| Field    | Type        | Null | Key | Default | Extra |
+----------+-------------+------+-----+---------+-------+
| id       | int(11)     | NO   | PRI | NULL    |       |
| name     | varchar(22) | NO   |     | NULL    |       |
| location | varchar(50) | YES  |     | NULL    |       |
+----------+-------------+------+-----+---------+-------+
3 rows in set (0.06 sec)
```

### add_notnull_constraint

```
ALTER TABLE <数据表名>
CHANGE COLUMN <字段名>
<字段名> <数据类型> NOT NULL;
```

```
mysql> ALTER TABLE tb_dept4
    -> CHANGE COLUMN location
    -> location VARCHAR(50) NOT NULL;
Query OK, 0 rows affected (0.15 sec)
Records: 0  Duplicates: 0  Warnings: 0

mysql> DESC tb_dept4;
+----------+-------------+------+-----+----------+-------+
| Field    | Type        | Null | Key | Default  | Extra |
+----------+-------------+------+-----+----------+-------+
| id       | int(11)     | NO   | PRI | NULL     |       |
| name     | varchar(22) | NO   |     | NULL     |       |
| location | varchar(50) | NO   |     | NULL     |       |
+----------+-------------+------+-----+----------+-------+
3 rows in set (0.00 sec)
```

### delete_notnull_constraint

```
mysql> ALTER TABLE tb_dept4
    -> CHANGE COLUMN location
    -> location VARCHAR(50) NULL;
Query OK, 0 rows affected (0.15 sec)
Records: 0  Duplicates: 0  Warnings: 0

mysql> DESC tb_dept4;
+----------+-------------+------+-----+----------+-------+
| Field    | Type        | Null | Key | Default  | Extra |
+----------+-------------+------+-----+----------+-------+
| id       | int(11)     | NO   | PRI | NULL     |       |
| name     | varchar(22) | NO   |     | NULL     |       |
| location | varchar(50) | YES  |     | NULL     |       |
+----------+-------------+------+-----+----------+-------+
3 rows in set (0.00 sec)
```

### see_the_constraint

```
SHOW CREATE TABLE <数据表名>;
```

## FUNCTION_SQL

### select

```
SELECT
{* | <字段列名>}
[
FROM <表 1>, <表 2>…
[WHERE <表达式>
[GROUP BY <group by definition>
[HAVING <expression> [{<operator> <expression>}…]]
[ORDER BY <order by definition>]
[LIMIT[<offset>,] <row count>]
]
```

### 	INSERT

```
INSERT INTO <表名> [ <列名1> [ , … <列名n>] ]
VALUES (值1) [… , (值n) ];
```

```
INSERT INTO <表名>
SET <列名1> = <值1>,
        <列名2> = <值2>,
        …
```

```
mysql> INSERT INTO tb_courses_new
    -> (course_id,course_name,course_grade,course_info)
    -> SELECT course_id,course_name,course_grade,course_info
    -> FROM tb_courses;
Query OK, 4 rows affected (0.17 sec)
Records: 4  Duplicates: 0  Warnings: 0
mysql> SELECT * FROM tb_courses_new;
+-----------+-------------+--------------+------------------+
| course_id | course_name | course_grade | course_info      |
+-----------+-------------+--------------+------------------+
|         1 | Network     |            3 | Computer Network |
|         2 | Database    |            3 | MySQL            |
|         3 | Java        |            4 | Java EE          |
|         4 | System      |            3 | Operating System |
+-----------+-------------+--------------+------------------+
4 rows in set (0.00 sec)
```

### query_without_repeat

```
SELECT DISTINCT <字段名> FROM <表名>;
```

- serval segments

```
mysql> SELECT DISTINCT name,age FROM student;
+----------+------+
| name     | age  |
+----------+------+
| zhangsan |   18 |
| lisi     |   19 |
| wangwu   |   18 |
| zhaoliu  |   18 |
| wangwu   |   20 |
+----------+------+
5 rows in set (0.00 sec)
```



#### return count

  ```
  mysql> SELECT COUNT(DISTINCT name,age) FROM student;
  +--------------------------+
  | COUNT(DISTINCT name,age) |
  +--------------------------+
  |                        5 |
  +--------------------------+
  1 row in set (0.01 sec)
  ```

#### another_name

```
<表名> [AS] <别名>	//可以在语句较长时被引用，如ORDER BY
```

```
SELECT
orderNumber [as] 'Order no.',
SUM(priceEach * quantityOrdered) [as] total
FROM
orderdetails
GROUP BY
'Order no.'
HAVING
total > 60000;
```

#### LIMIT

```
LIMIT 初始位置，记录数
LIMIT 记录数 OFFSET 初始位置
LIMIT 记录数
```

```
mysql> SELECT * FROM tb_students_info LIMIT 5 OFFSET 3;
+----+-------+---------+------+------+--------+------------+
| id | name  | dept_id | age  | sex  | height | login_date |
+----+-------+---------+------+------+--------+------------+
|  4 | Jane  |       1 |   22 | F    |    162 | 2016-12-20 |
|  5 | Jim   |       1 |   24 | M    |    175 | 2016-01-15 |
|  6 | John  |       2 |   21 | M    |    172 | 2015-11-11 |
|  7 | Lily  |       6 |   22 | F    |    165 | 2016-02-26 |
|  8 | Susan |       4 |   23 | F    |    170 | 2015-10-01 |
+----+-------+---------+------+------+--------+------------+
5 rows in set (0.00 sec)
```

#### ORDER

```
ORDER BY <字段名> [ASC|DESC]
```

```
#多字段，先按照左字段先排列
mysql> SELECT name,height FROM tb_students_info ORDER BY height,name;
+--------+--------+
| name   | height |
+--------+--------+
| Green  |    158 |
| Dany   |    160 |
| Jane   |    162 |
| Lily   |    165 |
| Tom    |    165 |
| Susan  |    170 |
| John   |    172 |
| Jim    |    175 |
| Thomas |    178 |
| Henry  |    185 |
+--------+--------+
10 rows in set (0.09 sec)
```



```
mysql> SELECT name,height FROM tb_student_info ORDER BY height DESC,name ASC;
+--------+--------+
| name   | height |
+--------+--------+
| Henry  |    185 |
| Thomas |    178 |
| Jim    |    175 |
| John   |    172 |
| Susan  |    170 |
| Lily   |    165 |
| Tom    |    165 |
| Jane   |    162 |
| Dany   |    160 |
| Green  |    158 |
+--------+--------+
10 rows in set (0.00 sec)
```



#### WHERE

```
WHERE 查询条件
```

```
mysql> SELECT name,height FROM tb_students_info
    -> WHERE height=170;
+-------+--------+
| name  | height |
+-------+--------+
| Susan |    170 |
+-------+--------+
1 row in set (0.17 sec)
```



#### LIKE

````
[NOT] LIKE  '字符串'
````

```
mysql> SELECT name FROM tb_students_info
    -> WHERE name LIKE 'T%';
+--------+
| name   |
+--------+
| Thomas |
| Tom    |
+--------+
2 rows in set (0.12 sec)
```

```
#_代表一个任意字符
mysql> SELECT name FROM tb_students_info
    -> WHERE name LIKE '____y';
+-------+
| name  |
+-------+
| Henry |
+-------+
1 row in set (0.00 sec)
```

```

#默认不区分大小写
mysql> SELECT name FROM tb_students_info WHERE name LIKE 't%';
+--------+
| name   |
+--------+
| Thomas |
| Tom    |
+--------+
2 rows in set (0.00 sec)
# 区分大小写
mysql> SELECT name FROM tb_students_info WHERE name LIKE BINARY 't%';
Empty set (0.01 sec)
```

#### BETWEEN

```
[NOT] BETWEEN 取值1 AND 取值2
```

```
mysql> SELECT name,age FROM tb_students_info
    -> WHERE age BETWEEN 20 AND 23;
+--------+------+
| name   | age  |
+--------+------+
| Green  |   23 |
| Henry  |   23 |
| Jane   |   22 |
| John   |   21 |
| Lily   |   22 |
| Susan  |   23 |
| Thomas |   22 |
| Tom    |   23 |
+--------+------+
8 rows in set (0.00 sec)
```

#### IS [NOT] NULL

```
mysql> SELECT `name`,`login_date` FROM tb_students_info
    -> WHERE login_date IS NULL;
+--------+------------+
| NAME   | login_date |
+--------+------------+
| Dany   | NULL       |
| Green  | NULL       |
| Henry  | NULL       |
| Jane   | NULL       |
| Thomas | NULL       |
| Tom    | NULL       |
+--------+------------+
6 rows in set (0.01 sec)
```

#### GROUP BY

```
GROUP BY  <字段名>
```

```
mysql> SELECT `sex`, GROUP_CONCAT(name) FROM tb_students_info
    -> GROUP BY sex;
+------+----------------------------+
| sex  | GROUP_CONCAT(name)         |
+------+----------------------------+
| 女   | Henry,Jim,John,Thomas,Tom  |
| 男   | Dany,Green,Jane,Lily,Susan |
+------+----------------------------+
2 rows in set (0.00 sec)
```

-  COUNT()，SUM()，AVG()，MAX() 和 MIN()

```
mysql> SELECT sex,GROUP_CONCAT(name) FROM tb_students_info
    ->GROUP BY sex WITH ROLLUP;
+------+------------------------------------------------------+
| sex  | GROUP_CONCAT(name)                                   |
+------+------------------------------------------------------+
| 女   | Henry,Jim,John,Thomas,Tom                            |
| 男   | Dany,Green,Jane,Lily,Susan                           |
| NULL | Henry,Jim,John,Thomas,Tom,Dany,Green,Jane,Lily,Susan |
+------+------------------------------------------------------+
3 rows in set (0.00 sec)
```

#### HAVING

```
但是 WHERE 和 HAVING 关键字也存在以下几点差异：
一般情况下，WHERE 用于过滤数据行，而 HAVING 用于过滤分组。
WHERE 查询条件中不可以使用聚合函数，而 HAVING 查询条件中可以使用聚合函数。
WHERE 在数据分组前进行过滤，而 HAVING 在数据分组后进行过滤 。
WHERE 针对数据库文件进行过滤，而 HAVING 针对查询结果进行过滤。也就是说，WHERE 根据数据表中的字段直接进行过滤，而 HAVING 是根据前面已经查询出的字段进行过滤。
WHERE 查询条件中不可以使用字段别名，而 HAVING 查询条件中可以使用字段别名。
```

```
mysql> SELECT name,sex FROM tb_students_info
    -> WHERE height>150;
+--------+------+
| name   | sex  |
+--------+------+
| Dany   | 男   |
| Green  | 男   |
| Henry  | 女   |
| Jane   | 男   |
| Jim    | 女   |
| John   | 女   |
| Lily   | 男   |
| Susan  | 男   |
| Thomas | 女   |
| Tom    | 女   |
+--------+------+
10 rows in set (0.00 sec)

mysql> SELECT name,sex FROM tb_students_info HAVING height>150;
ERROR 1054 (42S22): Unknown column 'height' in 'having clause'
```

```
mysql> SELECT GROUP_CONCAT(name),sex,height FROM tb_students_info
    -> GROUP BY height
    -> HAVING AVG(height)>170;
+--------------------+------+--------+
| GROUP_CONCAT(name) | sex  | height |
+--------------------+------+--------+
| John               | 女   |    172 |
| Jim                | 女   |    175 |
| Thomas             | 女   |    178 |
| Henry              | 女   |    185 |
+--------------------+------+--------+
4 rows in set (0.00 sec)

mysql> SELECT GROUP_CONCAT(name),sex,height FROM tb_students_info WHERE AVG(height)>170 GROUP BY height;
ERROR 1111 (HY000): Invalid use of group function
```

#### CROSS JOIN

```
SELECT <字段名> FROM <表1> CROSS JOIN <表2> [WHERE子句]

SELECT <字段名> FROM <表1>, <表2> [WHERE子句]

#返回结果就是两个表的笛卡尔积，返回结果数量就是两个表的数据行相乘
```

#### INNER JOIN

```
SELECT <字段名> FROM <表1> INNER JOIN <表2> [ON子句]
#内连接（INNER JOIN）主要通过设置连接条件的方式，来移除查询结果中某些数据行的交叉连接。简单来说，就是利用条件表达式来消除交叉连接的某些数据行。
#INNER JOIN 也可以使用 WHERE 子句指定连接条件，但是 INNER JOIN ... ON 语法是官方的标准写法，而且 WHERE 子句在某些时候会影响查询的性能。
```

#### OUTER JOIN

```
mysql> SELECT * FROM tb_course;
+----+-------------+
| id | course_name |
+----+-------------+
|  1 | Java        |
|  2 | MySQL       |
|  3 | Python      |
|  4 | Go          |
|  5 | C++         |
|  6 | HTML        |
+----+-------------+
6 rows in set (0.00 sec)

mysql> SELECT * FROM tb_students_info;
+----+--------+------+------+--------+-----------+
| id | name   | age  | sex  | height | course_id |
+----+--------+------+------+--------+-----------+
|  1 | Dany   |   25 | 男   |    160 |         1 |
|  2 | Green  |   23 | 男   |    158 |         2 |
|  3 | Henry  |   23 | 女   |    185 |         1 |
|  4 | Jane   |   22 | 男   |    162 |         3 |
|  5 | Jim    |   24 | 女   |    175 |         2 |
|  6 | John   |   21 | 女   |    172 |         4 |
|  7 | Lily   |   22 | 男   |    165 |         4 |
|  8 | Susan  |   23 | 男   |    170 |         5 |
|  9 | Thomas |   22 | 女   |    178 |         5 |
| 10 | Tom    |   23 | 女   |    165 |         5 |
| 11 | LiMing |   22 | 男   |    180 |         7 |
+----+--------+------+------+--------+-----------+
11 rows in set (0.00 sec)
```

```
#  LEFT OUTER JOIN
mysql> SELECT s.name,c.course_name FROM tb_students_info s LEFT OUTER JOIN tb_course c
    -> ON s.`course_id`=c.`id`;
+--------+-------------+
| name   | course_name |
+--------+-------------+
| Dany   | Java        |
| Henry  | Java        |
| NULL   | Java        |
| Green  | MySQL       |
| Jim    | MySQL       |
| Jane   | Python      |
| John   | Go          |
| Lily   | Go          |
| Susan  | C++         |
| Thomas | C++         |
| Tom    | C++         |
| LiMing | NULL        |
+--------+-------------+
12 rows in set (0.00 sec)
```

```
# RIGHT OUTER JOIN
mysql> SELECT s.name,c.course_name FROM tb_students_info s RIGHT OUTER JOIN tb_course c
    -> ON s.`course_id`=c.`id`;
+--------+-------------+
| name   | course_name |
+--------+-------------+
| Dany   | Java        |
| Green  | MySQL       |
| Henry  | Java        |
| Jane   | Python      |
| Jim    | MySQL       |
| John   | Go          |
| Lily   | Go          |
| Susan  | C++         |
| Thomas | C++         |
| Tom    | C++         |
| NULL   | HTML        |
+--------+-------------+
11 rows in set (0.00 sec)
```

#### 子查询

```
WHERE <表达式> <操作符> (子查询)
```

```
mysql> SELECT name FROM tb_students_info
    -> WHERE course_id IN (SELECT id FROM tb_course WHERE course_name = 'Java');
+-------+
| name  |
+-------+
| Dany  |
| Henry |
+-------+
2 rows in set (0.01 sec)
# 先跑子语句，再跑父语句
```

```
1) 子查询语句可以嵌套在 SQL 语句中任何表达式出现的位置
2) 只出现在子查询中而没有出现在父查询中的表不能包含在输出列中,应该为子查询结果集指定别名
```

#### **REGEXP**



| 选项         | 说明                                  | 例子                                       | 匹配值示例                 |
| ------------ | ------------------------------------- | ------------------------------------------ | -------------------------- |
| ^            | 匹配文本的开始字符                    | '^b' 匹配以字母 b 开头的字符串             | book、big、banana、bike    |
| $            | 匹配文本的结束字符                    | 'st$' 匹配以 st 结尾的字符串               | test、resist、persist      |
| .            | 匹配任何单个字符                      | 'b.t' 匹配任何 b 和 t 之间有一个字符       | bit、bat、but、bite        |
| *            | 匹配零个或多个在它前面的字符          | 'f*n' 匹配字符 n 前面有任意个字符 f        | fn、fan、faan、abcn        |
| +            | 匹配前面的字符 1 次或多次             | 'ba+' 匹配以 b 开头，后面至少紧跟一个 a    | ba、bay、bare、battle      |
| <字符串>     | 匹配包含指定字符的文本                | 'fa' 匹配包含‘fa’的文本                    | fan、afa、faad             |
| [字符集合]   | 匹配字符集合中的任何一个字符          | '[xz]' 匹配 x 或者 z                       | dizzy、zebra、x-ray、extra |
| [^]          | 匹配不在括号中的任何字符              | '[^abc]' 匹配任何不包含 a、b 或 c 的字符串 | desk、fox、f8ke            |
| 字符串{n,}   | 匹配前面的字符串至少 n 次             | 'b{2}' 匹配 2 个或更多的 b                 | bbb、bbbb、bbbbbbb         |
| 字符串 {n,m} | 匹配前面的字符串至少 n 次， 至多 m 次 | 'b{2,4}' 匹配最少 2 个，最多 4 个 b        | bbb、bbbb                  |

```
mysql> SELECT * FROM tb_students_info
    -> WHERE name REGEXP '[^a-t]' ;
+----+-------+------+------+--------+-----------+
| id | name  | age  | sex  | height | course_id |
+----+-------+------+------+--------+-----------+
|  1 | Dany  |   25 | 男   |    160 |         1 |
|  3 | Henry |   23 | 女   |    185 |         1 |
|  7 | Lily  |   22 | 男   |    165 |         4 |
|  8 | Susan |   23 | 男   |    170 |         5 |
+----+-------+------+------+--------+-----------+
4 rows in set (0.00 sec)
```

### UPDATE

```
UPDATE <表名> SET 字段 1=值 1 [,字段 2=值 2… ] [WHERE 子句 ]
[ORDER BY 子句] [LIMIT 子句]
```

```
mysql> UPDATE tb_courses_new
    -> SET course_grade=4;
Query OK, 3 rows affected (0.11 sec)
Rows matched: 4  Changed: 3  Warnings: 0
mysql> SELECT * FROM tb_courses_new;
+-----------+-------------+--------------+------------------+
| course_id | course_name | course_grade | course_info      |
+-----------+-------------+--------------+------------------+
|         1 | Network     |            4 | Computer Network |
|         2 | Database    |            4 | MySQL            |
|         3 | Java        |            4 | Java EE          |
|         4 | System      |            4 | Operating System |
+-----------+-------------+--------------+------------------+
4 rows in set (0.00 sec)
```

### DELETE

```
DELETE FROM <表名> [WHERE 子句] [ORDER BY 子句] [LIMIT 子句]
```

```
mysql> DELETE FROM tb_courses_new;
Query OK, 3 rows affected (0.12 sec)
mysql> SELECT * FROM tb_courses_new;
Empty set (0.00 sec)
```

### **TRUNCATE**

```
TRUNCATE [TABLE] 表名
#cleanup table
```

### check_mode

```
mysql> select @@sql_mode
    -> ;
+-----------------------------------------------------------------------------------------------------------------------+
| @@sql_mode                                                                                                            |
+-----------------------------------------------------------------------------------------------------------------------+
| ONLY_FULL_GROUP_BY,STRICT_TRANS_TABLES,NO_ZERO_IN_DATE,NO_ZERO_DATE,ERROR_FOR_DIVISION_BY_ZERO,NO_ENGINE_SUBSTITUTION |
+-----------------------------------------------------------------------------------------------------------------------+
1 row in set (0.00 sec)
```

## 视图、索引、存储过程、触发器

```
视图在数据库中的作用类似于窗户，用户可以通过这个窗口看到只对自己有用的数据。既保障了数据的安全性，又大大提高了查询效率。

索引是提高数据库性能的重要方式，用来快速找出数据表中的特定记录。如果在表中查询的列有一个索引，MySQL 能快速到达一个位置去搜寻数据，而不必查看所有数据。

存储过程是在数据库中定义一些 SQL 语句的集合，可以直接调用这些存储过程来执行已经定义好的 SQL 语句。避免了开发人员重复编写相同 SQL 语句的问题。

触发器和存储过程相似，都是嵌入到 MySQL 中的一段程序。触发器是由事件来触发某个操作。当数据库执行这些事件时，就会激活触发器来执行相应的操作。
```

#### create_view

```
CREATE VIEW <视图名> AS <SELECT语句>
```



```
mysql> CREATE VIEW view_tb_student
    -> AS SELECT * FROM tb_student;
Query OK, 0 rows affected (0.01 sec)

mysql> SELECT * FROM view_tb_student;
+------+------------+--------------+------+--------+
| age  | birthday   | student_name | sex  | fruit  |
+------+------------+--------------+------+--------+
|   18 | 2002-01-07 | gggd         | 1    | banana |
|   18 | 2002-01-07 | Jgddhh       | 1    | apple  |
|   10 | 2002-01-07 | Jggfhh       | 1    | apple  |
|   18 | 2002-01-07 | Joe          | 1    | apple  |
|   18 | 2002-01-07 | Joehh        | 1    | apple  |
| NULL | NULL       | sxy          | NULL | NULL   |
+------+------------+--------------+------+--------+
6 rows in set (0.00 sec)

mysql> DESC view_tb_student;
+--------------+-------------+------+-----+---------+-------+
| Field        | Type        | Null | Key | Default | Extra |
+--------------+-------------+------+-----+---------+-------+
| age          | int         | YES  |     | NULL    |       |
| birthday     | date        | YES  |     | NULL    |       |
| student_name | varchar(25) | NO   |     | NULL    |       |
| sex          | varchar(11) | YES  |     | NULL    |       |
| fruit        | varchar(11) | YES  |     | NULL    |       |
+--------------+-------------+------+-----+---------+-------+
5 rows in set (0.00 sec)
```

#### modify_view

```
ALTER VIEW <视图名> AS <SELECT语句>
```



```
mysql> ALTER VIEW view_tb_student
    -> AS SELECT student_name
    -> FROM tb_student;
Query OK, 0 rows affected (0.01 sec)

mysql> SELECT * FROM view_tb_student;
+--------------+
| student_name |
+--------------+
| sxy          |
| Jgddhh       |
| Jggfhh       |
| Joe          |
| Joehh        |
| gggd         |
+--------------+
6 rows in set (0.00 sec)
```

### delete_view

```
DROP VIEW <视图名1> [ , <视图名2> …]
```

```
mysql> DROP VIEW IF EXISTS v_students_info;
Query OK, 0 rows affected (0.00 sec)
mysql> SHOW CREATE VIEW v_students_info;
ERROR 1146 (42S02): Table 'test_db.v_students_info' doesn't exist
```



## INDEX

```
在经常需要搜索的列上建立索引，可以加快搜索的速度。
在作为主键的列上创建索引，强制该列的唯一性，并组织表中数据的排列结构。
在经常使用表连接的列上创建索引，这些列主要是一些外键，可以加快表连接的速度。
在经常需要根据范围进行搜索的列上创建索引，因为索引已经排序，所以其指定的范围是连续的。
在经常需要排序的列上创建索引，因为索引已经排序，所以查询时可以利用索引的排序，加快排序查询。
在经常使用 WHERE 子句的列上创建索引，加快条件的判断速度。
```

### create_index

```
CREATE <索引名> ON <表名> (<列名> [<长度>] [ ASC | DESC])
```

```
mysql> CREATE INDEX index_student ON tb_student(student_name);
Query OK, 0 rows affected (0.02 sec)
Records: 0  Duplicates: 0  Warnings: 0
```

```
mysql> SHOW INDEX FROM tb_student \G;
*************************** 1. row ***************************
        Table: tb_student
   Non_unique: 0
     Key_name: PRIMARY
 Seq_in_index: 1
  Column_name: student_name
    Collation: A
  Cardinality: 6
     Sub_part: NULL
       Packed: NULL
         Null:
   Index_type: BTREE
      Comment:
Index_comment:
      Visible: YES
   Expression: NULL
*************************** 2. row ***************************
        Table: tb_student
   Non_unique: 1
     Key_name: fk_student_like_fruit
 Seq_in_index: 1
  Column_name: fruit
    Collation: A
  Cardinality: 3
     Sub_part: NULL
       Packed: NULL
         Null: YES
   Index_type: BTREE
      Comment:
Index_comment:
      Visible: YES
   Expression: NULL
*************************** 3. row ***************************
        Table: tb_student
   Non_unique: 1
     Key_name: index_student
 Seq_in_index: 1
  Column_name: student_name
    Collation: A
  Cardinality: 6
     Sub_part: NULL
       Packed: NULL
         Null:
   Index_type: BTREE
      Comment:
Index_comment:
      Visible: YES
   Expression: NULL
3 rows in set (0.00 sec)

ERROR:
No query specified

mysql> SHOW CREATE TABLE tb_student \G;
*************************** 1. row ***************************
       Table: tb_student
Create Table: CREATE TABLE `tb_student` (
  `age` int DEFAULT NULL,
  `birthday` date DEFAULT NULL,
  `student_name` varchar(25) NOT NULL,
  `sex` varchar(11) DEFAULT NULL,
  `fruit` varchar(11) DEFAULT NULL,
  PRIMARY KEY (`student_name`),
  KEY `fk_student_like_fruit` (`fruit`),
  KEY `index_student` (`student_name`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8
1 row in set (0.00 sec)

ERROR:
No query specified
```

### delete_index

```
mysql> DROP INDEX index_student ON tb_student;
Query OK, 0 rows affected (0.02 sec)
Records: 0  Duplicates: 0  Warnings: 0

mysql> SHOW INDEX FROM tb_student \G;
*************************** 1. row ***************************
        Table: tb_student
   Non_unique: 0
     Key_name: PRIMARY
 Seq_in_index: 1
  Column_name: student_name
    Collation: A
  Cardinality: 6
     Sub_part: NULL
       Packed: NULL
         Null:
   Index_type: BTREE
      Comment:
Index_comment:
      Visible: YES
   Expression: NULL
*************************** 2. row ***************************
        Table: tb_student
   Non_unique: 1
     Key_name: fk_student_like_fruit
 Seq_in_index: 1
  Column_name: fruit
    Collation: A
  Cardinality: 3
     Sub_part: NULL
       Packed: NULL
         Null: YES
   Index_type: BTREE
      Comment:
Index_comment:
      Visible: YES
   Expression: NULL
2 rows in set (0.00 sec)

ERROR:
No query specified
```

```
mysql> ALTER TABLE tb_student
    -> DROP INDEX fk_student_like_fruit;
Query OK, 0 rows affected (0.01 sec)
Records: 0  Duplicates: 0  Warnings: 0

mysql> SHOW CREATE TABLE tb_student \G;
*************************** 1. row ***************************
       Table: tb_student
Create Table: CREATE TABLE `tb_student` (
  `age` int DEFAULT NULL,
  `birthday` date DEFAULT NULL,
  `student_name` varchar(25) NOT NULL,
  `sex` varchar(11) DEFAULT NULL,
  `fruit` varchar(11) DEFAULT NULL,
  PRIMARY KEY (`student_name`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8
1 row in set (0.00 sec)

ERROR:
No query specified
```



### 存储过程 PROCEDURE

```
1) 封装性
2) 可增强 SQL 语句的功能和灵活性
3) 可减少网络流量
4) 高性能
5) 提高数据库的安全性和数据的完整性
6) 使数据独立
```

#### create_procedure

```
CREATE PROCEDURE <过程名> ( [过程参数[,…] ] ) <过程体>
[过程参数[,…] ] 格式
[ IN | OUT | INOUT ] <参数名> <类型>
```

```
mysql> DELIMITER //
mysql> CREATE PROCEDURE ShowStudent()
    -> BEGIN
    -> SELECT * FROM tb_student;
    -> END //
Query OK, 0 rows affected (0.01 sec)

mysql> DELIMITER ;
mysql> CALL ShowStudent();
+------+------------+--------------+------+--------+
| age  | birthday   | student_name | sex  | fruit  |
+------+------------+--------------+------+--------+
|   18 | 2002-01-07 | gggd         | 1    | banana |
|   18 | 2002-01-07 | Jgddhh       | 1    | apple  |
|   10 | 2002-01-07 | Jggfhh       | 1    | apple  |
|   18 | 2002-01-07 | Joe          | 1    | apple  |
|   18 | 2002-01-07 | Joehh        | 1    | apple  |
| NULL | NULL       | sxy          | NULL | NULL   |
+------+------------+--------------+------+--------+
6 rows in set (0.00 sec)

Query OK, 0 rows affected (0.01 sec)
```
### search_procedure
```
#可以使用 SHOW PROCEDURE STATUS 命令查看数据库中存在哪些存储过程
#若要查看某个存储过程的具体信息，则可以使用 SHOW CREATE PROCEDURE <存储过程名>。
mysql>  SHOW CREATE PROCEDURE ShowStudent\G;
*************************** 1. row ***************************
           Procedure: ShowStudent
            sql_mode: ONLY_FULL_GROUP_BY,STRICT_TRANS_TABLES,NO_ZERO_IN_DATE,NO_ZERO_DATE,ERROR_FOR_DIVISION_BY_ZERO,NO_ENGINE_SUBSTITUTION
    Create Procedure: CREATE DEFINER=`root`@`localhost` PROCEDURE `ShowStudent`()
BEGIN
SELECT * FROM tb_student;
END
character_set_client: utf8
collation_connection: utf8_general_ci
  Database Collation: utf8_general_ci
1 row in set (0.00 sec)
```

```
mysql> DELIMITER //
mysql> CREATE PROCEDURE GetStudentByName
    -> (In name VARCHAR(30))
    -> BEGIN
    -> SELECT * FROM tb_student
    -> WHERE student_name=name;
    -> END //
Query OK, 0 rows affected (0.00 sec)

mysql> DELIMITER ;
mysql> CALL GetStudentByName('Joe');
+------+------------+--------------+------+-------+
| age  | birthday   | student_name | sex  | fruit |
+------+------------+--------------+------+-------+
|   18 | 2002-01-07 | Joe          | 1    | apple |
+------+------------+--------------+------+-------+
1 row in set (0.00 sec)

Query OK, 0 rows affected, 1 warning (0.01 sec)

mysql> SHOW PROCEDURE STATUS LIKE '%Student%';
+-----------------+------------------+-----------+----------------+---------------------+---------------------+---------------+---------+----------------------+----------------------+--------------------+
| Db              | Name             | Type      | Definer        | Modified            | Created             | Security_type | Comment | character_set_client | collation_connection | Database Collation |
+-----------------+------------------+-----------+----------------+---------------------+---------------------+---------------+---------+----------------------+----------------------+--------------------+
| tb_student_info | GetStudentByName | PROCEDURE | root@localhost | 2020-05-27 11:21:21 | 2020-05-27 11:21:21 | DEFINER       |         | utf8                 | utf8_general_ci      | utf8_general_ci    |
| tb_student_info | ShowStudent      | PROCEDURE | root@localhost | 2020-05-27 11:15:09 | 2020-05-27 11:15:09 | DEFINER       |         | utf8                 | utf8_general_ci      | utf8_general_ci    |
+-----------------+------------------+-----------+----------------+---------------------+---------------------+---------------+---------+----------------------+----------------------+--------------------+
2 rows in set (0.00 sec)
```

### modify_procedure_feature

```
ALTER PROCEDURE 存储过程名 [ 特征 ... ]
特征指定了存储过程的特性，可能的取值有：
CONTAINS SQL 表示子程序包含 SQL 语句，但不包含读或写数据的语句。
NO SQL 表示子程序中不包含 SQL 语句。
READS SQL DATA 表示子程序中包含读数据的语句。
MODIFIES SQL DATA 表示子程序中包含写数据的语句。
SQL SECURITY { DEFINER |INVOKER } 指明谁有权限来执行。
DEFINER 表示只有定义者自己才能够执行。
INVOKER 表示调用者可以执行。
COMMENT 'string' 表示注释信息。
# 若需要修改函数名和函数定义，则需要删除原存储过程
```

### delete_procedure

```
mysql> DROP PROCEDURE GetStudentByName;
Query OK, 0 rows affected (0.01 sec)

mysql> SHOW PROCEDURE STATUS LIKE '%Student%';
+-----------------+-------------+-----------+----------------+---------------------+---------------------+---------------+---------+----------------------+----------------------+--------------------+
| Db              | Name        | Type      | Definer        | Modified            | Created             | Security_type | Comment | character_set_client | collation_connection | Database Collation |
+-----------------+-------------+-----------+----------------+---------------------+---------------------+---------------+---------+----------------------+----------------------+--------------------+
| tb_student_info | ShowStudent | PROCEDURE | root@localhost | 2020-05-27 11:15:09 | 2020-05-27 11:15:09 | DEFINER       |         | utf8                 | utf8_general_ci      | utf8_general_ci    |
+-----------------+-------------+-----------+----------------+---------------------+---------------------+---------------+---------+----------------------+----------------------+--------------------+
1 row in set (0.00 sec)

```

### TRIGGER

#### create_trigger

```
mysql> CREATE TRIGGER SumOfAge
    -> BEFORE INSERT ON tb_student
    -> FOR EACH ROW
    -> SET @sum=@sum+NEW.age;
Query OK, 0 rows affected (0.01 sec)

mysql> SET @sum=0;
Query OK, 0 rows affected (0.01 sec)

mysql> INSERT INTO tb_student
    -> VALUES(20,'2000-5-8','INTOhelo',0,'peach');
Query OK, 1 row affected (0.01 sec)

mysql> SELECT @sum;
+------+
| @sum |
+------+
|   40 |
+------+
1 row in set (0.00 sec)

mysql> INSERT INTO tb_student
    -> VALUES(28,'2000-5-8','sparklo',0,'peach');
Query OK, 1 row affected (0.01 sec)

mysql> SELECT @sum;
+------+
| @sum |
+------+
|   68 |
+------+
1 row in set (0.00 sec)
```

#### show_trigger

```
mysql> SHOW TRIGGERS\G;
*************************** 1. row ***************************
             Trigger: SumOfAge
               Event: INSERT
               Table: tb_student
           Statement: SET @sum=@sum+NEW.age
              Timing: BEFORE
             Created: 2020-05-27 11:47:53.10
            sql_mode: ONLY_FULL_GROUP_BY,STRICT_TRANS_TABLES,NO_ZERO_IN_DATE,NO_ZERO_DATE,ERROR_FOR_DIVISION_BY_ZERO,NO_ENGINE_SUBSTITUTION
             Definer: root@localhost
character_set_client: utf8
collation_connection: utf8_general_ci
  Database Collation: utf8_general_ci
1 row in set (0.00 sec)

ERROR:
No query specified
```

```
mysql> SELECT * FROM information_schema.triggers WHERE trigger_name= 'SumOfAge'\G;
*************************** 1. row ***************************
           TRIGGER_CATALOG: def
            TRIGGER_SCHEMA: tb_student_info
              TRIGGER_NAME: SumOfAge
        EVENT_MANIPULATION: INSERT
      EVENT_OBJECT_CATALOG: def
       EVENT_OBJECT_SCHEMA: tb_student_info
        EVENT_OBJECT_TABLE: tb_student
              ACTION_ORDER: 1
          ACTION_CONDITION: NULL
          ACTION_STATEMENT: SET @sum=@sum+NEW.age
        ACTION_ORIENTATION: ROW
             ACTION_TIMING: BEFORE
ACTION_REFERENCE_OLD_TABLE: NULL
ACTION_REFERENCE_NEW_TABLE: NULL
  ACTION_REFERENCE_OLD_ROW: OLD
  ACTION_REFERENCE_NEW_ROW: NEW
                   CREATED: 2020-05-27 11:47:53.10
                  SQL_MODE: ONLY_FULL_GROUP_BY,STRICT_TRANS_TABLES,NO_ZERO_IN_DATE,NO_ZERO_DATE,ERROR_FOR_DIVISION_BY_ZERO,NO_ENGINE_SUBSTITUTION
                   DEFINER: root@localhost
      CHARACTER_SET_CLIENT: utf8
      COLLATION_CONNECTION: utf8_general_ci
        DATABASE_COLLATION: utf8_general_ci
1 row in set (0.00 sec)

ERROR:
No query specified
```

#### delete_trigger

```
DROP TRIGGER [ IF EXISTS ] [数据库名] <触发器名>
```



```
mysql> DROP TRIGGER SumOfAge;
Query OK, 0 rows affected (0.01 sec)
```

## EVENT

#### ifopen

```

mysql> SHOW VARIABLES LIKE 'event_scheduler';
+-----------------+-------+
| Variable_name   | Value |
+-----------------+-------+
| event_scheduler | ON    |
+-----------------+-------+
1 row in set (0.01 sec)

mysql> SELECT @@event_scheduler;
+-------------------+
| @@event_scheduler |
+-------------------+
| ON                |
+-------------------+
1 row in set (0.00 sec)

mysql> SHOW PROCESSLIST;
+----+-----------------+-----------------+-----------------+---------+-------+------------------------+------------------+
| Id | User            | Host            | db              | Command | Time  | State                  | Info             |
+----+-----------------+-----------------+-----------------+---------+-------+------------------------+------------------+
|  5 | event_scheduler | localhost       | NULL            | Daemon  | 91611 | Waiting on empty queue | NULL             |
| 36 | root            | localhost:57582 | tb_student_info | Query   |     0 | starting               | SHOW PROCESSLIST |
+----+-----------------+-----------------+-----------------+---------+-------+------------------------+------------------+
2 rows in set (0.00 sec)
```

#### turn_on_or_off_event

```
mysql>  SET GLOBAL event_scheduler = ON ;
Query OK, 0 rows affected (0.00 sec)

mysql> SHOW VARIABLES LIKE 'event_scheduler';
+-----------------+-------+
| Variable_name   | Value |
+-----------------+-------+
| event_scheduler | ON    |
+-----------------+-------+
1 row in set (0.00 sec)

mysql>  SET GLOBAL event_scheduler = OFF ;
Query OK, 0 rows affected (0.00 sec)

mysql> SHOW VARIABLES LIKE 'event_scheduler';
+-----------------+-------+
| Variable_name   | Value |
+-----------------+-------+
| event_scheduler | OFF   |
+-----------------+-------+
1 row in set (0.00 sec)
```

#### create_event

```
CREATE EVENT [IF NOT EXISTS] event_name
    ON SCHEDULE schedule
    [ON COMPLETION [NOT] PRESERVE]
    [ENABLE | DISABLE | DISABLE ON SLAVE]
    [COMMENT 'comment']
    DO event_body;
```

#### show_event
```
mysql> SELECT * FROM  information_schema.events\G;
*************************** 1. row ***************************
       EVENT_CATALOG: def
        EVENT_SCHEMA: tb_student_info
          EVENT_NAME: e_test
             DEFINER: root@localhost
           TIME_ZONE: SYSTEM
          EVENT_BODY: SQL
    EVENT_DEFINITION: INSERT INTO tb_eventtest(user,createtime)VALUES('MySQL',NOW())
          EVENT_TYPE: RECURRING
          EXECUTE_AT: NULL
      INTERVAL_VALUE: 5
      INTERVAL_FIELD: SECOND
            SQL_MODE: ONLY_FULL_GROUP_BY,STRICT_TRANS_TABLES,NO_ZERO_IN_DATE,NO_ZERO_DATE,ERROR_FOR_DIVISION_BY_ZERO,NO_ENGINE_SUBSTITUTION
              STARTS: 2020-05-27 13:38:17
                ENDS: NULL
              STATUS: ENABLED
       ON_COMPLETION: PRESERVE
             CREATED: 2020-05-27 13:38:17
        LAST_ALTERED: 2020-05-27 13:38:17
       LAST_EXECUTED: 2020-05-27 13:43:12
       EVENT_COMMENT:
          ORIGINATOR: 1
CHARACTER_SET_CLIENT: utf8
COLLATION_CONNECTION: utf8_general_ci
  DATABASE_COLLATION: utf8_general_ci
1 row in set (0.00 sec)

ERROR:
No query specified
```

```

mysql> SHOW EVENTS\G;
*************************** 1. row ***************************
                  Db: tb_student_info
                Name: e_test
             Definer: root@localhost
           Time zone: SYSTEM
                Type: RECURRING
          Execute at: NULL
      Interval value: 5
      Interval field: SECOND
              Starts: 2020-05-27 13:38:17
                Ends: NULL
              Status: ENABLED
          Originator: 1
character_set_client: utf8
collation_connection: utf8_general_ci
  Database Collation: utf8_general_ci
1 row in set (0.00 sec)

ERROR:
No query specified
```

#### change_event

```
mysql> ALTER EVENT e_test ON SCHEDULE EVERY 30 SECOND
    -> ON COMPLETION PRESERVE
    -> DO INSERT INTO tb_eventtest(user,createtime) VALUES('MySQL',NOW());
Query OK, 0 rows affected (0.00 sec)

mysql> SHOW EVENTS\G;
*************************** 1. row ***************************
                  Db: tb_student_info
                Name: e_test
             Definer: root@localhost
           Time zone: SYSTEM
                Type: RECURRING
          Execute at: NULL
      Interval value: 30
      Interval field: SECOND
              Starts: 2020-05-27 13:47:25
                Ends: NULL
              Status: ENABLED
          Originator: 1
character_set_client: utf8
collation_connection: utf8_general_ci
  Database Collation: utf8_general_ci
1 row in set (0.00 sec)

```

#### disable_event

```
mysql>  ALTER EVENT e_test DISABLE;
Query OK, 0 rows affected (0.01 sec)
```

#### delete_event

```
mysql>  DROP EVENT IF EXISTS e_test;
Query OK, 0 rows affected (0.01 sec)

mysql> SHOW EVENTS;
Empty set (0.00 sec)
```

## 事务 transaction

```
BEGIN;
START TRANSACTION;
COMMIT;
ROLLBACK;
# 确保autocommit为0，在执行事务时
SET autocommit = 0;
SHOW VARIABLES LIKE 'autocommit';
```

###  isolation_range

| 隔离级别        | 脏读 | 不可重复读 | 幻读 |
| --------------- | ---- | ---------- | ---- |
| READ UNCOMITTED | √    | √          | √    |
| READ COMMITTED  | ×    | √          | √    |
| REPEATABLE READ | ×    | ×          | √    |
| SERIALIZABLE    | ×    | ×          | ×    |



### show_isolation

```
+-----------------------+-----------------+
| Variable_name         | Value           |
+-----------------------+-----------------+
| transaction_isolation | REPEATABLE-READ |
+-----------------------+-----------------+
1 row in set (0.00 sec)
mysql> select @@transaction_isolation ;
+-------------------------+
| @@transaction_isolation |
+-------------------------+
| REPEATABLE-READ         |
+-------------------------+
1 row in set (0.00 sec)

mysql> select @@global.transaction_isolation ;
+--------------------------------+
| @@global.transaction_isolation |
+--------------------------------+
| REPEATABLE-READ                |
+--------------------------------+
1 row in set (0.00 sec)

mysql> select @@session.transaction_isolation ;
+---------------------------------+
| @@session.transaction_isolation |
+---------------------------------+
| REPEATABLE-READ                 |
+---------------------------------+
1 row in set (0.00 sec)
```

## user_manage


```
delete tb_uvsslabel as a
from tb_uvsslabel as a,
(select * from tb_uvsslabel group by small having count(1)>1) as b
where a.small=b.small
and a.id > b.id;
```

```
DELETE FROM tb_uvsslabel where id not in (select id from (select min(id) as id from tb_uvsslabel group by key) as b ) ;
```



## REFER

```
http://c.biancheng.net/mysql/
```
