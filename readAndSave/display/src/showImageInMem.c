#include <gtk/gtk.h>
#include <stdio.h>
#include <stdio.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/time.h>

#define DEBUG

static GtkWidget *image_global=NULL;
static GdkPixbuf* g_frame =NULL;
static unsigned int g_addr;
static unsigned int g_width;
static unsigned int g_height;
static unsigned int g_interval;
static unsigned int g_display_w;
static unsigned int g_display_h;

static struct timeval tv_record;
static struct timezone tz_record;
static struct timeval tv_current;
static struct timezone tz_current;
//描述该程序的若干选择
int printHelp();
//将row数据转换成三个通道的数据
void bayer_cfa_7x7(unsigned short *bayer_src, unsigned short res_w, unsigned short res_h,
                   unsigned short *bayer_dst_r, unsigned short *bayer_dst_g, unsigned short *bayer_dst_b);

//将row数据保存为rgb图片文件
int getimage(const char* path_input,
             unsigned int v_width,
             unsigned int v_height,
             const char* path_output);


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
  pixels=NULL;
}

/**
 * [RawToRgb transform image data of raw format to rgb]
 * @param  psrc     [raw data ,which has pixels of 8 bits]
 * @param  v_width  [width of image]
 * @param  v_height [height of image]
 * @param  pdst     [target pointer to save rgb data]
 * @return          [return 0 if succeed ,otherwise fail]
 */
int RawToRgb(unsigned char *psrc,
             unsigned int v_width,
             unsigned int v_height,
             unsigned char** pdst);


/**
 * [getSingleChannelData  transform image data of raw format to rgb(single channel)
 *  so as to display the image quickly ]
 * @param  psrc     [raw data ,which has pixels of 8 bits]
 * @param  v_width  [width of image]
 * @param  v_height [height of image]
 * @param  pdst     [target pointer to save rgb data(single channel)]
 * @return          [return 0 if succeed ,otherwise fail]
 */
int getSingleChannelData(
    unsigned char *psrc,
    unsigned int v_width,
    unsigned int v_height,
    unsigned char** pdst);


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

/**
 * [display_imageWithTranform same function as display_image(...),
 * to read image in Mem and display ,
 * but it tranform raw data to rgb(three channels or single channel),
 * the refresh rate of image can not be too short
 * (single channel 2s/fram, tri channels 60s/frame)]
 */
static gboolean display_imageWithTranform(){
  printf("%s\n", ">> display_image start");
  initTime();
  unsigned char *pdata = NULL;

  int size = readBuferInRamWithMmap(g_addr,g_height*g_width*sizeof(unsigned char),&pdata);
  if(size != g_height*g_width*sizeof(unsigned char)){
    printf("%s\n", "fail to read buffer!");
    return ;
  }

  printf("%s\n","succeed to readBuferInRamWithMmap" );
  outputTimeCost();

  if(pdata == NULL){
    printf("%s\n","pdata == NULL" );
    return TRUE;
  }
  else{
    printf("%s\n","pdata != NULL" );
  }
  GdkPixbuf* g_frame = NULL;
  g_frame = gdk_pixbuf_new_from_data(pdata,GDK_COLORSPACE_RGB,
                                     FALSE,8,g_width,g_height,g_width*3,NULL,NULL);

  if(g_frame == NULL){
    printf("g_frame == NULL\n" );
  }
  else{
    printf("g_frame != NULL\n" );

  }

  // 进行数据的拷贝
  unsigned char *pdst = NULL;

  if(getSingleChannelData(pdata,g_width,g_height,&pdst)==0){
    // free(pdata);
    // pdata=NULL;
    printf("%s\n","succeed to getSingleChannelData" );
    outputTimeCost();

    GdkPixbuf* g_frame = NULL;
    g_frame = gdk_pixbuf_new_from_data(pdst,GDK_COLORSPACE_RGB,
                                       FALSE,8,g_width,g_height,g_width*3,
                                       cb_GdkPixbufDestroyNotify,NULL);
    printf("%s\n","succeed to gdk_pixbuf_new_from_data" );
    outputTimeCost();


    if(g_frame == NULL){
      printf("%s\n","g_frame == NULL" );
      return;
    }
    // GdkPixbuf *dst_pixbuf = gdk_pixbuf_scale_simple(g_frame, g_display_w, g_display_h, GDK_INTERP_BILINEAR);
    GdkPixbuf *dst_pixbuf = gdk_pixbuf_new(GDK_COLORSPACE_RGB,
                                           FALSE,8,g_display_w,g_display_h);
    gdk_pixbuf_copy_area(g_frame,0,0, g_display_w, g_display_h,dst_pixbuf,0,0);
    printf("%s\n","succeed to gdk_pixbuf_copy_area" );
    outputTimeCost();

    if(dst_pixbuf == NULL){
      printf("%s\n","dst_pixbuf == NULL" );
      return;
    }
    gtk_image_set_from_pixbuf( GTK_IMAGE(image_global),dst_pixbuf);
    printf("%s\n","succeed to gtk_image_set_from_pixbuf" );
    outputTimeCost();

    g_object_unref(G_OBJECT(dst_pixbuf));	// pixbuf使用完，需要人为释放资源
    dst_pixbuf=NULL;
    g_object_unref(G_OBJECT(g_frame));	// pixbuf使用完，需要人为释放资源
    g_frame=NULL;

  }
  else{
    printf("%s\n","fail to getSingleChannelData" );

    // free(pdata);
    // pdata=NULL;
  }

  printf("%s\n","succeed to end" );
  outputTimeCost();


}


