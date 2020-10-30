#include <gtk/gtk.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/time.h>
#include <memory.h>
#include <sstream>
#include <iostream>
#include <pthread.h>
#include <unistd.h>
#include "../../lib/common/lib/channel_imagebuffer/channel_imagebuffer.h"
#include "../../lib_copy/pnm/pnm.h"


using namespace std;

#define DEBUG
static ImageBufferChannel* g_customer=nullptr;
static GtkWidget *image_global=nullptr;
//static unsigned int g_addr;
//static unsigned int g_width;
//static unsigned int g_height;
//static unsigned int g_interval;
static unsigned int g_display_w;
static unsigned int g_display_h;
static int g_imagetype;

static struct timeval tv_record;
static struct timezone tz_record;
static struct timeval tv_current;
static struct timezone tz_current;
static unsigned int g_delay=2000000;
static struct timeval tv_record_delay;
static struct timezone tz_record_delay;
static bool flag_display=false;
static pthread_mutex_t lock_display;
static uint g_size_mmap;
static int g_count=0;





static void initTime(){

  gettimeofday(&tv_record, &tz_record);
}

static void outputTimeCost(){

  gettimeofday(&tv_current, &tz_current);
  unsigned int costtime=(tv_current.tv_sec-tv_record.tv_sec)*1000000+
      (tv_current.tv_usec-tv_record.tv_usec);
  printf("++++++++++++++++++++++++++++++++costtime:%u+++++++++++++++++++++++++++++\n",costtime);
  initTime();
}



