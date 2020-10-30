#include "bayer_convert.h"
#include "math.h"
#include "string.h"
#include <stdio.h>
#include <stdlib.h>



void bayer_cfa_5x5(unsigned short *bayer_src, unsigned short res_w, unsigned short res_h,
      unsigned short *bayer_dst_r, unsigned short *bayer_dst_g, unsigned short *bayer_dst_b) {
//{{{
   int   i, j, l, k;
   unsigned short bayer_set_pixel[6*6];
   unsigned short bayer_src_ext[(res_w+4)*(res_h+4)];
   int   h_diff[4*2], v_diff[4*2], h_sum[4], v_sum[4], x_sum[4];
   int   total_h_diff[4], total_v_diff[4];
   int   pix_0_b_h, pix_0_b_v, pix_0_r_h, pix_0_r_v;
   int   pix_1_g_h, pix_1_g_v, pix_1_b_h, pix_1_b_v;
   int   pix_2_g_h, pix_2_g_v, pix_2_r_h, pix_2_r_v;
   int   pix_3_b_h, pix_3_b_v, pix_3_r_h, pix_3_r_v;

   unsigned short max_output_value = 4095;

   // extend bayer
   for (j=0; j<res_h+4; j++) {
      for (i=0; i<res_w+4; i++) {
         if (j<2) {
            if (i<2) {
               bayer_src_ext[j*(res_w+4)+i] = bayer_src[j*res_w+i];
            } else if (i<res_w+2) {
               bayer_src_ext[j*(res_w+4)+i] = bayer_src[j*res_w+i-2];
            } else {
               bayer_src_ext[j*(res_w+4)+i] = bayer_src[j*res_w+i-4];
            }
         } else if (j<res_h+2) {
            if (i<2) {
               bayer_src_ext[j*(res_w+4)+i] = bayer_src[(j-2)*res_w+i];
            } else if (i<res_w+2) {
               bayer_src_ext[j*(res_w+4)+i] = bayer_src[(j-2)*res_w+i-2];
            } else {
               bayer_src_ext[j*(res_w+4)+i] = bayer_src[(j-2)*res_w+i-4];
            }
         } else {
            if (i<2) {
               bayer_src_ext[j*(res_w+4)+i] = bayer_src[(j-4)*res_w+i];
            } else if (i<res_w+2) {
               bayer_src_ext[j*(res_w+4)+i] = bayer_src[(j-4)*res_w+i-2];
            } else {
               bayer_src_ext[j*(res_w+4)+i] = bayer_src[(j-4)*res_w+i-4];
            }
         }
      }
   }

   // process 2x2
   for (j=0; j<res_h/2; j++) {
      for (i=0; i<res_w/2; i++) {
         // extract 6x6 pixel for process
         for (l=0; l<6; l++) {
            for (k=0; k<6; k++) {
               bayer_set_pixel[l*6+k]  = bayer_src_ext[(j*2+l)*(res_w+4)+(i*2+k)];
            }
         }
         // calc temp result, h_diff and v_diff, even means left, odd means right
         h_diff[0*2+0] = bayer_set_pixel[2*6+2] - bayer_set_pixel[2*6+0];
         h_diff[0*2+1] = bayer_set_pixel[2*6+2] - bayer_set_pixel[2*6+4];
         h_diff[1*2+0] = bayer_set_pixel[2*6+3] - bayer_set_pixel[2*6+1];
         h_diff[1*2+1] = bayer_set_pixel[2*6+3] - bayer_set_pixel[2*6+5];
         h_diff[2*2+0] = bayer_set_pixel[3*6+2] - bayer_set_pixel[3*6+0];
         h_diff[2*2+1] = bayer_set_pixel[3*6+2] - bayer_set_pixel[3*6+4];
         h_diff[3*2+0] = bayer_set_pixel[3*6+3] - bayer_set_pixel[3*6+1];
         h_diff[3*2+1] = bayer_set_pixel[3*6+3] - bayer_set_pixel[3*6+5];
         v_diff[0*2+0] = bayer_set_pixel[2*6+2] - bayer_set_pixel[0*6+2];
         v_diff[0*2+1] = bayer_set_pixel[2*6+2] - bayer_set_pixel[4*6+2];
         v_diff[1*2+0] = bayer_set_pixel[2*6+3] - bayer_set_pixel[0*6+3];
         v_diff[1*2+1] = bayer_set_pixel[2*6+3] - bayer_set_pixel[4*6+3];
         v_diff[2*2+0] = bayer_set_pixel[3*6+2] - bayer_set_pixel[1*6+2];
         v_diff[2*2+1] = bayer_set_pixel[3*6+2] - bayer_set_pixel[5*6+2];
         v_diff[3*2+0] = bayer_set_pixel[3*6+3] - bayer_set_pixel[1*6+3];
         v_diff[3*2+1] = bayer_set_pixel[3*6+3] - bayer_set_pixel[5*6+3];

         h_sum[0] = bayer_set_pixel[2*6+1] + bayer_set_pixel[2*6+3];
         h_sum[1] = bayer_set_pixel[2*6+2] + bayer_set_pixel[2*6+4];
         h_sum[2] = bayer_set_pixel[3*6+1] + bayer_set_pixel[3*6+3];
         h_sum[3] = bayer_set_pixel[3*6+2] + bayer_set_pixel[3*6+4];
         v_sum[0] = bayer_set_pixel[1*6+2] + bayer_set_pixel[3*6+2];
         v_sum[1] = bayer_set_pixel[1*6+3] + bayer_set_pixel[3*6+3];
         v_sum[2] = bayer_set_pixel[2*6+2] + bayer_set_pixel[4*6+2];
         v_sum[3] = bayer_set_pixel[2*6+3] + bayer_set_pixel[4*6+3];

         x_sum[0] = bayer_set_pixel[1*6+1] + bayer_set_pixel[1*6+3] +
                    bayer_set_pixel[3*6+1] + bayer_set_pixel[3*6+3];
         x_sum[1] = bayer_set_pixel[1*6+2] + bayer_set_pixel[1*6+4] +
                    bayer_set_pixel[3*6+2] + bayer_set_pixel[3*6+4];
         x_sum[2] = bayer_set_pixel[2*6+1] + bayer_set_pixel[2*6+3] +
                    bayer_set_pixel[4*6+1] + bayer_set_pixel[4*6+3];
         x_sum[3] = bayer_set_pixel[2*6+2] + bayer_set_pixel[2*6+4] +
                    bayer_set_pixel[4*6+2] + bayer_set_pixel[4*6+4];

         total_h_diff[0] = abs(h_diff[0*2+0]) + abs(h_diff[0*2+1]) + abs(h_diff[1*2+0]);
         total_h_diff[1] = abs(h_diff[1*2+0]) + abs(h_diff[1*2+1]) + abs(h_diff[0*2+1]);
         total_h_diff[2] = abs(h_diff[2*2+0]) + abs(h_diff[2*2+1]) + abs(h_diff[3*2+0]);
         total_h_diff[3] = abs(h_diff[3*2+0]) + abs(h_diff[3*2+1]) + abs(h_diff[2*2+1]);
         total_v_diff[0] = abs(v_diff[0*2+0]) + abs(v_diff[0*2+1]) + abs(v_diff[1*2+0]);
         total_v_diff[1] = abs(v_diff[1*2+0]) + abs(v_diff[1*2+1]) + abs(v_diff[0*2+1]);
         total_v_diff[2] = abs(v_diff[2*2+0]) + abs(v_diff[2*2+1]) + abs(v_diff[3*2+0]);
         total_v_diff[3] = abs(v_diff[3*2+0]) + abs(v_diff[3*2+1]) + abs(v_diff[2*2+1]);

         pix_0_b_h = (v_sum[0]*2 + bayer_set_pixel[2*6+2]*4 - x_sum[0])/4;
         pix_0_b_v = (v_sum[0] + v_diff[0*2+0] + v_diff[0*2+1])/2;
         pix_0_r_h = (h_sum[0] + h_diff[0*2+0] + h_diff[0*2+1])/2;
         pix_0_r_v = (h_sum[0]*2 + bayer_set_pixel[2*6+2]*4 - x_sum[0])/4;

         pix_1_g_h = (h_sum[1] + h_diff[1*2+0] + h_diff[1*2+1])/2;
         pix_1_g_v = (v_sum[1] + v_diff[1*2+0] + v_diff[1*2+1])/2;
         pix_1_b_h = (x_sum[1] + h_sum[1]*2 - v_sum[1]*2)/4;
         pix_1_b_v = (x_sum[1] + v_sum[1]*2 - h_sum[1]*2)/4;

         pix_2_g_h = (h_sum[2] + h_diff[2*2+0] + h_diff[2*2+1])/2;
         pix_2_g_v = (v_sum[2] + v_diff[2*2+0] + v_diff[2*2+1])/2;
         pix_2_r_h = (x_sum[2] + h_sum[2]*2 - v_sum[2]*2)/4;
         pix_2_r_v = (x_sum[2] + v_sum[2]*2 - h_sum[2]*2)/4;

         pix_3_b_h = (h_sum[3] + h_diff[3*2+0] + h_diff[3*2+1])/2;
         pix_3_b_v = (h_sum[3]*2 + bayer_set_pixel[3*6+3]*4 - x_sum[3])/4;
         pix_3_r_h = (v_sum[3]*2 + bayer_set_pixel[3*6+3]*4 - x_sum[3])/4;
         pix_3_r_v = (v_sum[3] + v_diff[3*2+0] + v_diff[3*2+1])/2;

         // output pixel loc 0
         bayer_dst_g[j*2*res_w+i*2] = bayer_set_pixel[2*6+2];
         if (total_h_diff[0] <= total_v_diff[0]) {
            if (pix_0_r_h < 0) {
               bayer_dst_r[j*2*res_w+i*2] = 0;
            } else if (pix_0_r_h > max_output_value) {
               bayer_dst_r[j*2*res_w+i*2] = max_output_value;
            } else {
               bayer_dst_r[j*2*res_w+i*2] = pix_0_r_h;
            }
            if (pix_0_b_h < 0) {
               bayer_dst_b[j*2*res_w+i*2] = 0;
            } else if (pix_0_b_h > max_output_value) {
               bayer_dst_b[j*2*res_w+i*2] = max_output_value;
            } else {
               bayer_dst_b[j*2*res_w+i*2] = pix_0_b_h;
            }
         } else {
            if (pix_0_r_v < 0) {
               bayer_dst_r[j*2*res_w+i*2] = 0;
            } else if (pix_0_r_v > max_output_value) {
               bayer_dst_r[j*2*res_w+i*2] = max_output_value;
            } else {
               bayer_dst_r[j*2*res_w+i*2] = pix_0_r_v;
            }
            if (pix_0_b_v < 0) {
               bayer_dst_b[j*2*res_w+i*2] = 0;
            } else if (pix_0_b_v > max_output_value) {
               bayer_dst_b[j*2*res_w+i*2] = max_output_value;
            } else {
               bayer_dst_b[j*2*res_w+i*2] = pix_0_b_v;
            }
         }
         // output pixel loc 1
         bayer_dst_r[j*2*res_w+i*2+1] = bayer_set_pixel[2*6+3];
         if (total_h_diff[1] <= total_v_diff[1]) {
            if (pix_1_g_h < 0) {
               bayer_dst_g[j*2*res_w+i*2+1] = 0;
            } else if (pix_1_g_h > max_output_value) {
               bayer_dst_g[j*2*res_w+i*2+1] = max_output_value;
            } else {
               bayer_dst_g[j*2*res_w+i*2+1] = pix_1_g_h;
            }
            if (pix_1_b_h < 0) {
               bayer_dst_b[j*2*res_w+i*2+1] = 0;
            } else if (pix_1_b_h > max_output_value) {
               bayer_dst_b[j*2*res_w+i*2+1] = max_output_value;
            } else {
               bayer_dst_b[j*2*res_w+i*2+1] = pix_1_b_h;
            }
         } else {
            if (pix_1_g_v < 0) {
               bayer_dst_g[j*2*res_w+i*2+1] = 0;
            } else if (pix_1_g_v > max_output_value) {
               bayer_dst_g[j*2*res_w+i*2+1] = max_output_value;
            } else {
               bayer_dst_g[j*2*res_w+i*2+1] = pix_1_g_v;
            }
            if (pix_1_b_v < 0) {
               bayer_dst_b[j*2*res_w+i*2+1] = 0;
            } else if (pix_1_b_v > max_output_value) {
               bayer_dst_b[j*2*res_w+i*2+1] = max_output_value;
            } else {
               bayer_dst_b[j*2*res_w+i*2+1] = pix_1_b_v;
            }
         }
         // output pixel loc 2
         bayer_dst_b[(j*2+1)*res_w+i*2] = bayer_set_pixel[3*6+2];
         if (total_h_diff[2] <= total_v_diff[2]) {
            if (pix_2_g_h < 0) {
               bayer_dst_g[(j*2+1)*res_w+i*2] = 0;
            } else if (pix_2_g_h > max_output_value) {
               bayer_dst_g[(j*2+1)*res_w+i*2] = max_output_value;
            } else {
               bayer_dst_g[(j*2+1)*res_w+i*2] = pix_2_g_h;
            }
            if (pix_2_r_h < 0) {
               bayer_dst_r[(j*2+1)*res_w+i*2] = 0;
            } else if (pix_2_r_h > max_output_value) {
               bayer_dst_r[(j*2+1)*res_w+i*2] = max_output_value;
            } else {
               bayer_dst_r[(j*2+1)*res_w+i*2] = pix_2_r_h;
            }
         } else {
            if (pix_2_g_v < 0) {
               bayer_dst_g[(j*2+1)*res_w+i*2] = 0;
            } else if (pix_2_g_v > max_output_value) {
               bayer_dst_g[(j*2+1)*res_w+i*2] = max_output_value;
            } else {
               bayer_dst_g[(j*2+1)*res_w+i*2] = pix_2_g_v;
            }
            if (pix_2_r_v < 0) {
               bayer_dst_r[(j*2+1)*res_w+i*2] = 0;
            } else if (pix_2_r_v > max_output_value) {
               bayer_dst_r[(j*2+1)*res_w+i*2] = max_output_value;
            } else {
               bayer_dst_r[(j*2+1)*res_w+i*2] = pix_2_r_v;
            }
         }
         // output pixel loc 3
         bayer_dst_g[(j*2+1)*res_w+i*2+1] = bayer_set_pixel[3*6+3];
         if (total_h_diff[3] <= total_v_diff[3]) {
            if (pix_3_r_h < 0) {
               bayer_dst_r[(j*2+1)*res_w+i*2+1] = 0;
            } else if (pix_3_r_h > max_output_value) {
               bayer_dst_r[(j*2+1)*res_w+i*2+1] = max_output_value;
            } else {
               bayer_dst_r[(j*2+1)*res_w+i*2+1] = pix_3_r_h;
            }
            if (pix_3_b_h < 0) {
               bayer_dst_b[(j*2+1)*res_w+i*2+1] = 0;
            } else if (pix_3_b_h > max_output_value) {
               bayer_dst_b[(j*2+1)*res_w+i*2+1] = max_output_value;
            } else {
               bayer_dst_b[(j*2+1)*res_w+i*2+1] = pix_3_b_h;
            }
         } else {
            if (pix_3_r_v < 0) {
               bayer_dst_r[(j*2+1)*res_w+i*2+1] = 0;
            } else if (pix_3_r_v > max_output_value) {
               bayer_dst_r[(j*2+1)*res_w+i*2+1] = max_output_value;
            } else {
               bayer_dst_r[(j*2+1)*res_w+i*2+1] = pix_3_r_v;
            }
            if (pix_3_b_v < 0) {
               bayer_dst_b[(j*2+1)*res_w+i*2+1] = 0;
            } else if (pix_3_b_v > max_output_value) {
               bayer_dst_b[(j*2+1)*res_w+i*2+1] = max_output_value;
            } else {
               bayer_dst_b[(j*2+1)*res_w+i*2+1] = pix_3_b_v;
            }
         }

      }
   }


}
//}}}

