#ifndef BAYER_CONVERT_H
#define BAYER_CONVERT_H


#ifdef __cplusplus

extern "C"{

#endif


void bayer_cfa_5x5(unsigned short *bayer_src, unsigned short res_w, unsigned short res_h,
      unsigned short *bayer_dst_r, unsigned short *bayer_dst_g, unsigned short *bayer_dst_b);

void bayer_cfa_5x5_fine(unsigned short *bayer_src, unsigned short res_w, unsigned short res_h,
      unsigned short *bayer_dst_r, unsigned short *bayer_dst_g, unsigned short *bayer_dst_b);
void bayer_cfa_7x7(unsigned short *bayer_src, unsigned short res_w, unsigned short res_h,
      unsigned short *bayer_dst_r, unsigned short *bayer_dst_g, unsigned short *bayer_dst_b);

#ifdef __cplusplus
}
#endif

#endif