string stringFromInt(int v_value){
  string ret;
  stringstream ss;
  ss<<v_value;
  ss>>ret;
  return ret;

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



//读取内存固定物理地址中的数据
//映射内存区域，转存至某一区域，然后解除映射
static int readBuferDataInRamWithMmap(
    unsigned int v_addr,
    unsigned int v_size,
    unsigned char** ppdata);



//从映射的内存读取一定区域的图片
static int readBuferRectInRamWithMmap(unsigned int v_addr_src,
                                      unsigned int v_height_src,
                                      unsigned int v_stride_src, unsigned int v_bits,
                                      unsigned int v_width_dst,
                                      unsigned int v_height_dst,
                                      unsigned char** ppdata_dst);



/**
 * [cb_GdkPixbufDestroyNotify callback func to free pointer]
 * @param pixels [description]
 * @param data   [description]
 */
void cb_GdkPixbufDestroyNotify(guchar *pixels, gpointer data){
  std::cout<<"[start]"<<__func__<<endl;
  std::cout<<"[g_size_mmap]"<<g_size_mmap<<endl;

  fflush(stdout);

  munmap(pixels,g_size_mmap);
  //  free(pixels);
  pixels=nullptr;
  std::cout<<"[done]"<<__func__<<endl;

}

void cb_freee_GdkPixbufDestroyNotify(guchar *pixels, gpointer data){
  std::cout<<"[start]"<<__func__<<endl;
  std::cout<<"[g_size_mmap]"<<g_size_mmap<<endl;

  fflush(stdout);
  free(pixels);
  pixels=nullptr;
  std::cout<<"[done]"<<__func__<<endl;

}






/**
 * [getMsg callback function concluded when receive data from channel]
 * @param v_data  [description]
 * @param v_pdata [description]
 */
void cb_saveData(ImageBufferInArm v_data,void*v_pdata){

  std::cout<<"[start]"<<__func__<<endl;

  std::cout<<"[_loc:]"<<v_data._loc<<endl;


  uint bits_image;
  if (v_data._mode != g_imagetype) {
    return;
  }

  if(g_imagetype ==0){
    bits_image=1;
  }
  else if(g_imagetype == 1){
    bits_image=3;
  }

  (void)v_pdata;

  initTime();


  string path_image=stringFromInt(g_count)+".pnm";
  unsigned char *pdata_src = nullptr;
  unsigned g_height=v_data._height;
  unsigned g_width=v_data._width;
  g_size_mmap=v_data._height*v_data._width
      *sizeof(unsigned char)*bits_image;
  int size = readBuferDataInRamWithMmap(v_data._paddr,v_data._height*v_data._width
                                        *sizeof(unsigned char)*bits_image,&pdata_src);
  cout<<"size:"<<size<<endl;
  cout<<"g_height:"<<g_height<<endl;
  cout<<"g_width:"<<g_width<<endl;


  if(size != bits_image*g_height*g_width*sizeof(unsigned char)){
    printf("%s\n", "fail to read buffer!");
  }
  else{
    printf("%s\n","succeed to readBuferInRamWithMmap" );
    outputTimeCost();

    if(pdata_src == nullptr){
      printf("%s\n","pdata_src == nullptr" );
    }
    else{
      printf("%s\n","pdata_src != nullptr" );

      pthread_mutex_lock( &lock_display ) ;



      unsigned short *pdata=new unsigned short[4096*4096*3];
      for (size_t i = 0; i < 4096*4096*3; i++) {
        pdata[i]=static_cast<unsigned short>(pdata_src[i]);
        pdata[i]<<=8;
        // pdata[i]=pdata[i]<255?pdata[i]:255;
      }

      //    //以16个元素作为一个单元进行反转
      //      for (size_t i = 0; i < 4096*4096*3/16; i++) {
      //        for (size_t j = 0; j < 16/2; j++) {
      //          unsigned short tmp=pdata[i*16+16-j-1];
      //          pdata[i*16+16-j-1]=pdata[i*16+j];
      //          pdata[i*16+j]=tmp;
      //        }
      //        // pdata[i]=pdata[i]<255?pdata[i]:255;
      //      }



      PNM::saveDataToFile(path_image,PNM::DataType_rgb,PNM::MagicNumber_p6,
                          pdata,4096,4096,255);
      delete []pdata;


      pthread_mutex_unlock( &lock_display ) ;

      printf("%s\n","succeed to end" );
      outputTimeCost();

    }

  }

  g_count++;
  //通知驱动端该数据已处理
  int flag_return=g_customer->addNewImageBufferInArm(v_data);

}




/**
 * [getMsg callback function concluded when receive data from channel]
 * @param v_data  [description]
 * @param v_pdata [description]
 */
void cb_display_with_copy(ImageBufferInArm v_data,void*v_pdata){

  std::cout<<"[start]"<<__func__<<endl;
  std::cout<<"[_mode:]"<<v_data._mode<<endl;
  std::cout<<"[_loc:]"<<v_data._loc<<endl;
  fflush(stdout);

  uint bits_image;
  if (v_data._mode != g_imagetype) {
    return;
  }

  //  pthread_mutex_lock( &lock_display );

  if(g_imagetype ==0){
    bits_image=1;
  }
  else if(g_imagetype == 1){
    bits_image=4;
  }

  (void)v_pdata;

  initTime();


  string path_image=stringFromInt(g_count)+".pnm";
  unsigned char *pdata = nullptr;
  unsigned g_height=v_data._height;
  unsigned g_width=v_data._width;
  g_size_mmap=v_data._height*v_data._width
      *sizeof(unsigned char)*bits_image;
  int size = readBuferRectInRamWithMmap(v_data._paddr,
                                        v_data._height,
                                        v_data._width,
                                        bits_image,
                                        1920,
                                        1080
                                        ,&pdata);

  if(size != 0){
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


      //跳过第一张图片，否则可能出现画面卡住
      static bool fflag=true;
      if(g_imagetype==0){
        if(fflag){
          usleep(300000);
          fflag=false;
        }
      }else{
        if(fflag){
          usleep(500000);
          fflag=false;
        }
        //        usleep(50000);
      }

      std::cout<<"[before gdk_pixbuf_new_from_data]"<<v_data._loc<<endl;
      fflush(stdout);
      GdkPixbuf* g_frame = nullptr;
      g_frame = gdk_pixbuf_new_from_data(pdata,GDK_COLORSPACE_RGB,TRUE,8,
                                         1920,1080,1920*bits_image,cb_freee_GdkPixbufDestroyNotify,nullptr);
      std::cout<<"[after gdk_pixbuf_new_from_data]"<<v_data._loc<<endl;
      fflush(stdout);

      printf("%s\n","gdk_pixbuf_new_from_data" );
      outputTimeCost();
      if(g_frame == nullptr){
        printf("g_frame == nullptr\n" );
      }
      else{

        //拷贝显示

        {
          std::cout<<"[before gtk_image_set_from_pixbuf]"<<v_data._loc<<endl;
          fflush(stdout);

          gtk_image_set_from_pixbuf( GTK_IMAGE(image_global),g_frame);

          if(GTK_IMAGE (image_global)->storage_type==GTK_IMAGE_EMPTY){
            printf("GTK_IMAGE (image_global)->storage_type==GTK_IMAGE_EMPTY\n");
          }
          //          G_OBJECT(g_frame)->ref_count;
          g_object_unref(g_frame);
          v_data._status=true;


          printf("%s\n","  to end" );
          outputTimeCost();

        }

      }

    }
    cout<<"finish display image"<<endl;
    fflush(stdout);

  }
  //  munmap(pdata,g_size_mmap);

  cout<<"before return feedback to front"<<endl;
  fflush(stdout);

  g_count++;
  //通知驱动端该数据已处理
  int flag_return=g_customer->addNewImageBufferInArm(v_data);
  cout<<"finish return feedback to front"<<endl;
  fflush(stdout);


  cout<<"================"<<g_count<<"=================="<<endl;
  //  pthread_mutex_unlock( &lock_display ) ;

}





