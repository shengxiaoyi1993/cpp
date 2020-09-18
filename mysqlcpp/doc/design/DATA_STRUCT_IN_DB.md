# example

## 1 需求
- 设计数据库保存uvss系统的数据，并对各项功能进行测试
- 数据库接入现有系统的可操作性 （虽然可以接入，但是用mysql替换mongodb数据结构上有较大差异，不建议）
- 根据数据库配置表能够将数据库创建并部署
- 数据库数据拷贝时的处理

## 2 过程设计
- 列举原数据结构
- 并对数据关系分析
- 整理出表的结构，表和表的属性
- 理论验证各项查询功能
- 实现各项表的创建，删除和查询等功能


## 3 数据结构

### 3.1 in mongo


```
{
        "_id" : ObjectId("5edd99f8a2190000930029f7"),
        "SN" : "JkHuQqCuUktOMKyc",
        "big_ok" : true,
        "deny" : 0,
        "device_ID" : "5edd95f6a2190000930029dd",
        "device_name" : "1",
        "dir" : "/20/06/08/09.52.56_26_192.168.1.168/",
        "driver_name" : "",
        "face_blacklist" : false,
        "face_label" : [ ],
        "face_ok" : false,
        "face_snap_ok" : false,
        "face_whitelist" : false,
        "file_prex" : "20.06.08.09.52.56_26",
        "fod_auth_code" : "",
        "group_id" : 0,
        "image_id" : 21,
        "in_cf_db" : false,
        "note" : "",
        "plate_blacklist" : false,
        "plate_direction" : 0,
        "plate_finish" : true,
        "plate_number" : "",
        "plate_ok" : false,
        "plate_snap_ok" : false,
        "plate_whitelist" : false,
        "score" : 0,
        "small_label" : [ ],
        "small_ok" : true,
        "small_time" : 1591581176,
        "time" : 1591581176,
        "top_dir" : "C:/Program Files (x86)/UVSScure Server/uvss_test_data",
        "users" : [
                "test"
        ],
        "videos" : [ ]
}
```
- devicegroup

```
{
        "_id" : ObjectId("5edd95f6a2190000930029dd"),
        "FOD_code" : "",
        "FOD_level" : 0,
        "FOD_status" : false,
        "FOD_switch" : false,
        "descrption" : "",
        "face_blacklist_code" : "",
        "face_blacklist_level" : 0,
        "face_blacklist_status" : false,
        "face_blacklist_switch" : false,
        "face_camera" : {
                "IP" : "",
                "big_video_uri" : "",
                "camera_name_type" : 0,
                "camera_type" : 0,
                "connection_status" : 0,
                "import_video" : false,
                "min_score" : 99,
                "name" : "Face camera",
                "password" : "",
                "small_video_uri" : "",
                "timeout" : 0,
                "username" : ""
        },
        "name" : "1",
        "plate_camera_list" : [ ],
        "scan_type" : 0,
        "uvss_camera" : {
                "IP" : "192.168.1.168",
                "SN" : "JkHuQqCuUktOMKyc",
                "connection_status" : 2,
                "last_time" : 102400,
                "password" : "admin",
                "region" : "China",
                "timeout" : 30,
                "type" : 1,
                "username" : "root"
        },
        "video_camera_list" : [ ]
}
```

- userlist

```
{
        "_id" : ObjectId("5edd936fa2190000930029d2"),
        "device_list" : [
                "5edd95aca2190000930029d8",
                "5edd95f6a2190000930029dd"
        ],
        "is_login" : false,
        "password" : "8d969eef6ecad3c29a3a629280e686cf0c3f5d5a86aff3ca12020c923adc6c92",
        "username" : "admin",
        "valid" : true
}
```

### 3.2 in mysql

- 转换原则
  - 将变长数组转换成恒长数组
  - 将每个数组中的对象独立出来固定为表中的一个属性
- 设计前提
  - 假设mysql安全性可以保证的，数据库不对用户开放


####  3.2.1 表
```cpp
- 数据条目（包含状态信息和其他表的的元组的键）（T_DATAITEM）
- 各个设备列表
  - 通用相机(T_COMMON_CAMERA):人脸(FACE),环周(SURROUNDING),车牌(PLATE)
  - uvss设备(T_UVSS_CAMERA)
- 用户列表(T_USER)
- 设备组列表 (T_DEVICE_GROUP)
- 数组库信息(T_DATABASE_CONFIG)
- 人脸黑名单(T_FACE_BLACK_LIST)
- 人脸白名单（T_FACE_WRITE_LIST）
- 车辆黑名单(T_PLATE_BLACK_LIST)
- 车辆白名单(T_PLATE_WRITE_LIST)
- 数据字典(T_DATA_DICTIONARY)   //用于保存数据库中出现的枚举类型定义
```

