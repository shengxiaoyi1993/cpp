# design_practical

## 说明
- 本文档用于设计使用mysql的基本封装库生成一个具体的数据库的方法。
- 涉及数据库的建立等实际操作，该库的基本功能结构和实现流程
- 相当于是一个附加功能库，使用时可以同时使用mysql_wrapper和本模块

## 功能
- 使用一个配置文件（json格式）生成一个数据库
- 多个语句结合的复合功能
- 数据库的打包
- 数据库的迁移
- 根据配置文件访问数据生成数据库的基本信息表

## 功能实现

### 使用配置文件生成一个数据库
#### 流程

```
- 读取JSON格式的配置文件
- 组合成数据库创建命令
- 连接至DBMS
- 进行一系列的创建
- 根据配置表中的项目检测数据库中数据情况
- 输出数据库检测列表
```

#### 过程设计
- JSON格式设计

```
//属性设计
//表属性创建
//表关系创建
- db
  - tb[]
    - Field       | Type             | Null | Key | Default | Extra
  - tb_relation


  +-------------+------------------+------+-----+---------+----------------+
  | Field       | Type             | Null | Key | Default | Extra          |
  +-------------+------------------+------+-----+---------+----------------+
  | id          | int(11) unsigned | NO   | PRI | NULL    | auto_increment |
  | dir         | char(128)        | YES  |     | NULL    |                |
  | big         | char(128)        | YES  |     | NULL    |                |
  | small       | char(128)        | YES  | MUL | NULL    |                |
  | label0      | float            | YES  |     | NULL    |                |
  | label1      | float            | YES  |     | NULL    |                |
  +-------------+------------------+------+-----+---------+----------------+

  CREATE TABLE `tb_with_single_key` (
    `id` int NOT NULL,
    `name` varchar(25) DEFAULT NULL,
    `sex` int DEFAULT NULL,
    PRIMARY KEY (`id`)
  ) ENGINE=InnoDB DEFAULT CHARSET=utf8

//实例
{
  "db":"DB_UVSS",
  "tbs":[
  //table0
  {
    "tb":"T_DATAITEM",
    "entry":[
    //entry0
    {
      "Field":"DATA_ID",
      "Type":"int(11) unsigned",
      "Null":"NOT NULL",
      "Key":"PRI",
      "Default":"NULL",
      "Extra":"auto_increment",
      "Note":""
    },
    //entry1
    {},
    ...
    ]

  },
  //table1
  {},
  ...
  ]
}


//目标操作
CREATE TABLE tb_empl
    -> (
    -> id INT(11),
    -> name VARCHAR(25),
    -> deptId INT(11),
    -> salary FLOAT
    -> );

```
