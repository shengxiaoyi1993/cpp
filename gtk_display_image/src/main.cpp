#include   <gtk/gtk.h>
#include  <stdio.h>
#include <stdio.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <errno.h>
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>


using namespace std;






static GtkWidget *image_global=NULL;
GdkPixbuf* g_frame;



gboolean key_press (GtkWidget *widget);


/*
 * CloseAppWindow
 *
 * The window is closing down, end the gtk loop
*/
gint CloseAppWindow (GtkWidget *widget, gpointer data)
{
  gtk_main_quit ();

  return (FALSE);
}



//组合row数据
//1. 用函数计算出各个通道的像素
//2. 填充目标图片中的像素通道

//问题
//1. 函数使用方法
//   函数各个参数的含义，数据需要满足的格式


//测试：gtk支持的图片的透明通道的位置和size
//1. 导入一个图片buffer文件
//2. 插入透明通道的数据
//3. 设置图片参数，显示图片

// GdkScreen *screen = gdk_screen_get_default();
// GdkWindow *window = gdk_get_default_root_window();
// int width = gdk_screen_get_width(screen), height = gdk_screen_get_height(screen);
//
// GdkPixbuf *buf = gdk_pixbuf_get_from_window(window, 0, 0, width, height);
//
// gdk_pixbuf_save(buf, name, "jpeg", NULL, NULL);



int main(int argc, char *argv[])  {
  GtkWidget *windows;
  gtk_init(&argc,&argv);
  windows = gtk_window_new(GTK_WINDOW_TOPLEVEL);
  //    gtk_window_set_screen (GTK_WINDOW (windows),
  //                           gtk_widget_get_screen (do_widget));
  //    gtk_widget_show(windows);
  gint v_datalength=1024*3*sizeof(char);
  char *pdata=(char*)malloc(v_datalength);
  memset(pdata,255,v_datalength);
  GBytes * gbyte3=g_bytes_new(pdata,v_datalength);
  g_frame = gdk_pixbuf_new_from_bytes(
        gbyte3,GDK_COLORSPACE_RGB,FALSE,8,32,32,32*3);
  //    image_global = gtk_drawing_area_new ();
  image_global = gtk_image_new_from_pixbuf(g_frame);	// 通过pixbuf创建图片控件
  //    g_object_unref(g_frame);	// pixbuf使用完，需要人为释放资源
  gtk_widget_set_size_request (windows, 1024, 1024);

  //     gtk_signal_connect (GTK_OBJECT (windows), "enter_notify_event",
  //                         GTK_SIGNAL_FUNC (key_press), NULL);
  gtk_signal_connect (GTK_OBJECT (windows), "delete_event",
                      GTK_SIGNAL_FUNC (CloseAppWindow), NULL);
  g_timeout_add(1000, (GSourceFunc)key_press,image_global);
  gtk_container_add (GTK_CONTAINER (windows),  image_global);
  // g_signal_connect (windows, "expose-event",
  //                   G_CALLBACK (expose_cb), NULL);
  gtk_widget_show_all(GTK_WIDGET (windows));
  gtk_main();

  return 0;

}


gboolean key_press (GtkWidget *widget)
{

  //  int width=512;
  //  int height=512;

  string path_imagebuffer="/home/sxy/Share/tftp/imagerecord_0_1.txt";
  uint width_imagebuffer=1024;
  uint height_imagebuffer=1024;
  uint g_width=width_imagebuffer;
  uint g_height=height_imagebuffer;
  uint g_channels=4;

  ifstream infile(path_imagebuffer,ios::in);   //输入流
  if(!infile.is_open()){
    cout<<"open failed"<<endl;
    return -1;
  }


  //  std::string data_src((std::istreambuf_iterator<char>(infile)),
  //                       std::istreambuf_iterator<char>());
  //  cout<<"size:"<<data_src.size()<<endl;

  //读取文件中的数据


  static int i=0;
  if(NULL != widget){
    cout<<"i :"<<i<<endl;

    gint v_datalength=width_imagebuffer*height_imagebuffer*g_channels*sizeof(char);
    unsigned char *pdata=(unsigned char*)malloc(v_datalength);
    //    memset(pdata,0,v_datalength);


    for (uint m=0;m<v_datalength/4;m++) {
//      pdata[m*4+0]=m;
      pdata[m*4+3]=0;
    }
    //    memcpy(pdata,data_src.c_str(),v_datalength);

    if(pdata == NULL){
      printf("FAIL TO  GET ARM\n");
      fflush(stdout);
    }

    GdkPixbuf* g_frame = nullptr;


    //    g_frame = gdk_pixbuf_new_from_data((const unsigned char*)data_src.c_str(),GDK_COLORSPACE_RGB,FALSE,8,
    //                                       g_width,g_height,g_width*3,nullptr,nullptr);
    g_frame = gdk_pixbuf_new_from_data(pdata,GDK_COLORSPACE_RGB,TRUE,8,
                                       1024,1024,1024*g_channels,nullptr,nullptr);
    if(g_frame ==NULL){
      printf("g_frame ==NULL\n");

    }

    gtk_image_set_from_pixbuf(GTK_IMAGE(widget),g_frame);
    g_object_unref(g_frame);	// pixbuf使用完，需要人为释放资源
    //    free(pdata);
    //    pdata=nullptr;

  }

  i+=10;
  if(i>=255){
    i=0;
  }

  return TRUE;
}
