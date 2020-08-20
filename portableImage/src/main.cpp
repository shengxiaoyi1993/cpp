#include <iostream>
#include <string>
#include "pnm.h"

using namespace std;
 int main() {
   try {
     string path_image="../resources/ground.pgm";
     PNM pgm(path_image);
     pgm.saveToFile("../resources/ground_copy.pgm",PNM::MagicNumber_p5);
   } catch (const char * err_msg) {
     cout<<"err_msg:"<<err_msg<<endl;

   }


  return 0;
}
