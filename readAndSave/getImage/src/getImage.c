#include   <gtk/gtk.h>
#include  <stdio.h>
#include <stdio.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <errno.h>

//描述该程序的若干选择
int printHelp();
//将row数据转换成三个通道的数据
void bayer_cfa_7x7(unsigned short *bayer_src, unsigned short res_w, unsigned short res_h,
     unsigned short *bayer_dst_r, unsigned short *bayer_dst_g, unsigned short *bayer_dst_b);
//将row数据保存为图片文件
int getimage(const char* path_input,
       unsigned int v_width,
       unsigned int v_height,
     const char* path_output);




int main(int argc, char *argv[])  {
  if(argc!= 5){
    printf("\n>>Error:param not match\n\n");
    printHelp();
    return -1;
  }

  unsigned int v_width;
  unsigned int v_height;

  const char* path_input=argv[1];
  sscanf(argv[2],"%u",&v_width);
  sscanf(argv[3],"%u",&v_height);
  const char* path_output=argv[4];

  #ifdef DEBUG
  printf("path_input:   %s\n", path_input);
  printf("v_width:      %u\n", v_width);
  printf("v_height:     %u\n", v_height);
  printf("path_output:  %s\n", path_output);
  #endif

  int ret = getimage(path_input,v_width,v_height,path_output);
  if(ret == 0){
    printf("%s %s\n", "succeed to getimage:",path_output);
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
    unsigned int size=v_width*v_height;
    unsigned int v_datalength=size*3*sizeof(unsigned char);
    *pdst=(unsigned char*)malloc(v_datalength);
    memset(*pdst,'\0',v_datalength);
    if(*pdst == NULL){
      return -1;
    }


      //将数据转换成unsigned short
      unsigned short *pshortdata=(unsigned short*)malloc(size*sizeof (unsigned short));
      memset(pshortdata,'\0',size*sizeof (unsigned short));
      uint z;
      for( z=0;z<size;z++){
          pshortdata[z]=psrc[z];
      }

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

int printHelp(){
  printf("please input params as below:\n" );
  printf("./readmem  [inputfile] [height] [width] [outputfile]\n" );
  printf("inputfile: inputfile of raw data  \n" );
  printf("e.g.:      ./getimage ~/Share/tftp/imagebuffer.txt 4096 4096 devimage.jpg\n" );
  return 0;
}