//測試
//1. 理論上是在單一子線程中循環運行，需要測試

/**
 * [getMsg callback function concluded when receive data from channel]
 * @param v_data  [description]
 * @param v_pdata [description]
 */
void getMsg(ImageBufferInArm v_data,void*v_pdata){
  std::cout<<"[start]"<<__func__<<endl;
  cout<<"================"<<g_count<<" start=================="<<endl;

  fflush(stdout);

  //圖片通道數量
  uint bits_image;

  //g_imagetype由用戶指定
  //只接受某一格式的圖片
  if (v_data._mode != g_imagetype) {
    return;
  }

  //  pthread_mutex_lock( &lock_display );

  //根據用戶設定的格式，確定圖片通道數
  //現支持1通道和3通道的
  if(g_imagetype ==0){
    bits_image=1;
  }
  else if(g_imagetype == 1){
    bits_image=4;
  }

  (void)v_pdata;

  initTime();

  //以映射方式讀取圖片
  unsigned char *pdata = nullptr;
  unsigned g_height=v_data._height;
  unsigned g_width=v_data._width;
  g_size_mmap=v_data._height*v_data._width
      *sizeof(unsigned char)*bits_image;
  int size = readBuferInRamWithMmap(v_data._paddr,
                                    v_data._height*v_data._width*sizeof(unsigned char)*bits_image,
                                    &pdata);

  if(size != bits_image*g_height*g_width*sizeof(unsigned char)){
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


      //跳过第一张图片，否则可能出现画面卡住
      static bool fflag=true;
      if(g_imagetype==0){
        if(fflag){
          usleep(300000);
          fflag=false;
        }
      }else{
        if(fflag){
          usleep(500000);
          fflag=false;
        }
        //        usleep(50000);

      }


      std::cout<<"[before gdk_pixbuf_new_from_data]"<<v_data._loc<<endl;
      fflush(stdout);

      //显示图片的一小块
      GdkPixbuf* frame_tmp = gdk_pixbuf_new_from_data(pdata,GDK_COLORSPACE_RGB,TRUE,8,
                                                    1920,1080,g_width*bits_image,cb_GdkPixbufDestroyNotify,nullptr);
      std::cout<<"[after gdk_pixbuf_new_from_data]"<<v_data._loc<<endl;
      fflush(stdout);

      //顯示全部圖片
      //      frame_tmp = gdk_pixbuf_new_from_data(pdata,GDK_COLORSPACE_RGB,TRUE,8,
      //                                         g_width,g_height,g_width*bits_image,cb_GdkPixbufDestroyNotify,nullptr);

      printf("%s\n","gdk_pixbuf_new_from_data" );
      outputTimeCost();
      if(frame_tmp == nullptr){
        printf("frame_tmp == nullptr\n" );
      }
      else{

        //直接映射方法显示图片

        {

          std::cout<<"[before gtk_image_set_from_pixbuf]"<<v_data._loc<<endl;
          fflush(stdout);

          //按照代码
          //每当数据重新设置新图片时，原图片都会析构
          gtk_image_set_from_pixbuf( GTK_IMAGE(image_global),frame_tmp);
          std::cout<<"[after gtk_image_set_from_pixbuf]"<<v_data._loc<<endl;
          fflush(stdout);

          v_data._status=true;
          g_object_unref(frame_tmp);

          printf("%s\n","succeed to end" );
          outputTimeCost();

        }

      }

    }
    cout<<"finish display image"<<endl;
    fflush(stdout);

  }
  //  munmap(pdata,g_size_mmap);

  cout<<"before return feedback to front"<<endl;
  fflush(stdout);

  g_count++;
  //通知驱动端该数据已处理
  int flag_return=g_customer->addNewImageBufferInArm(v_data);
  cout<<"finish return feedback to front"<<endl;
  fflush(stdout);


  cout<<"================"<<g_count<<" end=================="<<endl;
  //  pthread_mutex_unlock( &lock_display ) ;

}



