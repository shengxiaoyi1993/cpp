# note
## change the restore root
```
[sxy@localhost mysql]$ ps -ef | grep mysqld
mysql     2395     1  0 14:23 ?        00:00:00 /bin/sh /usr/bin/mysqld_safe --basedir=/usr
mysql     2592  2395  0 14:23 ?        00:00:00 /usr/sbin/mysqld --basedir=/usr --datadir=/var/lib/mysql --plugin-dir=/usr/lib64/mysql/plugin --log-error=/var/log/mysqld.log --pid-file=/var/run/mysqld/mysqld.pid --socket=/var/lib/mysql/mysql.sock
sxy       6485  5556  0 14:44 pts/2    00:00:00 grep --color=auto mysqld


[sxy@localhost Content]$ sudo mv /var/lib/mysql /home/
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

## 20200831
- 测试数据库要求
  - 1m数据
  - 包含label字段，车牌号字段
  - label与车牌号是否需要对应
    - 100-1000张车牌
    - 对于实际的车底库，相同车牌总是对应相同的车底图片



- 数据库测试
  - 在1m数据库中查找一条目标条目，计算所有的label使得到的差值最小

- 流程
  - 规划手动添加车牌号然后进行测试的方法
  - 构建测试数据库
    - 添加车牌号字段
    - 添加数据
  - 编写测试函数，进行测试

1. 验证`手动添加车牌号`的测试可行性和可信度

```shell
- 需要计算label的数据条目数量
- 总查找时间=取出一定检索条件内的所有数据+逐条计算label_distance
  - 1m中添加单1条件对取出数据条目时间的影响
    - 受到数据类型的影响
  - 1m数据计算每条数据的label值的时间，从而计算出总的时间长度
```

2. 构建数据库
  - 删除多余数据
  - 修改数据项：plate
    - plate的分布，首先生成1000个plate
    - 1000个plate按照一定规律分布，生成总数为1m的数据，取其中的一个随机元素 (100000 1 10000 1 1000 1 )
    - 然后取出随机元素，更新数据库项中的内容

3. 进行测试
  - 无条件全部取出：18s/1000k 1.8s/100k 0.21s/10k 0.056s/1k
  - 条目测试：增加一条检索条件对取出数据的时间:
    - 全部取出：18s/1000k(全部取出)
    - 设置条件:
        - 取出100000:5673398 us
        - 取出10000:4196728 us
        - 取出1000:4041390 us
        - 结果：
          - 取出数据：1.67/100k
          - 单一检索条件判断：4.0/1000k
          - 检验：双检索条件取出110k数据
            - 计算结果9.84s
            - 实际时间 5917314 us
          - 结论：
            - 在已有搜索条件的基础上添加检索条件不会增加太多时间消耗
            - 若之前没有检索条件，另外添加检索条件会大幅增加检索消耗
            - 时间消耗主要花费在数据拷贝上，首次添加检索条件可能也是因为数据比较需要先拷贝到内存中
            - 只要筛选条件能够过滤2/9的数据，就值得设置筛选条件；
      - 获取数据时间：取出数据时间（+检索时间）
        - 取出数据时间由取出的数据量决定
        - 检索时间大值是总数据量的正相关值，约为取出时间的2/9
  - 单条数据项：label计算花费的时间:20.5us/f

阶段性结论
  1. 若之前没有检索条件，另外添加检索条件会大幅增加检索消耗，该值与数据库规模正相关（4s/1000k）
  2. 在已有搜索条件的基础上添加检索条件不会增加太多时间消耗
  3. 时间消耗主要花费在数据拷贝上，首次添加检索条件可能也是因为数据比较需要先拷贝数据到内存中
  4. 根据计算，只要筛选条件能够过滤2/9的数据，就值得设置筛选条件；
  5. 控制查找的数据库的大小是必要的，数据规模在25k时，取出所有数据并计算所有数据的label_ditance找到最优值时间低于1s
有以下改进建议
  1. 将存入比对数据库的数据进行分类存储，进行最临近检索时，先对数据进行处理找到相应类别，然后找到对应的子数据库
  2. 人为限制比对数据的总大小，如果假设来往的车辆只有在1K以内，保存过多的条目在比对数据库也没有意义
  3. 对于每条数据设置一条匹配数据和时间，每次查找时只计算匹配时间之后的数据，除非手动设置（采用该条会导致某条数据刚添加到数据库时，搜索时间较长；同时需要在空闲时间进行数据的计算，使较早的历史数据保持较新的匹配结果）
  4. 检索时根据设定label的范围值，在范围内的区间的多少
  5. 改进计算label_distance的方法，提高速度
需要测试
  1. 查看数据label的分类方法
  2. 测试设置各个label值方法是否可用；label值的合理区间

```
  mysql> SELECT COUNT(*) FROM tb_uvsslabel;