/**
 * [display_image same function as display_imageWithTranform(...),
 * to read image in Mem and display ,
 * but it does not tranform raw data to rgb to display image quickly,
 * so the image may look strange]
 */

static gboolean display_image(){
  printf("%s\n", ">> display_image start");
  initTime();

  unsigned char *pdata = NULL;

  int size = readBuferInRamWithMmap(g_addr,g_height*g_width*sizeof(unsigned char),&pdata);
  if(size != g_height*g_width*sizeof(unsigned char)){
    printf("%s\n", "fail to read buffer!");
    return TRUE;
  }

  printf("%s\n","succeed to readBuferInRamWithMmap" );
  outputTimeCost();

  if(pdata == NULL){
    printf("%s\n","pdata == NULL" );
    return TRUE;
  }
  else{
    printf("%s\n","pdata != NULL" );

  }

  GdkPixbuf* g_frame = NULL;
  g_frame = gdk_pixbuf_new_from_data(pdata,GDK_COLORSPACE_RGB,
                                     FALSE,8,g_width/3,g_height,g_width,NULL,NULL);
  printf("%s\n","gdk_pixbuf_new_from_data" );
  outputTimeCost();
  if(g_frame == NULL){
    printf("g_frame == NULL\n" );
  }
  else{
    printf("g_frame != NULL\n" );
  }

  gtk_image_set_from_pixbuf( GTK_IMAGE(image_global),g_frame);
  printf("%s\n","gtk_image_set_from_pixbuf" );
  outputTimeCost();

  g_object_unref(G_OBJECT(g_frame));	// pixbuf使用完，需要人为释放资源
  g_frame=NULL;

  printf("%s\n","succeed to end" );
  outputTimeCost();
  return TRUE;

}



static void test_call(){
  printf("%s\n", "test_call");
  return;
}



