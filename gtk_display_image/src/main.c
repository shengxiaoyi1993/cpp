 #include   <gtk/gtk.h>
 #include  <stdio.h>
 #include <stdio.h>
 #include <sys/mman.h>
 #include <fcntl.h>
 #include <errno.h>

static GtkWidget *image_global=NULL;


static int readBuferInRam(
								unsigned int v_addr,
								unsigned int v_size,
								unsigned char** ppdata){
								int fd;
								*ppdata=(char *)malloc(v_size*sizeof(unsigned char));
								memset(*ppdata,'\0',v_size*sizeof(unsigned char));
								fd = open("/dev/mem",O_RDWR);
								if(fd< 0)
								{
																printf("open /dev/mem failed.\n");
																return 0;
								}

								ssize_t size=read(fd,*ppdata,v_size);
								close(fd);
							  return size;
}


gboolean key_press (GtkWidget *widget)
{

  int width=512;
  int height=512;


    static int i=0;
    if(NULL != widget){
        // gint v_datalength=1024*3*sizeof(char);
        // char *pdata=(char*)malloc(v_datalength);
        // memset(pdata,i,v_datalength);


         char *pdata=NULL;
        int size= readBuferInRam(0,width*height*3,&pdata);
        printf("key_press size:%d\n",size);
        fflush(stdout);
        if(pdata == NULL){
          printf("FAIL TO  GET ARM\n");
          fflush(stdout);
        }

        GBytes * gbyte3=g_bytes_new(pdata,width*height*3);
        GdkPixbuf* src_frombuffer = gdk_pixbuf_new_from_bytes(gbyte3,0,FALSE,8,width,height,width*3);
//        image_global = gtk_image_new_from_pixbuf(src_frombuffer);	// 通过pixbuf创建图片控件
        gtk_image_set_from_pixbuf(widget,src_frombuffer);
        g_object_unref(src_frombuffer);	// pixbuf使用完，需要人为释放资源
        i+=50;
        if(i>=256){
            i=0;
        }
        printf("key_press func:%d\n",i);
        fflush(stdout);

    }
    else{
        printf("key_press func null:%d\n",i);
        fflush(stdout);

    }


    return TRUE;
}


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


 int main(int argc, char *argv[])  {

     GtkWidget *windows;
     //    GtkWidget *image;
     gtk_init(&argc,&argv);

     windows = gtk_window_new(GTK_WINDOW_TOPLEVEL);

     gtk_widget_show(windows);

     const char* im_pth = "/home/sxy/Pictures/test.bmp";
     //    image = gtk_image_new_from_file (im_pth);





     //    // 下面借助GdkPixbuf来修改图片的大小，注意接口以gdk_开头，不属于控件类
     //    // 创建pixbuf，需要占用资源，使用完，需要人为释放
     //    GdkPixbuf *src = gdk_pixbuf_new_from_file(im_pth, NULL);// 读取原图片
     //    GdkPixbuf *dst = gdk_pixbuf_scale_simple(src,
     //                                             100, 100, GDK_INTERP_BILINEAR);	// 修改图片大小(100, 100), 保存在dst


     //    GtkWidget *image_two = gtk_image_new_from_pixbuf(dst);	// 通过pixbuf创建图片控件

     //    GBytes *byte=gdk_pixbuf_read_pixel_bytes(src);
     //    //point to the data
     //    gconstpointer v_gp;
     //    //get the buffer size
     //    gsize v_gs;
     //    v_gp = g_bytes_get_data ( byte,&v_gs);
     //    printf("v_gs:%u\n",v_gs);

     //    //只有一种：GDK_COLORSPACE_RGB
     //    GdkColorspace v_gcs=gdk_pixbuf_get_colorspace(src);
     //    printf("v_gcs:%d\n",v_gcs);
     //    //3通道
     //    int v_gch=gdk_pixbuf_get_n_channels(src);
     //    printf("v_gch:%d\n",v_gch);
     //    //8
     //    int v_gbite=gdk_pixbuf_get_bits_per_sample(src);
     //    printf("v_gbite:%d\n",v_gbite);
     ////    guchar* v_gpix=gdk_pixbuf_get_pixels(src);
     ////    printf("v_gbite:%s\n",v_gpix);

     //    gsize v_gbytelength=gdk_pixbuf_get_byte_length(src);
     //    printf("v_gbytelength:%u\n",v_gbytelength);

     //    int v_growstride=gdk_pixbuf_get_rowstride(src);
     //    printf("v_growstride:%d\n",v_growstride);

     //    fflush(stdout);

     //    g_object_unref(src);	// pixbuf使用完，需要人为释放资源
     //    g_object_unref(dst);



     gint v_datalength=1024*3*sizeof(char);
     char *pdata=(char*)malloc(v_datalength);
     memset(pdata,255,v_datalength);
     GBytes * gbyte3=g_bytes_new(pdata,v_datalength);
     GdkPixbuf* src_frombuffer = gdk_pixbuf_new_from_bytes(gbyte3,0,FALSE,8,32,32,96);
     image_global = gtk_image_new_from_pixbuf(src_frombuffer);	// 通过pixbuf创建图片控件
     g_object_unref(src_frombuffer);	// pixbuf使用完，需要人为释放资源


//     gtk_signal_connect (GTK_OBJECT (windows), "enter_notify_event",
//                         GTK_SIGNAL_FUNC (key_press), NULL);
     gtk_signal_connect (GTK_OBJECT (windows), "delete_event",
                         GTK_SIGNAL_FUNC (CloseAppWindow), NULL);
     g_timeout_add(1000, (GSourceFunc)key_press,(gpointer)image_global);

     gtk_container_add (GTK_CONTAINER (windows), GTK_WIDGET (image_global));
     gtk_widget_show_all (GTK_WIDGET (windows));
     gtk_main();



     return 0;


 }
