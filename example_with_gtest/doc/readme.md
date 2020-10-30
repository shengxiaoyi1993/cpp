# readme
>更具体地说明和范例见gtest源码目录
>已测试部分在以后的测试过程中进行记录和积累



## 提供数值，字符串类型的比较
- ASSERT_系列：

```
bool值检查

1、 ASSERT_TRUE(参数)，期待结果是true

2、ASSERT_FALSE(参数)，期待结果是false

数值型数据检查

3、ASSERT_EQ(参数1，参数2)，传入的是需要比较的两个数 equal

4、ASSERT_NE(参数1，参数2)，not equal，不等于才返回true

5、ASSERT_LT(参数1，参数2)，less than，小于才返回true

6、ASSERT_GT(参数1，参数2)，greater than，大于才返回true

7、ASSERT_LE(参数1，参数2)，less equal，小于等于才返回true

8、ASSERT_GE(参数1，参数2)，greater equal，大于等于才返回true

字符串检查

9、ASSERT_STREQ(expected_str, actual_str)，两个C风格的字符串相等才正确返回

10、ASSERT_STRNE(str1, str2)，两个C风格的字符串不相等时才正确返回

11、ASSERT_STRCASEEQ(expected_str, actual_str)

12、ASSERT_STRCASENE(str1, str2)
```

- EXPECT_系列：
```
与以上类似的宏
```

## 提供事件机制
- 使能设置各个实例的初始化条件
  - TestSuite：能否为某一类的事件，在第一个事件开始执行SetUpTestCase，结束时执行TearDownTestCase。继承自testing::Test
  - TestCase：能否为某一类的事件，在每个事件开始执行SetUp，结束时执行TearDown。继承自testing::Test
  - 全局事件：能够在所有事件开始时执行SetUp，TearDown方法在所有案例执行后执行。 继承自testing::Environment
- faq：TEST()与TEST_F()的区别

## 死亡测试（需要测试）
- 检查程序是否按照预期的方式奔溃
- 分类
  - ASSERT_DEATH
  - ASSERT_EXIT

## 对于复杂情况的测试
- 提供了提供了模板化的方式让用户完成自定义表达式与提示信息。
- 分类
  - Using an existing boolen function
  >函数本身返回bool类型的值，利用()_PRED_()的系列的断言进行

  - Using a function that returns an assertingresult
  >通过对函数的分支进行处理而使其变成可断言的表达式

  - Using predicate-formatter
  >由于代码到达一定规模后，无法判断是元代码还是测试代码；gtest提供了()_PRED_FORMAT()_()的宏，最多接收五个参数

  - 访问类的私有成员
  - 首先考虑该私有成员是否能通过代码的调整来避免直接访问
  - 特殊情况下可以通过FRIST_TEST来破坏类的封闭性（本质上通过友元实现）
    - TEST（）直接调用
    - TEST_F()需要创键TestFixture的类

- value-parameter Test
  - 向某个方法传入不同不同的参数进行验证，每次调用只需要修改传入内容
  - 创建TestFixture,继承自test::Test和test::WithParamInterface<T>,或者只继承testing::TestWithParam<T>

- type test
  - 当一个函数有多个版本的实现，接收不同类型的参数，若采用value-parameter Test的方法，需要创建多个类，为减少重复代码，可以将代码模板化


- Type-Parameterizes Tests
- 全局共享资源
  - 继承自testing::Environment然后在main()方法中进行加载

- 创建监听器
  - gtest提供了各种事件的回调,继承自testing::EmptyTestEventListener

- 单元测试的启动

## references
- 解释地比较深入
```html
https://www.jianshu.com/p/8e858e64d359?utm_campaign=hugo
```
