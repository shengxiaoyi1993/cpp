#include <gtk/gtk.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/time.h>
#include <memory.h>
#include <iostream>
#include <pthread.h>
#include <unistd.h>
#include "../../lib/common/lib/channel_imagebuffer/channel_imagebuffer.h"


using namespace std;

#define DEBUG
static ImageBufferChannel* g_customer=nullptr;
static GtkWidget *image_global=nullptr;
static GdkPixbuf* g_frame =nullptr;
//static unsigned int g_addr;
//static unsigned int g_width;
//static unsigned int g_height;
//static unsigned int g_interval;
static unsigned int g_display_w;
static unsigned int g_display_h;

static struct timeval tv_record;
static struct timezone tz_record;
static struct timeval tv_current;
static struct timezone tz_current;
static unsigned int g_delay=2000000;
static struct timeval tv_record_delay;
static struct timezone tz_record_delay;
static bool flag_display=false;
static pthread_mutex_t lock_display;


static void initTime(){

  gettimeofday(&tv_record, &tz_record);
}

static void outputTimeCost(){

  gettimeofday(&tv_current, &tz_current);
  unsigned int costtime=(tv_current.tv_sec-tv_record.tv_sec)*1000000+
      (tv_current.tv_usec-tv_record.tv_usec);
  printf("costtime:%u\n",costtime);
  initTime();
}



//描述该程序的若干选择
int printHelp();

//读取内存固定物理地址中的数据
//v_addr： 内存物理地址
//v_size： 读取的数据长度（字节）
//ppdata： 保存数据的指针，空间不需要在外部申请;
//        该指针指向的数据由固定地址的映射得到，不需要释放内存
//return:  若读取数据成功，则输出返回得到的数据字节数
//note：   该函数涉及内存读取等系统调用，需要用root运行
static int readBuferInRamWithMmap(
    unsigned int v_addr,
    unsigned int v_size,
    unsigned char** ppdata);

    /**
     * [CloseAppWindow  callback func ,used to quit gtk_main,when "delete_event" occurs]
     * @param  widget [description]
     * @param  data   [description]
     * @return        [description]
     */
gint CloseAppWindow (GtkWidget *widget, gpointer data)
{
  gtk_main_quit ();
  return (FALSE);
}


/**
 * [cb_GdkPixbufDestroyNotify callback func to free pointer]
 * @param pixels [description]
 * @param data   [description]
 */
void cb_GdkPixbufDestroyNotify(guchar *pixels, gpointer data){
  free(pixels);
  pixels=nullptr;
}



/**
 * [getMsg callback function concluded when receive data from channel]
 * @param v_data  [description]
 * @param v_pdata [description]
 */
void getMsg(ImageBufferInArm v_data,void*v_pdata){

  std::cout<<"[start]"<<__func__<<endl;

  (void)v_pdata;

  initTime();

  static int count=0;
  unsigned char *pdata = nullptr;
  unsigned g_height=v_data._height;
  unsigned g_width=v_data._width;
  int size = readBuferInRamWithMmap(v_data._paddr,v_data._height*v_data._width
                                    *sizeof(unsigned char),&pdata);

  if(size != g_height*g_width*sizeof(unsigned char)){
    printf("%s\n", "fail to read buffer!");
  }
  else{
    printf("%s\n","succeed to readBuferInRamWithMmap" );
    outputTimeCost();

    if(pdata == nullptr){
      printf("%s\n","pdata == nullptr" );
    }
    else{
      printf("%s\n","pdata != nullptr" );

      pthread_mutex_lock( &lock_display ) ;

      //跳过第一张图片，否则可能出现画面卡住
      static bool fflag=true;
      if(fflag){
        usleep(500000);
        fflag=false;
      }

      GdkPixbuf* g_frame = nullptr;
      g_frame = gdk_pixbuf_new_from_data(pdata,GDK_COLORSPACE_RGB,FALSE,8,
        g_width/3,g_height,g_width,nullptr,nullptr);
      printf("%s\n","gdk_pixbuf_new_from_data" );
      outputTimeCost();
      if(g_frame == nullptr){
        printf("g_frame == nullptr\n" );
      }
      else{
        printf("g_frame != nullptr\n" );
      }

      gtk_image_set_from_pixbuf( GTK_IMAGE(image_global),g_frame);
      printf("%s\n","gtk_image_set_from_pixbuf" );
      outputTimeCost();

      g_object_unref(G_OBJECT(g_frame));	// pixbuf使用完，需要人为释放资源
      g_frame=nullptr;
      v_data._status=true;

      pthread_mutex_unlock( &lock_display ) ;

      printf("%s\n","succeed to end" );
      outputTimeCost();

    }

  }

  //通知驱动端该数据已处理
  int flag_return=g_customer->addNewImageBufferInArm(v_data);

}