//修改车牌号
>UPDATE tb_uvsslabel  set description='津E*M05K74'  WHERE id=1;
//修改字符集
>alter table tb_uvsslabel  modify description  char(10) character set gbk;
//
皖M*SCCMB: 1000
贵C*X7MMD: 10000
贵F*99HKW: 100000
```

4. 数据库结构优化测试（高维最临近算法）
- 目标：得到若干标准，将数据库分类成40个以上的子数据库，每个数据库不需要检索就可以取出所有图片
- 将数据库的规模控制在25000以内，寻找最邻近值的时间在1s以内，1000k数据需要分成40个类别
- 将存入比对数据库的数据进行分类存储，进行最临近检索时，先对数据进行处理找到相应类别，然后找到对应的子数据库
- 设定若干label值的区间进行检索（需要验证：如何选取区间；选定空间后是否始终能保留最临近的那个值；或者统计超出范围的维度数量小于一定值）
  - 前提是数据库规模控制在一定范围之内
  - 数据分布，某一条目的最临近的数据排列的数据分布，计算大量数据可以计算出得到

4.1 测试
4.1.1 k-means分类
>简要分析
- k-means 算法对数据进行分类计算
- 对数据库中的数据进行分类，每个数据库容量在25K,就需要分成40个子数据库（64）
- 64*16k
- 做64个聚类中心

- 初始聚类中心的选取使用 k-means++算法

- 大容量的数据库的聚类采用部分样本优化Mini Batch K-Means
  - 用样本集中的一部分的样本来做传统的K-Means
  - 选择一个合适的批样本大小batch size，无放回的随机采样
  - 多跑几次Mini Batch K-Means算法，用得到不同的随机采样集来得到聚类簇，选择其中最优的聚类簇

  - 逻辑
    1：从数据集中随机抽取一些数据形成小批量，把他们分配给最近的质心
    2：更新质心

- 过程设计
  - 传统k-means算法实现
    - 输入：数据集；预设的聚类中心（采用随机选取）；迭代次数；聚类中心数量
    - 输出：聚类中心结果；聚类效果评价指标
  - k-means++：聚类中心计算方法
    - 输入：数据集；聚类中心数量
    - 输出：聚类中心列表
  - Mini Batch K-Means：基于传统k-means算法，但是只计算部分数据，然后逐渐添加数据直至聚类中心稳定
    - 输入：数据集；预设的聚类中心；迭代次数；聚类中心数量
    - 输出：聚类中心结果；聚类效果评价指标

- 应用：对数据库中的数据进行分类
  - 模块可用性测试
  - 选取一部分数据
    - 先取10000条不同的数据
  - 确定聚类中心数，最大迭代次数
    - 先假设聚类中心为64，最大迭代为1000
    - 修改能够将分类器的数据状态保存到本地，下一次启动时能够接着之前的结果继续分类
  - 执行分类迭代
  - 取出运行结果，最好保存在本地
    - 分类器提供保存到本地的接口
  - 测试分类效果
    - 遍历数据查找到的数据条目是否在类群之中：在类群中的概率
    - 在类群找到的最相似图片与在数据库中找到的最相似图片差异/与图片自身的相似度
    - 实际应用时，会固定分类器的分类标准，样本数量较小时，可能找不到相似程度较高的图片，因此需要确定相似图片的最大distance
    - 实际效果与聚类中心数量与初始值的关联较大
    - 规划分类后的数据库的结构，若分类后搜索速度的提升
  - 优化参数和方法，确定该方法的准确性

### 4.1.2 k-means分类效果测试
- 参数及参数优化
  - 样本容量(达到较准确的分类效果所用最低样本容量，以减少分类标准计算时间)    1k 10k 50k 100k
  - 迭代次数（达到较准确的分类效果所用最低迭代计算次数，以减少分类标准计算时间）    100 500 1000 5000
  - 聚类中心数量（最优的数量） 2 4 8 16 32 64 128
  - 测试样本数量（得到较准确的测试结果的最低测试次数，假设测试足够多随机数据后测试结果趋向一个稳定值）
  - 初始值确定方法（对分类准确性的影响）

- 测试标准：检索到的相似图片的准确性
  - 在同类群中找到的相似图片与在全比对数据库中找到的相似图与原图的相似程度,只要label_distance在一定范围内认为是准确的;或者找到的图片在全剧查找中最相似的图片列表前几个就认为是准确的（宽松）
  - 在全比对数据中找到的图片与原图同类群的概率（严格）

- 测试结果记录

```shell
capacitys:5000 max_iterations:100 num_test:100 k_clusters:64 result:0.81
capacitys:5000 max_iterations:100 num_test:500 k_clusters:64 result:0.794
capacitys:5000 max_iterations:100 num_test:1000 k_clusters:64 result:0.786
capacitys:5000 max_iterations:500 num_test:100 k_clusters:64 result:0.76  2h
capacitys:5000 max_iterations:50 num_test:500 k_clusters:2 result:0.902 2020-09-07 19:33:22
capacitys:5000 max_iterations:50 num_test:500 k_clusters:4 result:0.902 2020-09-08 01:12:03
capacitys:5000 max_iterations:50 num_test:500 k_clusters:8 result:0.874 2020-09-08 06:50:01
capacitys:5000 max_iterations:50 num_test:500 k_clusters:16 result:0.86 2020-09-08 12:28:47
capacitys:5000 max_iterations:50 num_test:500 k_clusters:32 result:0.844 2020-09-08 18:09:15
capacitys:5000 max_iterations:50 num_test:500 k_clusters:64 result:0.794 2020-09-08 23:48:46
capacitys:5000 max_iterations:50 num_test:500 k_clusters:128 result:0.738 2020-09-09 05:28:36
capacitys:5000 max_iterations:50 num_test:500 k_clusters:256 result:0.69 2020-09-09 11:12:24
capacitys:5000 max_iterations:50 num_test:500 k_clusters:512 result:0.646 2020-09-09 17:07:06
capacitys:5000 max_iterations:50 num_test:500 k_clusters:1024 result:0.686 2020-09-09 23:38:37

