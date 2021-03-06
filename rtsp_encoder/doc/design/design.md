# rtsp解码器(c++)
## 1. 功能
- 截取一段时间内的图片：输入时间，回退时间，返回给定时间段内给定时间间隔的图片
- 截取短视频：输入时间长度，回退时间，截取从回退到的时间点开始的给定时长的视频
- 截单张图片：给定回退时间，输出当前时间点退回时间点的图片
- 保存一定时长的缓存

## 2. 运行
- 类的初始化，给定rtsp，给定时长


## 接口设计
- 构造函数
```
RtspEncoder(string rtsp,unsigned int v_buffer_length)
```

- 析构函数
```
//释放公共变量
~RtspEncoder();
```

- 判断是否激活
```
bool isValid();
```
- 截取一段时间内的图片
- 截取短视频
- 截单张图片

## 对AVPacket的测试
- 定义过程做了什么处理
- 初始化过程做了什么处理
```
av_init_packet 将变量置空
```
- av_free_packet处理
```
释放内存，指针置空
```
- av_copy_packet:获取数据


## faq
- 图片与视频解码是否使用同一个解码器:可以
- 获取帧与缓p存管理
  - 非工作状态：rtsp是持续运行的，初始化一定数量的帧，每获取一帧，覆盖最旧的帧，移动指向第一帧的指针
  - 工作状态：对于缓存的工作状态是相同的，
    - 获取单张图片：在缓存数据中寻找，或者等待特定时间后去寻找某个时间点后能够解码成图片的帧
    - 获取多张图片：设置类的回调函数作为全局变量，函数暂时锁住缓存数据，提取缓存中的数据，使用回调函数进行输出，函数退出时，将回调函数至空
    - 获取短视频，同样将文件名作为全局变量，先将缓存数据存入，只要获取帧的线程在获取到图片时将帧同时存入文件中即可。截取视频流的函数结束后将视频名为空。

- 是否要支持多线程的输出，即允许同时设置多个输出流，多个回调函数
- 解码成图片的函数只执行一次，随后使用多个回调函数返回

- 是否一定需要是解码关键帧，这需要测试解码关键帧与非关键帧所花费的时间与资源消耗

- 对于缓存中的帧，是否保存关键帧还是都保存，如果要保存实时的视频，则需要普通帧也进行缓存

- 对于录制视频的函数是否与录制视频同时录制。
  由于视频与图片抓取在不同时间录制会出现两者不同步的问题，应该设置同时录制的接口，同时设置图片与视频独立录制的过程。
- 若该类不能提供多线程同时录制图片或视频的功能，当某一功能在执行时，应对其他功能设置为禁用