####  3.2.1 表属性

- T_DATAITEM


```
{
  //包含的实体
  DATA_ID                    //唯一主键
  DEVICE_GROUP_ID           
  DEVICE_SN_CODE

  //上图状态码
  BIG_IMAGE_OK
  SMALL_IMAGE_OK
  FACE_IMAGE_L_OK         
  FACE_SNAP_IMAGE_L_OK
  PLATE_IMAGE_L_OK
  PLATE_SNAP_IMAGE_L_OK
  FACE_IMAGE_R_OK             
  FACE_SNAP_IMAGE_R_OK
  PLATE_IMAGE_R_OK
  PLATE_SNAP_IMAGE_R_OK
  SURROUNDING_HR_VIDEO_OK[4]  //环周相机高分辨率视频          
  SURROUNDING_LR_VIDEO_OK[4]  //环周相机低分辨率视频         
  SURROUNDING_HR_IMAGE_OK[4]  //环周相机高分辨率视频
  SURROUNDING_LR_IMAGE_OK[4]  //环周相机低分辨率视频  
  DATA_FINISH                 //该条目录制一旦完成，就不再有变更

  //高级信息状态码
  IN_FACE_BLACK_LIST
  IN_FACE_WRITE_LIST
  DRIVER_NAME                 //根据人脸与黑白名单中的比对结果确定司机姓名
  IN_PLATE_BLACK_LIST
  IN_PLATE_WRITE_LIST



  //包含的数据
  STOREAGE_DIR           //数据保存路径
  FACE_LABEL[128]        //人脸label，用于判定人脸相似程度
  PLATE_DIRECTION        //标记车辆行驶的方向与车牌相机相关联,给定三种状态：OUT，IN，BIDIRECTION，在数据字典中记录
  PLATE_LICENSE          //识别出的车牌
  FACE_SCORE             //人脸评分
  SMALL_IMAGE_LABEL[128] //小图label
  CAPTURE_TIME           //开始录制的时间
  USERS[10]              //值班人员列表


  //用户设置
  CHECK_STATUS           //共有三种状态：PASS DENY UNCHECK
  IN_COMPARE_DB          //是或否
  NOTE                   //用户填写的注释

}
```

```
//数据库中不直接保存文件名，但是具有与文件一一对应的标记，该标记对应文件是否存在
//文件与标记名以某种格式相互对应
//每条数据包含的文件
大图
小图
人脸图 人脸扣图      
车牌图片 车牌扣图
录制的高分辨率环周视频
录制的低分辨率环周视频
录制的高分辨率环周图片
录制的低分辨率环周图片

```

- T_COMMON_CAMERA

```
{
  DEVICE_CODE  //主码
  USERNAME
  PASSWORD
  IP
  PORT//确定一下需要用到哪些port
  HR_RTSP                //高分辨率rtsp流
  LR_RTSP                //低分辨率rtsp流
  STATUS                 //连接状态
  MANUFACTOR             //厂家
  VERSION                //版本号
  TYPE                   //三种类型：人脸(FACE),环周(SURROUNDING),车牌(PLATE) 添加到数字字典
  ACCESS_METHOD          //三种接入方式：SDK API ONVIF
}
```

- T_UVSS_CAMERA

```
{
  DEVICE_SN_CODE         //SN码
  USERNAME
  PASSWORD
  IP
  PORT                  //端口号
  SERVER_IP             //与设备连接的主机
  VERSION
  COMPANY
  REMAIN_TIMES          剩余可用次数
  TYPE                  //待确定，添加到数据字典
  REGION                //国家和区域
  LANGUAGE              //语言版本

  IS_ACTIVATE           //是否被激活
  FUN_BLACK_WHITE_LIST //记录黑白名单激活状态
  FUN_FOD_DETECT       //记录FOD激活状态

  STATUS                //实时连接状态

}
```



- T_USER

```
{
  USERNAME                  //主码，唯一；
  PASSWORD
  TYPE                      //共两种类型:ADMIN ORIDINARY,保存至数据字典
  STATUS_LIVE               //该用户的生命周期，是否被删除：若需要删除原有用户，就将用户状态设置为不可用状态；这是为了搜索数据时有对应的条目
  #BEGIN//创建时间
  #END //终止时间，被置为不可用时间；若处于可用状态，则该数据无效
  STATUS_LOG                //用户的登陆状态：同一时间，只能有一个用户登陆
  IP_LOG                    //用户以客户端方式登陆，当前登陆的IP，若用户未登陆，则该位置无效
  LIST_DEVICE_GROUP[]       //具有权限的设备组列表，当某一设备组设置为不可用时，应该循环遍历更新该状态
}
```



