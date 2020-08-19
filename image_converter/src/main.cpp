#include <iostream>
#include "ImageConverter.hpp"


using namespace std;
 int main() {
   string file_ppm="../resources/test_raw.ppm";
   ImageConverter imageconverter(file_ppm,ImageType_PPM);
   // imageconverter.saveToFile("");

  return 0;
}
