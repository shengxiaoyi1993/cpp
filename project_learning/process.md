# process

## 概念

- 第一，进程是一个实体。每一个进程都有它自己的地址空间，一般情况下，包括文本区域（text region）、数据区域（data region）和堆栈（stack region）。文本区域存储处理器执行的代码；数据区域存储变量和进程执行期间使用的动态分配的内存；堆栈区域存储着活动过程调用的指令和本地变量
- 程序是一个没有生命的实体，只有处理器赋予程序生命时（操作系统执行之），它才能成为一个活动的实体，我们称其为进程。

## 意义

- 从理论角度看，是对正在运行的程序过程的抽象；
- 从实现角度看，是一种数据结构，目的在于清晰地刻画动态系统的内在规律，有效管理和调度进入计算机系统主存储器运行的程序。

## 特点

- 动态性：进程的实质是程序在多道程序系统中的一次执行过程，进程是动态产生，动态消亡的。
- 并发性：任何进程都可以同其他进程一起并发执行
- 独立性：进程是一个能独立运行的基本单位，同时也是系统分配资源和调度的独立单位；
- 异步性：由于进程间的相互制约，使进程具有执行的间断性，即进程按各自独立的、不可预知的速度向前推进
- 结构特征：进程由程序、数据和进程控制块三部分组成。
- 多个不同的进程可以包含相同的程序：一个程序在不同的数据集里就构成不同的进程，能得到不同的结果；但是执行过程中，程序不能发生改变。

## 内容

- 那个程序的可运行机器码的一个在存储器的映像。 分配到的存储器（通常包括虚拟内存的一个区域）。存储器的内容包括可运行代码、特定于进程的数据（输入、输出）、调用堆栈、堆栈（用于保存运行时运数中途产生的数据）。 分配给该进程的资源的操作系统描述符，诸如文件描述符（Unix术语）或文件句柄（Windows）、数据源和数据终端。 安全特性，诸如进程拥有者和进程的权限集（可以容许的操作）。 处理器状态（内文），诸如寄存器内容、物理存储器寻址等。当进程正在运行时，状态通常储存在寄存器，其他情况在存储器。

## 切换

- 处理器处理的进程的切换，未运行时进程的上下文（中间数据）保存在四由堆栈中；运行时恢复到处理器堆栈

## status

- Running：占用处理器资源；处于此状态的进程数小于等于处理器的数量
- Blocked:某条件未满足时，无法操作，如IO操作/进程同步
- Ready：进程已获得除处理器以外的所有资源。高优先队列，低优先队列

## 进程与程序

- 程序是指令和数据的有序集合，其本身没有任何运行的含义，是一个静态的概念。而进程是程序在处理机上的一次执行过程，它是一个动态的概念。
- 程序可以作为一种软件资料长期存在，而进程是有一定生命期的。程序是永久的，进程是暂时的。
- 进程更能真实地描述并发，而程序不能；
- 进程是由进程控制块、程序段、数据段三部分组成;
- 进程具有创建其他进程的功能，而程序没有。
- 同一程序同时运行于若干个数据集合上，它将属于若干个不同的进程，也就是说同一程序可以对应多个进程。
- 在传统的操作系统中，程序并不能独立运行，作为资源分配和独立运行的基本单元都是进程

## 线程与进程

- 通常在一个进程中可以包含若干个线程，它们可以利用进程所拥有的资源
- 在引入线程的操作系统中，通常都是把进程作为分配资源的基本单位
- 而把线程作为独立运行和独立调度的基本单位，由于线程比进程更小，基本上不拥有系统资源，故对它的调度所付出的开销就会小得多，能更高效的提高系统内多个程序间并发执行的程度。

## 进程控制

### 进程创建

#### 创建分类

- 用户登录：用户在终端键入登录命令后，如果是合法用户，系统将为该终端建立一个进程，并把它插入到就绪队列中
- 作业调度：批处理系统,批处理任务
- 提供服务：应用程序请求某种服务，如打印服务
- 应用请求:基于应用进程的需求，由它创建一个新的进程，以便使新进程以并发的运行方式完成特定任务。

#### 进程的创建过程
一旦操作系统发现了要求创建新进程的事件后，便调用进程创建原语create()按下述步骤创建一个新进程。
1） 申请空白PCB（Process Control Block）。为新进程申请获得唯一的数字标识符，并从PCB集合中索取一个空白PCB。
2） 为新进程分配资源。为新进程的程序和数据以及用户栈分配必要的内存空间。显然，此时操作系统必须知道新进程所需要的内存大小。
3） 初始化进程控制块。PCB的初始化包括：
①初始化标识信息，将系统分配的标识符和父进程标识符，填入新的PCB中。
②初始化处理机状态信息，使程序计数器指向程序的入口地址，使栈指针指向栈顶。
③初始化处理机控制信息，将进程的状态设置为就绪状态或静止就绪状态，对于优先级，通常是将它设置为最低优先级，除非用户以显式的方式提出高优先级要求。
4） 将新进程插入就绪队列，如果进程就绪队列能够接纳新进程，便将新进程插入到就绪队列中。