int main(int argc, char *argv[])  {
  if(argc!= 6){
    printf("\n>>Error:param not match\n\n");
    printHelp();
    return -1;
  }


  sscanf(argv[1],"%x",&g_addr);
  sscanf(argv[2],"%u",&g_width);
  sscanf(argv[3],"%u",&g_height);
  sscanf(argv[4],"%u",&g_interval);
  sscanf(argv[5],"%u*%u",&g_display_w,&g_display_h);

#ifdef DEBUG
  printf("g_addr:       0x%x\n", g_addr);
  printf("g_width:      %u\n", g_width);
  printf("g_height:     %u\n", g_height);
  printf("g_interval:   %u\n", g_interval);
  printf("g_display_w:  %u\n", g_display_w);
  printf("g_display_h:  %u\n", g_display_h);
#endif

  {

    GtkWidget *windows;

    gtk_init(&argc,&argv);
    windows = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    //显示界面初始状态
    gint v_datalength=g_display_w*g_display_h*3*sizeof(char);
    char *pdata=(char*)malloc(v_datalength);
    memset(pdata,0,v_datalength);
    GBytes * gbyte3=g_bytes_new(pdata,v_datalength);
    g_frame = gdk_pixbuf_new_from_bytes(
          gbyte3,GDK_COLORSPACE_RGB,FALSE,8,g_display_w,g_display_h,g_display_w*3);
    image_global = gtk_image_new_from_pixbuf(g_frame);	// 通过pixbuf创建图片控件
    gtk_widget_set_size_request (windows, g_display_w, g_display_h);
    gtk_widget_set_size_request (image_global, g_display_w, g_display_h);

    gtk_signal_connect (GTK_OBJECT (windows), "delete_event",
                        GTK_SIGNAL_FUNC (CloseAppWindow), NULL);
    g_timeout_add(g_interval, (GSourceFunc)display_image,NULL);
    gtk_container_add (GTK_CONTAINER (windows),  image_global);
    gtk_widget_show_all(GTK_WIDGET (windows));
    gtk_main();
  }


  return 0;
}