int main(int argc, char *argv[])  {
  if(argc != 2){
    printf("\n>>Error:param not match\n\n");
    printHelp();
    return -1;
  }
  pthread_mutex_init( &lock_display,NULL ) ;


  sscanf(argv[1],"%u*%u",&g_display_w,&g_display_h);

#ifdef DEBUG
  printf("g_display_w:  %u\n", g_display_w);
  printf("g_display_h:  %u\n", g_display_h);
#endif

  {

    GtkWidget *windows;

    gtk_init(&argc,&argv);
    windows = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gettimeofday(&tv_record_delay, &tz_record_delay);

    gint v_datalength=g_display_w*g_display_h*3*sizeof(char);
    char *pdata=(char*)malloc(v_datalength);
    memset(pdata,0,v_datalength);
    GBytes * gbyte3=g_bytes_new(pdata,v_datalength);
    g_frame = gdk_pixbuf_new_from_bytes(
          gbyte3,GDK_COLORSPACE_RGB,FALSE,8,g_display_w,g_display_h,g_display_w*3);
    image_global = gtk_image_new_from_pixbuf(g_frame);	// 通过pixbuf创建图片控件
    gtk_widget_set_size_request (windows, g_display_w, g_display_h);
    gtk_signal_connect (GTK_OBJECT (windows), "delete_event",
                        GTK_SIGNAL_FUNC (CloseAppWindow), nullptr);
    gtk_container_add (GTK_CONTAINER (windows),  image_global);
    gtk_widget_show_all(GTK_WIDGET (windows));

    g_customer=new ImageBufferChannel(MsgChannel_Mode::customer,
                                      ImageBufferChannel_TYPE_Display,
                                      getMsg,nullptr);
    //init fpga regster,make all image block available
    ImageBufferInArm v_data;
    v_data._mode=0;
    g_customer->addNewImageBufferInArm(v_data);
    v_data._mode=1;
    g_customer->addNewImageBufferInArm(v_data);
    v_data._mode=2;
    g_customer->addNewImageBufferInArm(v_data);
    v_data._mode=3;
    g_customer->addNewImageBufferInArm(v_data);

    gtk_main();
  }


  return 0;
}



static int readBuferInRamWithMmap(
    unsigned int v_addr,
    unsigned int v_size,
    unsigned char** ppdata){
  printf("readBuferInRamWithMmap addr:0x%x\n",v_addr );
  int ret=0;
  int fd;
  fd = open("/dev/mem",O_RDWR);
  if(fd< 0)
  {
    printf("open /dev/mem failed.\n");
    fflush(stdout);
    return -1;
  }

  //直接使用物理地址映射的内存
  *ppdata=(unsigned char*)mmap(nullptr,sizeof(unsigned char )*v_size,
                               PROT_READ|PROT_WRITE,MAP_SHARED,fd,v_addr);
  if (*ppdata == MAP_FAILED) {
    printf("failed to mmap /dev/mem!\n");
    ret=-1;
  }
  else{
    ret=v_size;
  }

  close(fd);
  return ret;
}


int printHelp(){
  printf("please input params as below:\n" );
  printf("./showImageInMem  [screen_width*screen_height]\n" );
  printf("note:     please run as root  \n" );
  printf("e.g.:     ./displaydemo 1024*1024\n" );
  return 0;
}
