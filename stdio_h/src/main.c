#include<stdio.h>
#include <stdarg.h>
/// [FILE] 同struct _IO_FILE
///  - 使用fchmod()可以修改某一文件的权限
/// [off_t]
///  - long
/// [ssize_t]
///  - long
/// [fpos_t]
///
/// stdin/stdout/stderr
///  - 实际类型是FILE
/// [remove()]
///  - 删除文件
///  - return 0:正常
/// [rename()]
///  -
/// [renameat()]
///  - 同rename，但是针对文件夹与文件相对路径分开的情况
///  - __old是相对路径，则一般是针对于__oldfd而言；但是对于__oldfd的值为AT_FDCWD时，是针对当前进程的相对路径路径
///  - __new同__old
///  - 几个错误码
///   - EBADF:__oldfd或__newfd不存在
///   - ENOTDIR：__oldfd或__newfd表述的是文件而非文件夹
/// [tmpfile()]
///  -  以二进制更新模式(wb+)创建临时文件。被创建的临时文件会在流关闭的时候或者在程序终止的时候自动删除。
///  - 失败则返回NULL
/// [tmpnam()]
///  - 生成并返回一个有效的临时文件名，该文件名之前是不存在的。如果 str 为空，则只会返回临时文件名
///  - 一个指向 C 字符串的指针，该字符串存储了临时文件名。如果 str 是一个空指针，则该指针指向一个内部缓冲区，缓冲区在下一次调用函数时被覆盖。
///  - 如果 str 不是一个空指针，则返回 str。如果函数未能成功创建可用的文件名，则返回一个空指针。
/// [tmpnam_r()]
///
/// [tempnam()]
///  - 生成唯一零时文件名
/// 依次执行下列四个判断，直到判断结果为真，则以此规则为目录：
/// 1、如果定义了环境变量TMPDIR，则使用其值作为目录。
/// 2、如果参数directory为非NULL并且存在，则使用其值作为目录
/// 3、将<stdio.h>中的字符串p_tmpdir用作目录
/// 4、将本地目录（通常是/tmp）作为目录
/// 如果prefix非空，则将其用作文件名头几个字符（最多5个）
/// 该函数用malloc函数分配动态存储区存放路径名，当不再使用此路径时会释放此存储区
/// [fclose()]
///  - 关闭流 stream。刷新所有的缓冲区
///  - 如果流成功关闭，则该方法返回零。如果失败，则返回 EOF。
///
/// [fflush()]
///  - 刷新流 stream 的输出缓冲区。
///  - 如果fflush返回EOF,数据可能由于写错误已经丢失。当设置一个重要错误处理器时,最安全的是用setvbuf函数关闭缓冲或者使用低级I/0例程,如open、close和write来代替流I/O函数。
/// [fflush_unlocked()]
///  - 与fflush()相对应
///  - 非线程安全
///  - 不应该被使用<>?为什么要提供这类_unlocked函数
///
/// [fopen()]
///  - [r/w/a][b][+]
///  - 打开方式的基本属性：原始数据可读|添加的数据是否可读|可写|文件指针位置|文本方式还是二进制
///  - 对于文本文件与二进制文件，unix系统相同，但是windows下文本文件换行符是"\r\n"，二进制文件换行符是"\n"
///  - dos/win 读文件时，会将换行符号CRLF(0x0D 0x0A)全部转换成单个的0x0A，并且当遇到结束符CTRLZ(0x1A)时，就认为文件已经结束。相应的，写文件时，会将所有的0x0A换成0x0D0x0A
///  - 因此文本方式读二进制数据时，可能读不完整
///  - 数据分成内存中的数据与硬盘中的数据，假设unix与win内存中的数据相同，但是硬盘中的数据可能不同，主要树换行符,内存（0x0A） <> 硬盘unix（0x0A）<>硬盘win（0x0D0x0A）
/// [freopen()]
///  - 将一个已经打开的流重定向到新的文件名，如将stdout重定向到一个文件
///  - 例程见下
/// [fdopen()]
///  - 为一个文件表述符创建一个流
///
/// [fmemopen()]
///  - 将一块内存作为文件打开，对文件的读写即为缓冲区与内存的操作
/// 1、buf参数指向缓冲区的起始位置，size参数指定了缓冲区大小的字节数；若buf为空，fmemopen函数分配size字节的缓冲区，当流关闭时缓冲区会被释放。
/// 2、当以追加方式打开内存流时，文件位置指针设置为缓冲区中第一个null字节处；若缓冲区中不存在null字节，则文件位置指针设置为缓冲区结尾的后一个字节处。
/// 3、如果buf参数是一个null指针，打开流进行读或者写没有任何意义。<与1冲突>
/// 4、增加流缓冲区中数据量且调用fclose、fflush、fseek、fseeo以及fsetpos中任一个时都会自动在当前位置写入一个null字节