int main(int argc, char *argv[])  {
  if(argc != 3){
    printf("\n>>Error:param not match\n\n");
    printHelp();
    return -1;
  }
  pthread_mutex_init( &lock_display,NULL ) ;

  char imagetype[32];

  sscanf(argv[1],"%u*%u",&g_display_w,&g_display_h);
  sscanf(argv[2],"%s",imagetype);

  if(strcmp("raw",imagetype) == 0){
    g_imagetype=0;
  }
  else if(strcmp("rgb",imagetype) == 0){
    g_imagetype=1;
  }
  else{
    printf("Error:image_type not match\n");
    throw "Error:image_type not match";
  }

#ifdef DEBUG
  printf("g_display_w:  %u\n", g_display_w);
  printf("g_display_h:  %u\n", g_display_h);
  printf("imagetype:  %s\n", imagetype);
#endif

  {

    GtkWidget *windows;

    gtk_init(&argc,&argv);
    windows = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gettimeofday(&tv_record_delay, &tz_record_delay);

    gint v_datalength=g_display_w*g_display_h*3*sizeof(char);
    unsigned char *pdata=(unsigned char*)malloc(v_datalength);
    memset(pdata,0,v_datalength);
//    GBytes * gbyte3=g_bytes_new(pdata,v_datalength);
//    GdkPixbuf* g_frame = gdk_pixbuf_new_from_bytes(
//          gbyte3,GDK_COLORSPACE_RGB,FALSE,8,g_display_w,g_display_h,g_display_w*3);

    GdkPixbuf* g_frame = gdk_pixbuf_new_from_data(pdata,GDK_COLORSPACE_RGB,FALSE,8,
                                                  g_display_w,g_display_h,g_display_w*3,cb_GdkPixbufDestroyNotify,nullptr);


    image_global = gtk_image_new_from_pixbuf(g_frame);	// 通过pixbuf创建图片控件
    g_object_unref(g_frame);
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
    v_data._status=1;
    v_data._mode=0;
    v_data._loc=0;
    g_customer->addNewImageBufferInArm(v_data);
    v_data._loc=1;
    g_customer->addNewImageBufferInArm(v_data);
    v_data._loc=2;
    g_customer->addNewImageBufferInArm(v_data);
    v_data._loc=3;
    g_customer->addNewImageBufferInArm(v_data);
    v_data._mode=1;
    v_data._loc=0;
    g_customer->addNewImageBufferInArm(v_data);
    v_data._loc=1;
    g_customer->addNewImageBufferInArm(v_data);
    v_data._loc=2;
    g_customer->addNewImageBufferInArm(v_data);
    v_data._loc=3;
    g_customer->addNewImageBufferInArm(v_data);

    gtk_main();
  }


  return 0;
}



static int readBuferDataInRamWithMmap(
    unsigned int v_addr,
    unsigned int v_size,
    unsigned char** ppdata){
  int ret=0;
  int fd;
  fd = open("/dev/mem",O_RDWR);
  if(fd< 0)
  {
    printf("open /dev/mem failed.\n");
    fflush(stdout);
    return -1;
  }
  *ppdata=(unsigned char *)malloc(v_size*sizeof(unsigned char));
  memset(*ppdata,'\0',v_size*sizeof(unsigned char));
  if(*ppdata == NULL){
    printf("failed MALLOC.\n");
    fflush(stdout);
    ret=-1;
  }
  else{
    void *data=mmap(NULL,sizeof(unsigned char )*v_size,
                    PROT_READ|PROT_WRITE,MAP_SHARED,fd,v_addr);
    if (data == MAP_FAILED) {
      printf("failed to mmap /dev/mem!\n");
      free(*ppdata);
      *ppdata=NULL;
      ret=-1;
    }
    else{
      memcpy(*ppdata,data,sizeof(unsigned char )*v_size);
      ret=v_size;
      munmap(data,v_size);

    }
  }

  close(fd);
  return ret;
}