void bayer_cfa_7x7(unsigned short *bayer_src, unsigned short res_w, unsigned short res_h,
                   unsigned short *bayer_dst_r, unsigned short *bayer_dst_g, unsigned short *bayer_dst_b) {
  // --{{{
  int   i, j, l, k, m, n;
  short loc_x, loc_y;
  unsigned short bayer_set[7*7];
  int   calc_temp[24];
  int   h_diff, v_diff, nw_diff, sw_diff;
  int   pixel_temp_r, pixel_temp_g, pixel_temp_b;

  unsigned short max_output_value = 4095;

  for (j=0; j<res_h; j++) {
    for (i=0; i<res_w; i++) {
      // get bayer_set
      for (n=0; n<7; n++) {
        for (m=0; m<7; m++) {
          loc_x = i-3+m;
          loc_y = j-3+n;
          if (loc_x<0) {
            loc_x = 0;
          } else if (loc_x>=res_w) {
            loc_x = res_w-1;
          }
          if (loc_y<0) {
            loc_y = 0;
          } else if (loc_y>=res_h) {
            loc_y = res_h-1;
          }

          bayer_set[n*7+m] = bayer_src[loc_y*res_w+loc_x];
        }
      }
      // diff
      h_diff = abs(bayer_set[2*7+4]-bayer_set[2*7+2]) + abs(bayer_set[2*7+5]-bayer_set[2*7+3]) +
          abs(bayer_set[2*7+3]-bayer_set[2*7+1]) + abs(bayer_set[3*7+4]-bayer_set[3*7+2]) +
          abs(bayer_set[3*7+5]-bayer_set[3*7+3]) + abs(bayer_set[3*7+3]-bayer_set[3*7+1]) +
          abs(bayer_set[4*7+4]-bayer_set[4*7+2]) + abs(bayer_set[4*7+5]-bayer_set[4*7+3]) +
          abs(bayer_set[4*7+3]-bayer_set[4*7+1]);
      v_diff = abs(bayer_set[4*7+2]-bayer_set[2*7+2]) + abs(bayer_set[5*7+2]-bayer_set[3*7+2]) +
          abs(bayer_set[3*7+2]-bayer_set[1*7+2]) + abs(bayer_set[4*7+3]-bayer_set[2*7+3]) +
          abs(bayer_set[5*7+3]-bayer_set[3*7+3]) + abs(bayer_set[3*7+3]-bayer_set[1*7+3]) +
          abs(bayer_set[4*7+4]-bayer_set[2*7+4]) + abs(bayer_set[5*7+4]-bayer_set[3*7+4]) +
          abs(bayer_set[3*7+4]-bayer_set[1*7+4]);
      // h_diff = abs(bayer_set[1*7+5]-bayer_set[1*7+3]) + abs(bayer_set[1*7+1]-bayer_set[1*7+3]) +
      //          abs(bayer_set[2*7+5]-bayer_set[2*7+3]) + abs(bayer_set[2*7+1]-bayer_set[2*7+3]) +
      //          abs(bayer_set[3*7+5]-bayer_set[3*7+3]) + abs(bayer_set[3*7+1]-bayer_set[3*7+3]) +
      //          abs(bayer_set[4*7+5]-bayer_set[4*7+3]) + abs(bayer_set[4*7+1]-bayer_set[4*7+3]) +
      //          abs(bayer_set[5*7+5]-bayer_set[5*7+3]) + abs(bayer_set[5*7+1]-bayer_set[5*7+3]) +
      //          abs(bayer_set[1*7+4]-bayer_set[1*7+3]) + abs(bayer_set[1*7+2]-bayer_set[1*7+3]) +
      //          abs(bayer_set[2*7+4]-bayer_set[2*7+3]) + abs(bayer_set[2*7+2]-bayer_set[2*7+3]) +
      //          abs(bayer_set[3*7+4]-bayer_set[3*7+3]) + abs(bayer_set[3*7+2]-bayer_set[3*7+3]) +
      //          abs(bayer_set[4*7+4]-bayer_set[4*7+3]) + abs(bayer_set[4*7+2]-bayer_set[4*7+3]) +
      //          abs(bayer_set[5*7+4]-bayer_set[5*7+3]) + abs(bayer_set[5*7+2]-bayer_set[5*7+3]);

      // v_diff = abs(bayer_set[5*7+1]-bayer_set[3*7+1]) + abs(bayer_set[1*7+1]-bayer_set[3*7+1]) +
      //          abs(bayer_set[5*7+2]-bayer_set[3*7+2]) + abs(bayer_set[1*7+2]-bayer_set[3*7+2]) +
      //          abs(bayer_set[5*7+3]-bayer_set[3*7+3]) + abs(bayer_set[1*7+3]-bayer_set[3*7+3]) +
      //          abs(bayer_set[5*7+4]-bayer_set[3*7+4]) + abs(bayer_set[1*7+4]-bayer_set[3*7+4]) +
      //          abs(bayer_set[5*7+5]-bayer_set[3*7+5]) + abs(bayer_set[1*7+5]-bayer_set[3*7+5]) +
      //          abs(bayer_set[4*7+1]-bayer_set[3*7+1]) + abs(bayer_set[2*7+1]-bayer_set[3*7+1]) +
      //          abs(bayer_set[4*7+2]-bayer_set[3*7+2]) + abs(bayer_set[2*7+2]-bayer_set[3*7+2]) +
      //          abs(bayer_set[4*7+3]-bayer_set[3*7+3]) + abs(bayer_set[2*7+3]-bayer_set[3*7+3]) +
      //          abs(bayer_set[4*7+4]-bayer_set[3*7+4]) + abs(bayer_set[2*7+4]-bayer_set[3*7+4]) +
      //          abs(bayer_set[4*7+5]-bayer_set[3*7+5]) + abs(bayer_set[2*7+5]-bayer_set[3*7+5]);
      if (h_diff<v_diff) {
        calc_temp[0] = ((bayer_set[2*7+1]+bayer_set[2*7+2]+bayer_set[2*7+3])*2-bayer_set[2*7+0]-bayer_set[2*7+4])/4;
        calc_temp[1] = ((bayer_set[2*7+2]+bayer_set[2*7+3]+bayer_set[2*7+4])*2-bayer_set[2*7+1]-bayer_set[2*7+5])/4;
        calc_temp[2] = ((bayer_set[2*7+3]+bayer_set[2*7+4]+bayer_set[2*7+5])*2-bayer_set[2*7+2]-bayer_set[2*7+6])/4;
        calc_temp[3] = ((bayer_set[3*7+1]+bayer_set[3*7+2]+bayer_set[3*7+3])*2-bayer_set[3*7+0]-bayer_set[3*7+4])/4;
        calc_temp[4] = ((bayer_set[3*7+2]+bayer_set[3*7+3]+bayer_set[3*7+4])*2-bayer_set[3*7+1]-bayer_set[3*7+5])/4;
        calc_temp[5] = ((bayer_set[3*7+3]+bayer_set[3*7+4]+bayer_set[3*7+5])*2-bayer_set[3*7+2]-bayer_set[3*7+6])/4;
        calc_temp[6] = ((bayer_set[4*7+1]+bayer_set[4*7+2]+bayer_set[4*7+3])*2-bayer_set[4*7+0]-bayer_set[4*7+4])/4;
        calc_temp[7] = ((bayer_set[4*7+2]+bayer_set[4*7+3]+bayer_set[4*7+4])*2-bayer_set[4*7+1]-bayer_set[4*7+5])/4;
        calc_temp[8] = ((bayer_set[4*7+3]+bayer_set[4*7+4]+bayer_set[4*7+5])*2-bayer_set[4*7+2]-bayer_set[4*7+6])/4;
      } else {
        calc_temp[0] = ((bayer_set[1*7+2]+bayer_set[2*7+2]+bayer_set[3*7+2])*2-bayer_set[0*7+2]-bayer_set[4*7+2])/4;
        calc_temp[1] = ((bayer_set[1*7+3]+bayer_set[2*7+3]+bayer_set[3*7+3])*2-bayer_set[0*7+3]-bayer_set[4*7+3])/4;
        calc_temp[2] = ((bayer_set[1*7+4]+bayer_set[2*7+4]+bayer_set[3*7+4])*2-bayer_set[0*7+4]-bayer_set[4*7+4])/4;
        calc_temp[3] = ((bayer_set[2*7+2]+bayer_set[3*7+2]+bayer_set[4*7+2])*2-bayer_set[1*7+2]-bayer_set[5*7+2])/4;
        calc_temp[4] = ((bayer_set[2*7+3]+bayer_set[3*7+3]+bayer_set[4*7+3])*2-bayer_set[1*7+3]-bayer_set[5*7+3])/4;
        calc_temp[5] = ((bayer_set[2*7+4]+bayer_set[3*7+4]+bayer_set[4*7+4])*2-bayer_set[1*7+4]-bayer_set[5*7+4])/4;
        calc_temp[6] = ((bayer_set[3*7+2]+bayer_set[4*7+2]+bayer_set[5*7+2])*2-bayer_set[2*7+2]-bayer_set[6*7+2])/4;
        calc_temp[7] = ((bayer_set[3*7+3]+bayer_set[4*7+3]+bayer_set[5*7+3])*2-bayer_set[2*7+3]-bayer_set[6*7+3])/4;
        calc_temp[8] = ((bayer_set[3*7+4]+bayer_set[4*7+4]+bayer_set[5*7+4])*2-bayer_set[2*7+4]-bayer_set[6*7+4])/4;
      }
      calc_temp[9]   = bayer_set[3*7+3] + (bayer_set[3*7+4]+bayer_set[3*7+2]-calc_temp[5]-calc_temp[3])/2;
      calc_temp[10]  = bayer_set[3*7+3] + (bayer_set[4*7+3]+bayer_set[2*7+3]-calc_temp[7]-calc_temp[1])/2;
      calc_temp[11]  = calc_temp[4] + (bayer_set[2*7+2]+bayer_set[2*7+4]+bayer_set[4*7+2]+bayer_set[4*7+4]
          -calc_temp[0]-calc_temp[2]-calc_temp[6]-calc_temp[8])/4;
      if (j%2==0) {
        if (i%2==0) {
          pixel_temp_r   = calc_temp[9];
          pixel_temp_g   = bayer_set[3*7+3];
          pixel_temp_b   = calc_temp[10];
        } else {
          pixel_temp_r   = bayer_set[3*7+3];
          pixel_temp_g   = calc_temp[4];
          pixel_temp_b   = calc_temp[11];
        }
      } else {
        if (i%2==0) {
          pixel_temp_r   = calc_temp[11];
          pixel_temp_g   = calc_temp[4];
          pixel_temp_b   = bayer_set[3*7+3];
        } else {
          pixel_temp_r   = calc_temp[10];
          pixel_temp_g   = bayer_set[3*7+3];
          pixel_temp_b   = calc_temp[9];
        }
      }

      if (pixel_temp_r<0) {
        bayer_dst_r[(j)*res_w+i] = 0;
      } else if (pixel_temp_r>max_output_value) {
        bayer_dst_r[(j)*res_w+i] = max_output_value;
      } else {
        bayer_dst_r[(j)*res_w+i] = pixel_temp_r;
      }
      if (pixel_temp_g<0) {
        bayer_dst_g[(j)*res_w+i] = 0;
      } else if (pixel_temp_g>max_output_value) {
        bayer_dst_g[(j)*res_w+i] = max_output_value;
      } else {
        bayer_dst_g[(j)*res_w+i] = pixel_temp_g;
      }
      if (pixel_temp_b<0) {
        bayer_dst_b[(j)*res_w+i] = 0;
      } else if (pixel_temp_b>max_output_value) {
        bayer_dst_b[(j)*res_w+i] = max_output_value;
      } else {
        bayer_dst_b[(j)*res_w+i] = pixel_temp_b;
      }

    }
  }





}
// --}}}



