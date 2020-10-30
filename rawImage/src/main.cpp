#include<iostream>
#include "raw/raw.h"
#include "../lib/pnm/pnm.h"

using namespace std;

 int main() {
   try {
     string file="../../resources/imagebuffer.raw";
     string file_copy="../../test_result/imagebuffer_copy.raw";
     string file_copy_8="../../test_result/imagebuffer_copy_8.raw";
     string file_copy_16="../../test_result/imagebuffer_copy_16.raw";

     string ret_file="../../test_result/imagebuffer.ppm";
     string ret_file_8="../../test_result/imagebuffer_8.ppm";
     string ret_file_16="../../test_result/imagebuffer_16.ppm";

     RAW  rawdata(file,RAW::RAWType_RGGB,8,8,4096,4096);
     rawdata.saveToFile(file_copy,8);
     rawdata.saveToFile(file_copy_8,8);
     rawdata.saveToFile(file_copy_16,16);

     RAW  rawdata_8(file_copy_8,RAW::RAWType_RGGB,8,8,4096,4096);
     RAW  rawdata_16(file_copy_16,RAW::RAWType_RGGB,16,8,4096,4096);


     uint width;
     uint height;
     unsigned short *prgb=rawdata.getRGBData(width,height);
     uint width_8;
     uint height_8;
     unsigned short *prgb_8=rawdata.getRGBData(width_8,height_8);
     uint width_16;
     uint height_16;
     unsigned short *prgb_16=rawdata.getRGBData(width_16,height_16);

     PNM::saveDataToFile(ret_file,PNM::DataType_rgb,PNM::MagicNumber_p6,prgb,width,height,255);
     PNM::saveDataToFile(ret_file_8,PNM::DataType_rgb,PNM::MagicNumber_p6,prgb_8,width_8,height_8,255);
     PNM::saveDataToFile(ret_file_16,PNM::DataType_rgb,PNM::MagicNumber_p6,prgb_16,width_16,height_16,255);
     cout<<"[end]: result is stored in test_result/"<<endl;


     delete [] prgb;
     prgb=nullptr;
     delete [] prgb_8;
     prgb_8=nullptr;
     delete [] prgb_16;
     prgb_16=nullptr;


   } catch (string msg) {
     cout<<"msg:"<<msg<<endl;
   }

  return 0;
}
