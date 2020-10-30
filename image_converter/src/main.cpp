#include <iostream>
#include "ImageConverter.hpp"
#include "../lib/pnm/pnm.h"
#include "../lib/raw/raw.h"

using namespace std;


//load from pnm ,save to pnm
void test_PNM2PNM();

//load from raw,save to pnm
void test_RAW2PNM();
//load from raw,save to pnm
void test_JPEG2PNM();
void test_PNM2JPEG();


 int main() {
//   test_PNM2PNM();
//   test_RAW2PNM();
//   test_JPEG2PNM();
   test_PNM2JPEG();

  return 0;
}




 void test_PNM2PNM(){
   try {
     string file_ppm="../../resources/image_pnm/ppm_8_bi.ppm";
     string file_ppm_ret="../../resources/image_pnm/pgm_8_bi.pgm";

     ImageConverter imageconverter(file_ppm,ImageType::ImageType_PNM);
     imageconverter.saveToPNM(file_ppm_ret, PNM::MagicNumber_p5,255);
   } catch (  string msg) {
     cout<<"msg:"<<msg<<endl;
   }

 }


 void test_RAW2PNM(){
   try {
     string file="../../resources/image_raw/imagebuffer.raw";
     string file_copy="../../resources/image_raw/imagebuffer_copy.raw";
     string ret_file="../../resources/image_result/imagebuffer_fromraw.ppm";
     ImageConverter   imageconverter(file,ImageType::ImageType_RAW,3,8,8,4096,4096);
     imageconverter.saveToPNM(ret_file, PNM::MagicNumber_p6,255);

   } catch (string msg) {
     cout<<"msg:"<<msg<<endl;
   }

 }

 void test_JPEG2PNM(){
   try {
     string file_jpg="../resources/image_jpeg/jpg_rgb.jpeg";
     string file_pnm="../resources/image_jpeg/ppm_fromjpg_255.ppm";
     ImageConverter   imageconverter(file_jpg,ImageType::ImageType_JPEG);
     imageconverter.saveToPNM(file_pnm, PNM::MagicNumber_p6,255);
   } catch (string msg) {
     cout<<"msg:"<<msg<<endl;
   }
 }

 void test_PNM2JPEG(){
   try {
     string file_pnm="../resources/image_jpeg/ppm_fromjpg_255.ppm";
     string file_jpg="../resources/image_jpeg/jpg_rgb_frompnm.jpeg";
     ImageConverter   imageconverter(file_pnm,ImageType::ImageType_PNM);
     imageconverter.saveToJPEG(file_jpg);
   } catch (string msg) {
     cout<<"msg:"<<msg<<endl;
   }
 }