/// [open_memstream()]
/// 1、创建的流只能写打开。
/// 2、不能指定缓冲区，但可以分别通过ptr和sizeloc参数访问缓冲区的地址和大小。
/// 3、关闭流后需要自行释放缓冲区。
/// 4、对流添加字节会增加缓冲区的大小。
/// [setbuf()]
/// - 定义流 stream 应如何缓冲。该函数应在与流 stream 相关的文件被打开时，且还未发生任何输入或输出操作之前被调用一次。
/// - buffer -- 这是分配给用户的缓冲，它的长度至少为 BUFSIZ 字节，BUFSIZ 是一个宏常量，表示数组的长度。
/// [setvbuf()]
///  - 定义流 stream 应如何缓冲。
///  - _IOFBF/_IOLBF/_IONBF 全缓冲/行缓冲/无缓冲
///  - buffer -- 这是分配给用户的缓冲。如果设置为 NULL，该函数会自动分配一个指定大小的缓冲。
/// [setbuffer()]
///  - 设置文件流的缓冲区。参数stream为指定的文件流，参数buf指向自定的缓冲区起始地址，参数size为缓冲区大小。
/// [setlinebuf()]
///  - 用来设置文件流以换行为依据的无缓冲IO
/// [snprintf()]
///  - 格式化将一段字符串写入内存
/// [vsnprintf()]
///  - 作用同snprintf
///  - 例程中有相互转换的代码
/// [vdprintf()]
///  - 格式化写入文件描述符
/// [dprintf()]
///  - 同上
/// [fscanf()]
///  - 从stream中格式化读取数据
/// [scanf()]
///  - 从stdint格式化读取数据
/// [sscanf()]
///  - 从字符串格式化读取数据
/// [vfscanf()]
///  - 同上
/// [vscanf()]
/// - 同上
/// [vsscanf()]
///  - 同上
/// [fgetc()]
///  - 读取一个字符串
/// [getc()]
///  - 同上
/// - 区别在于调用getc函数时所用的参数stream不能是有副作用的表达式(稍后解释)，而fgetc函数则可以，也就是说，getc可以被当作宏来调用，而fgetc只能作为函数来调用。
/// [getchar()]
/// [getc_unlocked()]
/// [getchar_unlocked()]
/// [fgetc_unlocked()]
/// [fputc()]
/// [putc()]
/// [putchar()]
/// [fputc_unlocked()]
/// [putc_unlocked()]
/// [putchar_unlocked()]
/// [getw()]
///  - Get a word (int) from STREAM
/// [putw()]
/// [fgets()]
///  -  从指定的流 stream 读取一行，并把它存储在 str 所指向的字符串内。当读取 (n-1) 个字符时，或者读取到换行符时，或者到达文件末尾时，它会停止，具体视情况而定
/// [__getdelim()]
///
/// [getdelim()]
///  - getline()的一般形式
///  - 读到某个分割符
/// [getline()]
///
/// [fputs()]
/// [puts()]
/// [ungetc()]
///  - 把字符 char（一个无符号字符）推入到指定的流 stream 中，以便它是下一个被读取到的字符
///  - char -- 这是要被推入的字符。该字符以其对应的 int 值进行传递。
///  - stream -- 这是指向 FILE 对象的指针，该 FILE 对象标识了输入流
/// [fread()]
/// [fwrite()]
/// [fread_unlocked()]
/// [fwrite_unlocked()]
/// [fseek()]
///  - 设置流 stream 的文件位置为给定的偏移 offset，参数 offset 意味着从给定的 whence 位置查找的字节数。
///   - stream -- 这是指向 FILE 对象的指针，该 FILE 对象标识了流。
///   - offset -- 这是相对 whence 的偏移量，以字节为单位。
///   - whence -- 这是表示开始添加偏移 offset 的位置。它一般指定为下列常量之一：
///    - SEEK_SET
///    - SEEK_CUR
///    - SEEK_END
/// [ftell()]
///  - 返回给定流 stream 的当前文件位置
///  - 该函数返回位置标识符的当前值。如果发生错误，则返回 -1L，全局变量 errno 被设置为一个正值
///
/// [rewind()]
///  - 设置文件位置为给定流 stream 的文件的开头
/// [fseeko()]
///  - 几个函数唯一的不同是offset的数据类型不同，相应的能够处理的偏移量的范围也就有大有小
/// [ftello()]
/// [fgetpos()]
///  - 获取当前流的位置
///  - 与fsetpos配合，可以反复从某个位置重写
/// [fsetpos()]
/// [clearerr()]
///  -  清除给定流 stream 的文件结束和错误标识符
///  - ferror()与clearerr()配合使用
///
/// [feof()]
///  - 函数 feof 只用于检测流文件，当文件内部位置指针指向文件结束时，并未立即置位 FILE 结构中的文件结束标记，只有再执行一次读文件操作，才会置位结束标志，此后调用 feof 才会返回为真
/// [ferror()]
///  - 测试给定流 stream 的错误标识符
///  - 如果设置了与流关联的错误标识符，该函数返回一个非零值，否则返回一个零值
//当文件流FILE* fp非法时，返回EOF（-1）。
//当文件流FILE* fp前面的操作发生错误时，返回1。
//并且由于文件流的错误只是使用一个标志位_IO_ERR_SEEN来表示的，因此ferror的返回值就不可能针对不同的错误返回不同的值了