- T_DEVICE_GROUP

```
{

  DEVICE_GROUP_ID        //唯一主键，系统自动生成
  DEVICE_GROUP_NAME      //设备组名，用户可能使用该条件进行数据库检索，为区别需要设置成不同

  //组成部分
  DEVICE_SN_CODE        //对应到UVSS设备栏的某一条目
  FACE_CAMERA[2]         //对应到通用相机栏的某一条目
  SURROUNDING_CAMERA[4]  //对应到通用相机栏的某一条目
  PLATE_CAMERA[2]        //对应到通用相机栏的某一条目

  //状态
   STATUS               //是否处于可用状态，是否被删除
}
```


- T_DATABASE_CONFIG

```
{
  TOP_DIR //数据条目的文件保存路径
}
```

- T_FACE_BLACK_LIST

```
{
  NAME
  LABELS[]
}
```

- T_FACE_WRITE_LIST

```
{
  NAME
  LABELS[]
}
```

- T_PLATE_BLACK_LIST

```
{
  PLATE_LICENSE[]
}
```

- T_PLATE_WRITE_LIST

```
{
  PLATE_LICENSE[]
}
```


- T_DATA_DICTIONARY

```
//属性
{
  ID         //自动生成的ID，另外的表使用的是ID，然后根据ID查找到枚举类型
  ENUM_TYPE  //实际指向的枚举类型
}

//ENUM_TYPE列举
{
  PLATE_DIRECTION_IN
  PLATE_DIRECTION_OUT
  PLATE_DIRECTION_BIDIRECTION

  COMMON_CAMERA_TYPE_FACE
  COMMON_CAMERA_TYPE_SURROUNDING
  COMMON_CAMERA_TYPE_PLATE

  COMMON_CAMERA_ACCESS_METHOD_SDK
  COMMON_CAMERA_ACCESS_METHOD_API
  COMMON_CAMERA_ACCESS_METHOD_ONVIF

  USER_TYPE_ADMIN
  USER_TYPE_ORIDINARY

}
```

```
- 命名规则：https://blog.csdn.net/zwhfyy/article/details/82462533
- 数据字典的两种形式。当某种属性的值为固定数量的枚举类型时，可以采用数字字典方式进行处理。即主表中保存另一表上存储的代码，同过连接就可查询到原来的值。但是仅仅是这样，可能回产生较多的表，此时可以将多张表合并成一张。这样做的前提是值的数据类型是相同的。

```



## 讨论条目


- 设备组与UVSS的关系：有限制的n:1关系
  - 1:1
  - 1:n：同一设备组允许更新不同UVSS设备；将一套设备组置为不可用时，清空该设备组设置的UVSS设备和其他通用相机，只保留ID和设备组名，可以避免同一UVSS设备配置到不同设备组的情况
  - n:1
  - n:m

-  设备的激活状态与数据高级功能的执行：高级功能与UVSS设备绑定而非与设备组绑定
  - 某一UVSS设备的状态
    - 连接状态
    - 激活状态
    - 高级功能激活状态 （高级激活功能要在设备已被激活的基础上）

  - 激活状态的生命周期:
    - 终身制，不保存激活码 （暂定）
    - 定时检查制

  - 数据是否进行高级功能操作取决于录制数据的设备的激活状态
    - 取决于***查看时***设备的高级功能激活状态,不管设备是否连接；设备一旦配置为激活，该状态一直保留。


- 已被激活的设备查找相似图片计算FOD时，若找到的图片恰好是未被激活FOD的设备录制的图片，两者是否能计算FOD：
  - 能


- 对于与数据条目搜索相关的表项，如设备组ID、UVSS设备、用户名，当表中的条目删除后，条目会变更为不可用状态，而非完全删除。插入新的条目，若条目与之前的条目相同，则会恢复可用状态。（该规定是处于用户搜索的考虑，若以某个条件搜索的结果包含某条数据，只要该数据不删除，无论做了什么配置，就一直能搜索到该数据；该处要对用户进行提醒）

- 对于通用相机设否需要唯一标识：没有的话多态设备组中同时使用同一台通用相机，通用相机栏会有重复条目；若需要设置，则需要确定唯一标识的手段。（暂定不做唯一标识）

- 对于DATA_ID和暂定为自增的自然数，可以提高检索效率


- 插入人脸黑白名单可能造成数据不一致性