capacitys:10000 max_iterations:1000 num_test:500 k_clusters:2 result:0.91 2020-09-07 17:14:40
capacitys:10000 max_iterations:1000 num_test:500 k_clusters:4 result:0.9 2020-09-07 22:54:13
capacitys:10000 max_iterations:1000 num_test:500 k_clusters:8 result:0.858 2020-09-08 04:32:14
capacitys:10000 max_iterations:1000 num_test:500 k_clusters:16 result:0.848 2020-09-08 10:11:18
capacitys:10000 max_iterations:1000 num_test:500 k_clusters:32 result:0.86 2020-09-08 15:52:08
capacitys:10000 max_iterations:1000 num_test:500 k_clusters:64 result:0.762 2020-09-08 21:34:27
capacitys:10000 max_iterations:1000 num_test:500 k_clusters:128 result:0.684 2020-09-09 03:17:27
capacitys:10000 max_iterations:1000 num_test:500 k_clusters:256 result:0.65 2020-09-09 09:08:50
capacitys:10000 max_iterations:1000 num_test:500 k_clusters:512 result:0.646 2020-09-09 15:25:04
capacitys:10000 max_iterations:1000 num_test:500 k_clusters:1024 result:0.632 2020-09-09 23:02:39
```


### 4.1.2 k-means分类进阶
- 使用其他算法进行分类，是否有更好的效果
- 使用样本增量法提高分类速度


## 需要mysql库的支持
- 将数据库分成若干子数据，一次性获取速度
- 更加便捷安全的接口
- 异调试

## 需要log模块的支持
- 打印运行信息到本地文件
- 打印运行结果到输出窗口