//截取左上角的区域
static int readBuferRectInRamWithMmap(
    unsigned int v_addr_src,
    unsigned int v_height_src,
    unsigned int v_stride_src,
    unsigned int v_bits,
    unsigned int v_width_dst,
    unsigned int v_height_dst,
    unsigned char** ppdata_dst){

  if(v_width_dst>v_stride_src||v_height_dst>v_height_src){
    return -1;
  }

  printf("v_addr_src:0x%x\n",v_addr_src);
  printf("v_height_src:%u\n",v_height_src);
  printf("v_stride_src:%u\n",v_stride_src);
  printf("v_bits:%u\n",v_bits);
  printf("v_width_dst:%u\n",v_width_dst);
  printf("v_height_dst:%u\n",v_height_dst);


  printf("%s\n",__func__ );
  outputTimeCost();

  int ret=0;
  int fd;
  unsigned int size_src=v_height_src*v_stride_src*v_bits;
  unsigned int size_dst=v_width_dst*v_height_dst*v_bits;

  fd = open("/dev/mem",O_RDWR);
  if(fd< 0)
  {
    printf("open /dev/mem failed.\n");
    fflush(stdout);
    return -1;
  }


  //申请目的内存
  *ppdata_dst=(unsigned char *)malloc(size_dst*sizeof(unsigned char));
  //      *ppdata_dst=(unsigned char *)malloc(size_src*sizeof(unsigned char));


  printf("size_dst:%d\n",size_dst);
  printf("%s\n"," malloc mem:" );
  outputTimeCost();

  if(*ppdata_dst == NULL){
    printf("failed MALLOC.\n");
    fflush(stdout);
    ret=-1;
  }
  else{
    //    memset(*ppdata_dst,'\0',size_dst*sizeof(unsigned char));


    //映射某一区域
    void *data=mmap(NULL,sizeof(unsigned char )*size_src,
                    PROT_READ|PROT_WRITE,MAP_SHARED,fd,v_addr_src);
    printf("%s\n"," mmap mem:" );
    outputTimeCost();
    if (data == MAP_FAILED) {
      printf("failed to mmap /dev/mem!\n");
      free(*ppdata_dst);
      *ppdata_dst=NULL;
      ret=-1;
    }
    else{
      //成功映射
      //将目标数据拷贝到目标区域
      printf("将目标数据拷贝到目标区域\n");
      fflush(stdout);

      unsigned char* psrc=(unsigned char*)data;
      printf("after将目标数据拷贝到目标区域\n");
      fflush(stdout);

      //拷贝整片内存需要400ms左右时间
      //逐行拷贝的总时间也就50ms左右

      //rgba
      //拷贝整片内存需要680ms左右时间
      //逐行拷贝的总时间也就70ms左右
      //但是显示的时间都比较长需要1s以上
      for(uint i=0;i<v_height_dst;i++){
        memcpy(*ppdata_dst+v_width_dst*v_bits*i,
               psrc+v_stride_src*v_bits*i,
               sizeof(unsigned char )*v_width_dst*v_bits);
      }

      //                  memcpy(*ppdata_dst,data,size_src);
      printf("%s\n"," memcpy mem:" );
      outputTimeCost();
      ret=0;
      //拷贝成功
      //解除映射
      munmap(data,size_src);
      printf("%s\n"," munmap mem:" );
      outputTimeCost();
    }
  }

  close(fd);
  return ret;


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
  printf("./showImageInMem  [screen_width*screen_height] [image_type]\n" );
  printf("image_type:    'raw' or 'rgb' " );
  printf("note:     please run as root  \n" );
  printf("e.g.:     ./displaydemo 1920*1080\n" );
  return 0;
}