int RawToRgb(unsigned char *psrc,
             unsigned int v_width,
             unsigned int v_height,
             unsigned char** pdst){
  //malloc pdst
  unsigned int size=v_width*v_height;
  unsigned int v_datalength=size*3*sizeof(unsigned char);
  *pdst=(unsigned char*)malloc(v_datalength);
  memset(*pdst,'\0',v_datalength);
  if(*pdst == NULL){
    return -1;
  }


  //in order to use bayer_cfa_7x7,transform psrc to unsigned short format
  unsigned short *pshortdata=(unsigned short*)malloc(size*sizeof (unsigned short));
  memset(pshortdata,'\0',size*sizeof (unsigned short));
  uint z;
  for( z=0;z<size;z++){
    pshortdata[z]=psrc[z];
  }

  //get Color component of r,g,b
  unsigned short *pshortdata_r=(unsigned short*)malloc(size*sizeof (unsigned short));
  memset(pshortdata_r,'\0',size*sizeof (unsigned short));
  unsigned short *pshortdata_g=(unsigned short*)malloc(size*sizeof (unsigned short));
  memset(pshortdata_g,'\0',size*sizeof (unsigned short));
  unsigned short *pshortdata_b=(unsigned short*)malloc(size*sizeof (unsigned short));
  memset(pshortdata_b,'\0',size*sizeof (unsigned short));
  bayer_cfa_7x7(pshortdata,v_width,v_height,pshortdata_r,pshortdata_g,pshortdata_b);
  for(z=0;z<size;z++){
    pshortdata_r[z]=pshortdata_r[z]<255?pshortdata_r[z]:255;
    pshortdata_g[z]=pshortdata_g[z]<255?pshortdata_g[z]:255;
    pshortdata_b[z]=pshortdata_b[z]<255?pshortdata_b[z]:255;
  }

  //用本地二进制文件中的数据填充各个通道
  //because different sequence of data between data from bus and image to display
  //we must change the sequence to normal
  //16 units as cycle，reverse the data in every cycles
  size_t i;
  int interval=16;
  for( i=0;i<size/16;i++ ){
    size_t j;
    for(j=0;j<16;j++){
      size_t count=i*16+j;
      size_t count_reverse=i*16+16-j-1;

      (*pdst)[3*count]=(unsigned char)pshortdata_r[count_reverse];
      (*pdst)[3*count+1]=(unsigned char)pshortdata_g[count_reverse];
      (*pdst)[3*count+2]=(unsigned char)pshortdata_b[count_reverse];

    }
  }

  free(pshortdata_r);
  pshortdata_r=NULL;
  free(pshortdata_g);
  pshortdata_g=NULL;
  free(pshortdata_b);
  pshortdata_b=NULL;
  free(pshortdata);
  pshortdata=NULL;

  return 0;
}



