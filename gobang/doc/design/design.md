# design

## 五子棋AI对奕程序
- 测试环境：QQ游戏的五子棋游戏 windows
- 功能：
  - 简单操作游戏界面上的按钮，流程控制；对时间计数的识别
  - 对游戏界面和状态的识别
  - 截取图片，对图片上的落子进行识别，保存棋子位置的，记录每一步的落子
  - 对五子棋落子可能性进行计算，计算出获胜概率最高的算法
    - 穷举法
    - 一定策略的下法
    - 对一定数量的棋局的统计，统计出最佳走法
  - 测试是否存在必胜走法

- 涉及技术
  - 键鼠控制：https://blog.csdn.net/m0_37537177/article/details/78197220 ok
  - opencv图片的简单匹配识别
  - windows下的截图   ok
    ```
    https://blog.csdn.net/shenzhuan7/article/details/43052233?utm_medium=distribute.pc_relevant.none-task-blog-BlogCommendFromMachineLearnPai2-3.channel_param&depth_1-utm_source=distribute.pc_relevant.none-task-blog-BlogCommendFromMachineLearnPai2-3.channel_param
    https://blog.csdn.net/qq_18984151/article/details/79231953?utm_medium=distribute.pc_relevant.none-task-blog-BlogCommendFromMachineLearnPai2-1.channel_param&depth_1-utm_source=distribute.pc_relevant.none-task-blog-BlogCommendFromMachineLearnPai2-1.channel_param
    ```
  - 棋子位置的保存
  - 算法

## 使用流程
- 开启游戏界面
- 打开程序
- 识别游戏界面的窗口；调整至标准大小
- 我方确认开始
- 轮询游戏是否开始
- 判断哪方先手
  - 我方先手，落子
  - 对面先手
- 监控落子状态|读秒，计算时间剩余
- 读取棋子位置，计算最近落子状态

##  模块确定
- 键盘鼠标控制程序/鼠标光标、手型确识别
- 截面控制按钮确定/截面确定/计数时间确定/
- 桌面截图模块/扣图模块
- 棋子位置确定，棋子位置相关算法
