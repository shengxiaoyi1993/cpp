# design_mysql

## 需求
- 封装mysql使其便于理解和使用
- 充分测试，保证接口安全

## 接口设计
- 数据库操作  
  - 登陆数据库服务器  
  - 与数据库服务器断开连接（回调）
  - 查看数据库列表  
  - 创建数据库  
  - 删除数据库  
  - 退出登陆
  - 查看数据库
  - 创建/删除/查看数据库基本表
  - ...
- 数据操作
  - 增
  - 删
  - 改
  - 查
- 索引操作
- 原生操作 (query字符串)
- 易调试

## 过程记录
- q:mysql已有c++类库，是否需要重新封装需要根据类库是否满足使用需要
- 测试mysql的各项功能


## 应用场景分析
- 单一数据库
- 多张基本表
- 主表上的数据根据车牌号建立单张索引就行了
- 需要保证索引表在DBMS处理后仍可以正常使用

- 使用过程
```
- 单一用户登陆（保存用户有关的信息，连接状态等，数据库的重新登陆）
- 数据库管理
  - 建立数据库
- 索引管理
  - 将某一字段设置为数据库
- 建立数据库
- 数据表管理
- 建立多张表
- 插入数据样本（添加到索引表中）
```

## 功能
- 将需要翻译成query字符串
- 解析搜索结果

### DBMS
- 登陆与退出
- 系统功能设置
- 数据占用的空间
- 是否设置为自动提交

### 数据库
- 创建和删除数据库
- 输出已有的数据库的列表

### 基本表
- 创建和删除基本表
- 输出基本表的列表

### 数据操作
- 增删改查
- 某张索引进行查询
- 多张表的联合查询

### 索引操作
- 创建和删除索引
- 输出索引的列表


### faq
- 是否支持多并发
- 是否支持事务提交
- 是否将查询到的数据保存在本地
  - 不保存状态，就能支持多并发；
  - 只保留连接；
  - 连接的状态也不保存，返回周期性检查连接结果，每次进行数据操作时都要验证连接是否正常
- 编写程序时，是否需要数据表的概念：
- 是否需要设置对应的数据库，是否可以更改
- 是否可以更改登陆的用户？
- 是否可以更改登陆的服务器地址?