void bayer_cfa_5x5_fine(unsigned short *bayer_src, unsigned short res_w, unsigned short res_h,
      unsigned short *bayer_dst_r, unsigned short *bayer_dst_g, unsigned short *bayer_dst_b) {
//{{{
   int   i, j, l, k, m, n;
   unsigned short bayer_set[5*5];
   unsigned short bayer_src_ext[(res_w+4)*(res_h+4)];
   int   calc_temp[24];
   int   h_diff, v_diff, nw_diff, sw_diff;
   int   pixel_temp_r, pixel_temp_g, pixel_temp_b;

   unsigned short max_output_value = 4095;

   // extend bayer
   for (j=0; j<res_h+4; j++) {
      for (i=0; i<res_w+4; i++) {
         if (j<2) {
            if (i<2) {
               bayer_src_ext[j*(res_w+4)+i] = bayer_src[j*res_w+i];
            } else if (i<res_w+2) {
               bayer_src_ext[j*(res_w+4)+i] = bayer_src[j*res_w+i-2];
            } else {
               bayer_src_ext[j*(res_w+4)+i] = bayer_src[j*res_w+i-4];
            }
         } else if (j<res_h+2) {
            if (i<2) {
               bayer_src_ext[j*(res_w+4)+i] = bayer_src[(j-2)*res_w+i];
            } else if (i<res_w+2) {
               bayer_src_ext[j*(res_w+4)+i] = bayer_src[(j-2)*res_w+i-2];
            } else {
               bayer_src_ext[j*(res_w+4)+i] = bayer_src[(j-2)*res_w+i-4];
            }
         } else {
            if (i<2) {
               bayer_src_ext[j*(res_w+4)+i] = bayer_src[(j-4)*res_w+i];
            } else if (i<res_w+2) {
               bayer_src_ext[j*(res_w+4)+i] = bayer_src[(j-4)*res_w+i-2];
            } else {
               bayer_src_ext[j*(res_w+4)+i] = bayer_src[(j-4)*res_w+i-4];
            }
         }
      }
   }

   // process 2x2
   for (j=0; j<res_h/2; j++) {
      for (i=0; i<res_w/2; i++) {
         // extract 5x5
         for (l=0; l<2; l++) {
            for (k=0; k<2; k++) {
               for (n=0; n<5; n++) {
                  for (m=0; m<5; m++) {
                     bayer_set[n*5+m] = bayer_src_ext[(j*2+l+n)*(res_w+4)+(i*2+k+m)];
                  }
               }

               h_diff = abs(bayer_set[2*5+0] - bayer_set[2*5+2]) + abs(bayer_set[2*5+1] - bayer_set[2*5+3]) +
                     abs(bayer_set[2*5+2] - bayer_set[2*5+4]);
               v_diff = abs(bayer_set[0*5+2] - bayer_set[2*5+2]) + abs(bayer_set[1*5+2] - bayer_set[3*5+2]) +
                     abs(bayer_set[2*5+2] - bayer_set[4*5+2]);
               nw_diff = abs(bayer_set[0*5+0] - bayer_set[2*5+2]) + abs(bayer_set[2*5+2] - bayer_set[4*5+4]) +
                     abs(bayer_set[1*5+1] - bayer_set[3*5+3]);
               sw_diff = abs(bayer_set[0*5+4] - bayer_set[2*5+2]) + abs(bayer_set[2*5+2] - bayer_set[4*5+0]) +
                     abs(bayer_set[1*5+3] - bayer_set[3*5+1]);

               calc_temp[0] = (bayer_set[2*5+1] + bayer_set[2*5+3])/2;
               calc_temp[1] = (bayer_set[1*5+2] + bayer_set[3*5+2])/2;
               calc_temp[2] = (bayer_set[1*5+3] + bayer_set[3*5+1])/2;
               calc_temp[3] = (bayer_set[1*5+1] + bayer_set[3*5+3])/2;
               calc_temp[4] = (2*bayer_set[2*5+2] - (bayer_set[2*5+0] + bayer_set[2*5+4]))/2;
               calc_temp[5] = (2*bayer_set[2*5+2] - (bayer_set[0*5+2] + bayer_set[4*5+2]))/2;
               calc_temp[6] = (2*bayer_set[2*5+2] - (bayer_set[0*5+0] + bayer_set[4*5+4]))/2;
               calc_temp[7] = (2*bayer_set[2*5+2] - (bayer_set[0*5+4] + bayer_set[4*5+0]))/2;
               calc_temp[8] = (2*bayer_set[2*5+2] - (bayer_set[1*5+3] + bayer_set[3*5+1]))/2;
               calc_temp[9] = (2*bayer_set[2*5+2] - (bayer_set[1*5+1] + bayer_set[3*5+3]))/2;
               calc_temp[10] = (bayer_set[0*5+3] + bayer_set[2*5+3] + bayer_set[2*5+1] + bayer_set[4*5+1])/4;
               calc_temp[11] = (bayer_set[1*5+2] + bayer_set[1*5+4] + bayer_set[3*5+0] + bayer_set[3*5+2])/4;
               calc_temp[12] = (bayer_set[0*5+1] + bayer_set[2*5+1] + bayer_set[2*5+3] + bayer_set[4*5+3])/4;
               calc_temp[13] = (bayer_set[1*5+0] + bayer_set[1*5+2] + bayer_set[3*5+2] + bayer_set[3*5+4])/4;
               calc_temp[14] = (bayer_set[1*5+1] + bayer_set[1*5+3] + bayer_set[3*5+1] + bayer_set[3*5+3])/4;
               calc_temp[15] = (bayer_set[1*5+2] + bayer_set[2*5+3] + bayer_set[3*5+2] + bayer_set[2*5+1])/4;
               calc_temp[16] = (bayer_set[2*5+1] + bayer_set[2*5+3] - bayer_set[1*5+2] - bayer_set[3*5+2])/2;
               calc_temp[17] = (bayer_set[1*5+2] + bayer_set[3*5+2] - bayer_set[2*5+1] - bayer_set[2*5+3])/2;
               calc_temp[18] = (bayer_set[1*5+1] + bayer_set[3*5+3] - bayer_set[1*5+3] - bayer_set[3*5+1])/2;
               calc_temp[19] = (bayer_set[1*5+3] + bayer_set[3*5+1] - bayer_set[1*5+1] - bayer_set[3*5+3])/2;

               if (h_diff<=v_diff && h_diff<=nw_diff && h_diff<=sw_diff) {
                  if (l==0 && k==0) {
                     pixel_temp_r = calc_temp[0]+calc_temp[4];
                     pixel_temp_g = bayer_set[2*5+2];
                     pixel_temp_b = calc_temp[1]+calc_temp[5];
                  } else if (l==0 && k==1) {
                     pixel_temp_r = bayer_set[2*5+2];
                     pixel_temp_g = calc_temp[0]+calc_temp[4];
                     pixel_temp_b = calc_temp[14]+calc_temp[16];
                  } else if (l==1 && k==0) {
                     pixel_temp_r = calc_temp[14]+calc_temp[16];
                     pixel_temp_g = calc_temp[0]+calc_temp[4];
                     pixel_temp_b = bayer_set[2*5+2];
                  } else {
                     pixel_temp_r = calc_temp[1]+calc_temp[5];
                     pixel_temp_g = bayer_set[2*5+2];
                     pixel_temp_b = calc_temp[0]+calc_temp[4];
                  }
               } else if (v_diff<=h_diff && v_diff<=nw_diff && v_diff<=sw_diff) {
                  if (l==0 && k==0) {
                     pixel_temp_r = calc_temp[0]+calc_temp[4];
                     pixel_temp_g = bayer_set[2*5+2];
                     pixel_temp_b = calc_temp[1]+calc_temp[5];
                  } else if (l==0 && k==1) {
                     pixel_temp_r = bayer_set[2*5+2];
                     pixel_temp_g = calc_temp[1]+calc_temp[5];
                     pixel_temp_b = calc_temp[14]+calc_temp[17];
                  } else if (l==1 && k==0) {
                     pixel_temp_r = calc_temp[14]+calc_temp[17];
                     pixel_temp_g = calc_temp[1]+calc_temp[5];
                     pixel_temp_b = bayer_set[2*5+2];
                  } else {
                     pixel_temp_r = calc_temp[1]+calc_temp[5];
                     pixel_temp_g = bayer_set[2*5+2];
                     pixel_temp_b = calc_temp[0]+calc_temp[4];
                  }
               } else if (nw_diff<=h_diff && nw_diff<=v_diff && nw_diff<=sw_diff) {
                  if (l==0 && k==0) {
                     pixel_temp_r = calc_temp[10]+calc_temp[8];
                     pixel_temp_g = bayer_set[2*5+2];
                     pixel_temp_b = calc_temp[11]+calc_temp[8];
                  } else if (l==0 && k==1) {
                     pixel_temp_r = bayer_set[2*5+2];
                     pixel_temp_g = calc_temp[15]+calc_temp[18];
                     pixel_temp_b = calc_temp[3]+calc_temp[6];
                  } else if (l==1 && k==0) {
                     pixel_temp_r = calc_temp[3]+calc_temp[6];
                     pixel_temp_g = calc_temp[15]+calc_temp[18];
                     pixel_temp_b = bayer_set[2*5+2];
                  } else {
                     pixel_temp_r = calc_temp[11]+calc_temp[8];
                     pixel_temp_g = bayer_set[2*5+2];
                     pixel_temp_b = calc_temp[10]+calc_temp[8];
                  }
               } else {
                  if (l==0 && k==0) {
                     pixel_temp_r = calc_temp[12]+calc_temp[9];
                     pixel_temp_g = bayer_set[2*5+2];
                     pixel_temp_b = calc_temp[11]+calc_temp[9];
                  } else if (l==0 && k==1) {
                     pixel_temp_r = bayer_set[2*5+2];
                     pixel_temp_g = calc_temp[15]+calc_temp[19];
                     pixel_temp_b = calc_temp[2]+calc_temp[7];
                  } else if (l==1 && k==0) {
                     pixel_temp_r = calc_temp[2]+calc_temp[7];
                     pixel_temp_g = calc_temp[15]+calc_temp[19];
                     pixel_temp_b = bayer_set[2*5+2];
                  } else {
                     pixel_temp_r = calc_temp[11]+calc_temp[9];
                     pixel_temp_g = bayer_set[2*5+2];
                     pixel_temp_b = calc_temp[12]+calc_temp[9];
                  }
               }

               if (pixel_temp_r<0) {
                  bayer_dst_r[(j*2+l)*res_w+i*2+k] = 0;
               } else if (pixel_temp_r>max_output_value) {
                  bayer_dst_r[(j*2+l)*res_w+i*2+k] = max_output_value;
               } else {
                  bayer_dst_r[(j*2+l)*res_w+i*2+k] = pixel_temp_r;
               }
               if (pixel_temp_g<0) {
                  bayer_dst_g[(j*2+l)*res_w+i*2+k] = 0;
               } else if (pixel_temp_g>max_output_value) {
                  bayer_dst_g[(j*2+l)*res_w+i*2+k] = max_output_value;
               } else {
                  bayer_dst_g[(j*2+l)*res_w+i*2+k] = pixel_temp_g;
               }
               if (pixel_temp_b<0) {
                  bayer_dst_b[(j*2+l)*res_w+i*2+k] = 0;
               } else if (pixel_temp_b>max_output_value) {
                  bayer_dst_b[(j*2+l)*res_w+i*2+k] = max_output_value;
               } else {
                  bayer_dst_b[(j*2+l)*res_w+i*2+k] = pixel_temp_b;
               }


            }
         }





      }
   }


}
//}}}

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