int getimage(const char* path_input,
             unsigned int v_width,
             unsigned int v_height,
             const char* path_output){


  unsigned int size=v_width*v_height;
  //需要的图片大小
  unsigned int v_datalength=size*3*sizeof(unsigned char);

  //读取本地二进制文件
  FILE *fp=fopen(path_input,"r");
  if(fp == NULL){
    printf(">>Error: %s %s\n", "fail to open",path_input);
    return -1;
  }

  unsigned char *preaddata=NULL;
  unsigned char *pdata=NULL;
  preaddata=(unsigned char*)malloc(size*sizeof (unsigned char));
  if(preaddata == NULL){
    return -1;
  }
  memset(preaddata,'\0',size*sizeof (unsigned char));
  size_t size_read=fread(preaddata,sizeof(unsigned char),size,fp);
  if(size_read<=0){
    return -1;
  }

  if(RawToRgb(preaddata,v_width,v_height,&pdata)==0){
    printf("%s\n", "succeed togetSingleChannelData");
    GBytes * gbyte3=g_bytes_new(pdata,v_datalength);
    GdkPixbuf* src_frombuffer = gdk_pixbuf_new_from_bytes(gbyte3,0,FALSE,8,v_width,v_height,v_width*3);
    gboolean ret= gdk_pixbuf_save(src_frombuffer,
                                  path_output,
                                  "jpeg", NULL, "quality", "100", NULL);

    if(ret == TRUE){
      return 0;
    }
    else{
      return -1;
    }
  }
  else{
    printf("%s\n","fail to transfer" );
    return -1;
  }

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
  *ppdata=mmap(NULL,sizeof(unsigned char )*v_size,
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

int getSingleChannelData(
    unsigned char *psrc,
    unsigned int v_width,
    unsigned int v_height,
    unsigned char** pdst){
  //
  unsigned int size=v_width*v_height;
  unsigned int v_datalength=size*3*sizeof(unsigned char);
  *pdst=(unsigned char*)malloc(v_datalength);
  printf("%s\n","getSingleChannelData:malloc" );
  outputTimeCost();

  memset(*pdst,'\0',v_datalength);

  printf("%s\n","getSingleChannelData:memset" );
  outputTimeCost();

  if(*pdst == NULL){
    return -1;
  }

#define SIZE_BLOCK 1024
  unsigned int size_block=SIZE_BLOCK;
  printf("%s\n","getSingleChannelData:memcpy_block" );
  outputTimeCost();


  //用本地二进制文件中的数据填充各个通道
  size_t i;
  unsigned int tmp=size/16;
  for( i=0;i<tmp;i++ ){
    size_t j;
    size_t tmp_i=i<<4;
    size_t tmp_num=tmp_i+15;

    for(j=0;j<16;j++){
      size_t count=tmp_i+j;
      size_t count_reverse=tmp_num-j;
      (*pdst)[3*count]=psrc[count_reverse];
      // (*pdst)[3*count+1]=psrc[count_reverse];
      // (*pdst)[3*count+2]=psrc[count_reverse];
    }
  }

  printf("%s\n","getSingleChannelData:copy" );
  outputTimeCost();
  return 0;
}


int printHelp(){
  printf("please input params as below:\n" );
  printf("./showImageInMem  [addr] [height] [width] [interval] [screen_width*screen_height]\n" );
  printf("interval  get image per interval ms  \n" );
  printf("note:     please run as root  \n" );
  printf("e.g.:     ./showImageInMem 0x60000000 4096 4096 100 1024*1024\n" );
  return 0;
}
