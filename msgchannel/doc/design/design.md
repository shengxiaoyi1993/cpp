# msgchannel

## 说明

- 进程间交互的单通信类
- 可供多个producer和customer调用，但之间没有调配，使用的是竞争机制

## 对外接口

- 实例化为特定标识的通道
- producer发送一定长度的消息给消息队列
- customer设置回调函数，传出接收到的数据



## 实现
### 传输的主体是消息队列
- 消息队列的操作

```
Ftok
msgget
msgsnd
msgrcv
```

- 对关键信息的打印log
- 消息队列中消息获取