/// [clearerr_unlocked()]
/// [feof_unlocked()]
/// [ferror_unlocked()]
/// [perror()]
/// [fileno()]
///  - fileno()用来取得参数stream指定的文件流所使用的文件描述词
/// [fileno_unlocked()]
/// [popen()]
///  - popen()函数通过创建一个管道，调用fork()产生一个子进程，执行一个shell以运行命令来开启一个进程。
///  - type参数只能是读或者写中的一种，得到的返回值（标准I/O流）也具有和type相应的只读或只写类型。
///  - 如果调用fork()或pipe()失败，或者不能分配内存将返回NULL，否则返回标准I/O流。popen()没有为内存分配失败设置errno值。如果调用fork()或pipe()时出现错误，errno被设为相应的错误类型。如果type参数不合法，errno将返回EINVAL。
/// [pclose()]
/// [ctermid()]
///  - 可被用来确定控制终端的名字。
///  - (详细地)描述，描画，解释;
///  - 通过为每个文件对象 FILE 赋予一个锁定计数和 (当锁定计数非零时) 一个所有者线程来实现的
///  - 用于线程见文件流加锁

/// [ftrylockfile()]
/// [funlockfile()]

void test_freopen(void);
int my_snprintf(char *s, int size, const char *fmt, ...);
void test_my_snprintf(void);


int main(int argc, char *argv[])
{
//  FILE *fp=NULL;

//  printf("off_t:%lu\n",sizeof (off_t));
//  printf("ssize_t:%lu\n",sizeof (ssize_t));
//  printf("fpos_t:%lu\n",sizeof (fpos_t));


//  off_t ot;
//  ssize_t st=-1;
////  fpos_t ft=1;
//  ot=st;

//  test_freopen();

  test_my_snprintf();
  
  printf("%s\n",ctermid(NULL));


  return 0;
}


void test_freopen(void){
  freopen("out.stream","a",stdout);
  printf("string to file\n");

}

int my_snprintf(char *s, int size, const char *fmt, ...) //该自定义函数，与系统提供的snprintf()函数相同。
{
    va_list ap;
    int n=0;
    va_start(ap, fmt); //获得可变参数列表
    n=vsnprintf (s, size, fmt, ap); //写入字符串s
    va_end(ap); //释放资源
    return n; //返回写入的字符个数
}


void test_my_snprintf(void){
  char str[1024];
  my_snprintf( str, sizeof(str), "%d,%d,%d,%d",5,6,7,8);
  printf("%s\n",str);
}


