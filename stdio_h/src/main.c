#include<stdio.h>
/// [FILE] 同struct _IO_FILE
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
/// [fflush_unlocked()]
///
/// [fopen()]
/// [freopen()]
/// [fdopen()]
/// [fmemopen()]
/// [open_memstream()]
/// [setbuf()]
/// [setvbuf()]
/// [setbuffer()]
/// [setlinebuf()]
/// [snprintf()]
/// [vsnprintf()]
/// [vdprintf()]
/// [dprintf()]
/// [fscanf()]
/// [scanf()]
/// [sscanf()]
/// [vfscanf()]
/// [vscanf()]
/// [vsscanf()]
/// [fgetc()]
/// [getc()]
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
/// [putw()]
/// [fgets()]
/// [__getdelim()]
/// [getdelim()]
/// [getline()]
/// [fputs()]
/// [puts()]
/// [ungetc()]
/// [fread()]
/// [fwrite()]
/// [fread_unlocked()]
/// [fwrite_unlocked()]
/// [fseek()]
/// [ftell()]
/// [rewind()]
/// [fseeko()]
/// [ftello()]
/// [fgetpos()]
/// [fsetpos()]
/// [clearerr()]
/// [feof()]
/// [ferror()]
/// [clearerr_unlocked()]
/// [feof_unlocked()]
/// [ferror_unlocked()]
/// [perror()]
/// [fileno()]
/// [fileno_unlocked()]
/// [popen()]
/// [pclose()]
/// [ctermid()]
/// [flockfile()]
/// [ftrylockfile()]
/// [funlockfile()]


int main(int argc, char *argv[])
{
//  FILE *fp=NULL;

  printf("off_t:%lu\n",sizeof (off_t));
  printf("ssize_t:%lu\n",sizeof (ssize_t));
  printf("fpos_t:%lu\n",sizeof (fpos_t));


  off_t ot;
  ssize_t st=-1;
//  fpos_t ft=1;
  ot=st;




  return 0;
}
