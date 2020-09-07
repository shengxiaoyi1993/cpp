# design

## 需求
- 能够适应不同类型的数据求聚类中心
- 支持初始聚类中心随机生成或者个按照kmeans算法生成(尚未支持)
- 支持在原有数据的基础上添加数据，然后进行聚群中心的更新（尚未支持）

## 总体设计
1. 查阅初步确定，图片label数据分类算法为K-means。
2. 采用K-means++算法确定聚类中心的初始值。原理是让聚类中心的初始值分布地足够离散。
3. Mini Batch K-Means解决原数据库过大的问题。逐渐选取少量样本更新聚类中心，直至聚类中心在一定范围内稳定（未完成）

## 数据结构设计

### 基本数据结构
- 由外界输入
- 该类需要提供计算距离的方法
- 因为要使用vector,因此要提供复制函数和拷贝构造函数

### cluster
- 团簇类
- 基本数据结构的堆
- 聚类中心
- 提供计算均值团簇中心
- 和更新团簇中心的方法

### 算法类 kmeans
- 输入：参数和数据
- 输出：聚类结果

## 系统设计&使用方法

- 范例
```cpp
//输入数据点列表
//支持不同的自定义数据结构，但是自定义数据结构需要定义若干运算，见PointEg
vector<alg::PointEg> list;//填充该表

//初始化分类器
alg::KmeansCluster<alg::PointEg> classfier(v_k,9999,list);
//设置迭代时的观察函数，回调函数不能阻塞
classfier.setOutputClustersFunc(printClusters);
//迭代过程
classfier.run();
//获取聚类中心列表
vector<alg::PointEg> list_centrapoint= classfier.getCentraPoints();
//获取聚类列表
classfier.getClusters()


```

- debug
  - 通过开启在cmake 添加`ADD_DEFINITIONS(-D DEBUG_SYSLOGGER)`可以开启分类器的log



## advance
1. 数据是否保存到内部，若是数据过大需要提供将不用的数据保存到本地文件的接口
2. 保存临时状态的接口，执行若干次迭代停止后，仍可以接着上一次的迭代继续运算
