#include <iostream>
#include <string>
#include "pnm/pnm.h"

using namespace std;
 int main() {
//   try {
//     string path_image="../resources/ground.pgm";
//     PNM pgm(path_image);
//     pgm.saveToFile("../resources/ground_copy.pgm",PNM::MagicNumber_p5);
//   } catch (const char * err_msg) {
//     cout<<"err_msg:"<<err_msg<<endl;

//   }

   //load ppm_binary resources/binary_mc.ppm
   try {
     string path_image="../resources/binary_mc.ppm";
     PNM pgm(path_image);
     pgm.saveToFile("../resources/binary_mc_copy_10_low.ppm",PNM::MagicNumber_p5,4095);
   } catch (const char * err_msg) {
     cout<<"err_msg:"<<err_msg<<endl;

   }




  return 0;
}