### 进程终止
#### 引起进程终止的事件
1）正常结束
在任何计算机系统中，都应该有一个表示进程已经运行完成的指示。例如，在批处理系统中，通常在程序的最后安排一条Hold指令或终止的系统调用。当程序运行到Hold指令时，将产生一个中断，去通知OS本进程已经完成。
2）异常结束
在进程运行期间，由于出现某些错误和故障而迫使进程终止。这类异常事件很多，常见的有：越界错误，保护错，非法指令，特权指令错，运行超时，等待超时，算术运算错，I/O故障。
3）外界干预
外界干预并非指在本进程运行中出现了异常事件，而是指进程应外界的请求而终止运行。这些干预有：操作员或操作系统干预，父进程请求，父进程终止。

#### 进程的终止过程
如果系统发生了上述要求终止进程的某事件后，OS便调用进程终止原语，按下述过程去终止指定的进程。
1）根据被终止进程的标识符，从PCB集合中检索出该进程的PCB，从中读出该进程状态。
2）若被终止进程正处于执行状态，应立即终止该进程的执行，并置调度标志为真。用于指示该进程被终止后应重新进行调度。
3）若该进程还有子孙进程，还应将其所有子孙进程予以终止，以防他们成为不可控的进程。
4）将被终止的进程所拥有的全部资源，或者归还给其父进程，或者归还给系统。
5）将被终止进程（它的PCB）从所在队列（或链表）中移出，等待其它程序来搜集信息。

### 阻塞唤醒
#### 1.引起进程阻塞和唤醒的事件
1）请求系统服务
当正在执行的进程请求操作系统提供服务时，由于某种原因，操作系统并不立即满足该进程的要求时，该进程只能转变为阻塞状态来等待，一旦要求得到满足后，进程被唤醒。
2）启动某种操作
当进程启动某种操作后，如果该进程必须在该操作完成之后才能继续执行，则必须先使该进程阻塞，以等待该操作完成，该操作完成后，将该进程唤醒。
3）新数据尚未到达
对于相互合作的进程，如果其中一个进程需要先获得另一（合作）进程提供的数据才能运行以对数据进行处理，则是要其所需数据尚未到达，该进程只有（等待）阻塞，等到数据到达后，该进程被唤醒。
4）无新工作可做
系统往往设置一些具有某特定功能的系统进程，每当这种进程完成任务后，便把自己阻塞起来以等待新任务到来，新任务到达后，该进程被唤醒。
#### 2.进程阻塞过程
正在执行的进程，当发现上述某事件后，由于无法继续执行，于是进程便通过调用阻塞原语block()把自己阻塞。可见，进程的阻塞是进程自身的一种主动行为。进入block过程后，由于此时该进程还处于执行状态，所以应先立即停止执行，把进程控制块中的现行状态由执行改为阻塞，并将PCB插入阻塞队列。如果系统中设置了因不同事件而阻塞的多个阻塞队列，则应将本进程插入到具有相同事件的阻塞（等待）队列。最后，转调度程序进行重新调度，将处理机分配给另一就绪进程，并进行切换，亦即，保留被阻塞进程的处理机状态（在PCB中），再按新进程的PCB中的处理机状态设置CPU环境。

#### 3. 进程唤醒过程
当被阻塞的进程所期待的事件出现时，如I/O完成或者其所期待的数据已经到达，则由有关进程（比如，用完并释放了该I/O设备的进程）调用唤醒原语wakeup()，将等待该事件的进程唤醒。唤醒原语执行的过程是：首先把被阻塞的进程从等待该事件的阻塞队列中移出，将其PCB中的现行状态由阻塞改为就绪，然后再将该PCB插入到就绪队列中。

## 调度算法
进程的调度算法包括：
实时系统中：FIFO(First Input First Output，先进先出算法)，SJF(Shortest Job First，最短作业优先算法)，SRTF(Shortest Remaining Time First，最短剩余时间优先算法）。
交互式系统中：RR(Round Robin，时间片轮转算法)，HPF(Highest Priority First，最高优先级算法)，多级队列，最短进程优先，保证调度，彩票调度，公平分享调度。
## 阶段
进程是由进程控制块、程序段、数据段三部分组成。一个进程可以包含若干线程(Thread)，线程可以帮助应用程序同时做几件事(比如一个线程向磁盘写入文件，另一个则接收用户的按键操作并及时做出反应，互相不干扰)，在程序被运行后，系统首先要做的就是为该程序进程建立一个默认线程，然后程序可以根据需要自行添加或删除相关的线程。是可并发执行的程序。在一个数据集合上的运行过程，是系统进行资源分配和调度的一个独立单位，也是称活动、路径或任务，它有两方面性质：活动性、并发性。进程可以划分为运行、阻塞、就绪三种状态，并随一定条件而相互转化：就绪--运行，运行--阻塞，阻塞--就绪。
进程为应用程序的运行实例，是应用程序的一次动态执行。看似高深，我们可以简单地理解为：它是操作系统当前运行的执行程序。在系统当前运行的执行程序里包括：系统管理计算机个体和完成各种操作所必需的程序；用户开启、执行的额外程序，当然也包括用户不知道，而自动运行的非法程序（它们就有可能是病毒程序）。

