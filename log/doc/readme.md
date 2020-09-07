# readme

## 需求
- 满足多线程使用
- 多个对象同时使用
- 宏使用 可由cmake控制调试


## 使用方法
- 宏调用

```cpp
LOG_INFO_NOLOCK("INFO:%s","log...");

```

- 类调用

```cpp
SysLogger logger;
logger.InitLogger("log.txt",0);
logger.WriteLog(0,"log.txt",1,0,"txt:%s","hello");

```
