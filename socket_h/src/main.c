#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

/// socket
/// 应用 TCP UDP ICMP IP 与用户层的交互
///
/// -socket函数支持的套接字类型包括SOCK_STREAM（数据流）、SOCK_DGRAM（数据报）、SOCK_SEQPACKET（顺序数据报）、SOCK_RAW（原始套接字）、SOCK_RDM（可靠传递消息）、SOCK_PACKET（数据包）
//AF_UNIX, AF_LOCAL	本地交互协议
//AF_INET	IPv4协议
//AF_INET6	IPv6协议
//AF_NETLINK	内核接口设备协议
//AF_IPX	IPX-Novell协议
//AF_X25	ITU-T X.25/ISO-8208协议
//AF_AX25

//业余无线电AX.25协议
//AF_ATMPVC	原始ATM接入协议
//AF_APPLETALK	苹果公司的Appletalk协议
//AF_PACKET	底层数据包接口

///在Linux系统中创建一个套接字时会在内核中创建一个套接字数据结构，然后返回一个套接字描述符标识这个套接字数据结构。
/// 这个套接字数据结构包含连接的各种信息，如目的地址、TCP状态以及发送接收缓冲区等。
/// TCP协议这个套接字数据机构的内容来控制这条连接。

/// socketpair
/// socketpair()函数用于创建一对无名的、相互连接的套接子。
/// 如果函数成功，则返回0，创建好的套接字分别是sv[0]和sv[1]；否则返回-1，错误码保存于errno中
/// 基本用法：
/// 1. 这对套接字可以用于全双工通信，每一个套接字既可以读也可以写。例如，可以往sv[0]中写，
/// 从sv[1]中读；或者从sv[1]中写，从sv[0]中读；
/// 2. 如果往一个套接字(如sv[0])中写入后，再从该套接字读时会阻塞，只能在另一个套接字中(sv[1])
/// 上读成功；
/// 3. 读、写操作可以位于同一个进程，也可以分别位于不同的进程，如父子进程。如果是父子进程时，
/// 一般会功能分离，一个进程用来读，一个用来写。因为文件描述副sv[0]和sv[1]是进程共享的，
/// 所以读的进程要关闭写描述符, 反之，写的进程关闭读描述符。

/// bind
/// 正如上面所说bind()函数把一个地址族中的特定地址赋给socket。例如对应AF_INET、AF_INET6
/// 就是把一个ipv4或ipv6地址和端口号组合赋给socket

//addr：一个const struct sockaddr *指针，指向要绑定给sockfd的协议地址。
//这个地址结构根据地址创建socket时的地址协议族的不同而不同，如ipv4对应的是：
//struct sockaddr_in {
//    sa_family_t    sin_family; /* address family: AF_INET */
//    in_port_t      sin_port;   /* port in network byte order */
//    struct in_addr sin_addr;   /* internet address */
//};
///* Internet address. */
//struct in_addr {
//    uint32_t       s_addr;     /* address in network byte order */
//};

//ipv6对应的是：

//struct sockaddr_in6 {
//    sa_family_t     sin6_family;   /* AF_INET6 */
//    in_port_t       sin6_port;     /* port number */
//    uint32_t        sin6_flowinfo; /* IPv6 flow information */
//    struct in6_addr sin6_addr;     /* IPv6 address */
//    uint32_t        sin6_scope_id; /* Scope ID (new in 2.4) */
//};
//struct in6_addr {
//    unsigned char   s6_addr[16];   /* IPv6 address */
//};


/// getsockname
/// 获取监听的地址和端口
///
/// connect
/// connect函数的第一个参数即为客户端的socket描述字，第二参数为服务器的socket地址，
/// 第三个参数为socket地址的长度。客户端通过调用connect函数来建立与TCP服务器的连接。
///
///
/// getpeername
/// 获取connfd表示的连接上的对端地址
///
/// send
/// 不论是客户还是服务器应用程序都用send函数来向TCP连接的另一端发送数据
///
/// recv
/// 用recv函数从TCP连接的另一端接收数据。
///
/// sendto
///
/// recvfrom
///
///  一般情况下，send、recv在TCP协议下使用，sendto、recvfrom在UDP协议下使用，也可以在TCP协议下使用，不过用的很少
///
/// sendmsg
/// recvmsg
/// msg_name 和 msg_namelen 这两个成员用于套接字未连接的场合
/// recvmsg和sendmsg是最通用的I/O函数，只要设置好参数，read、readv、recv、recvfrom
/// 和write、writev、send、sendto等函数都可以对应换成这两个函数来调用
///
/// getsockopt
/// setsockopt
/// listen
/// 调用listen()来监听这个socket，如果客户端这时调用connect()发出连接请求，服务器端就会接收到这个请求
///
/// accept
/// accept函数的第一个参数为服务器的socket描述字，第二个参数为指向struct sockaddr *的指针，
/// 用于返回客户端的协议地址，第三个参数为协议地址的长度。如果accpet成功，那么其返回值是由内核
/// 自动生成的一个全新的描述字，代表与返回客户的TCP连接
///
/// shutdown
/// sockatmark
/// isfdtype


#define MAXLINE 4096
#define PORT 6563
#define LISTENQ 1024
#include<stdio.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<unistd.h>
#include<string.h>
#include<arpa/inet.h>

int case_srv() ;

int main(int argc, char *argv[])
{

// int sktfd= socket(0,0,0);

// struct sockaddr *addr;
//// bind(sktfd,,);



// close(sktfd);

  case_srv();

  return 0;
}




int case_srv() {
    int listenfd, connfd;
    struct sockaddr_in servaddr;//服务器绑定的地址
    struct sockaddr_in listendAddr, connectedAddr, peerAddr;//分别表示监听的地址，连接的本地地址，连接的对端地址
    int listendAddrLen, connectedAddrLen, peerLen;
    char ipAddr[INET_ADDRSTRLEN];//保存点分十进制的地址
    listenfd = socket(AF_INET, SOCK_STREAM, 0);
    memset(&servaddr, 0, sizeof(servaddr));

    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(PORT);

    bind(listenfd, (struct sockaddr*)&servaddr, sizeof(servaddr));//服务器端绑定地址

    listen(listenfd, LISTENQ);
    listendAddrLen = sizeof(listendAddr);
    getsockname(listenfd, (struct sockaddr *)&listendAddr, &listendAddrLen);//获取监听的地址和端口
    printf("listen address = %s:%d\n", inet_ntoa(listendAddr.sin_addr), ntohs(listendAddr.sin_port));

    fflush(stdout);

    while(1) {
        connfd = accept(listenfd, (struct sockaddr *)NULL, NULL);
        connectedAddrLen = sizeof(connectedAddr);
        getsockname(connfd, (struct sockaddr *)&connectedAddr, &connectedAddrLen);//获取connfd表示的连接上的本地地址
        printf("connected server address = %s:%d\n", inet_ntoa(connectedAddr.sin_addr), ntohs(connectedAddr.sin_port));
        getpeername(connfd, (struct sockaddr *)&peerAddr, &peerLen); //获取connfd表示的连接上的对端地址
        printf("connected peer address = %s:%d\n", inet_ntop(AF_INET, &peerAddr.sin_addr, ipAddr, sizeof(ipAddr)), ntohs(peerAddr.sin_port));
        fflush(stdout);
    }
    return 0;
}
