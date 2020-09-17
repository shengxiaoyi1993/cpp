#include <gtk/gtk.h>
#include <stdio.h>
#include <stdio.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <errno.h>
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>


using namespace std;





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




int main(int argc, char *argv[])  {
  gtk_init(&argc,&argv);

  GdkScreen *screen = gdk_screen_get_default();
  int width = gdk_screen_get_width(screen), height = gdk_screen_get_height(screen);

  GdkWindow *root;
  GdkPixbuf *new_pixbuf;

  root = gdk_get_default_root_window ();
  new_pixbuf = gdk_pixbuf_get_from_drawable (NULL, root, NULL,
                                             0, 0, 0, 0, width, height);
  gdk_pixbuf_save(new_pixbuf, "screenshot.jpg", "jpeg", NULL, NULL);

  return 0;

}
