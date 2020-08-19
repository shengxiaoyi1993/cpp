#include <iostream>
#include <string>
#include "pnm.h"

using namespace std;
 int main() {
   string path_image="../resources/ground.pgm";
   PNM pgm(path_image);
   pgm.saveToFile("../resources/ground_copy.pgm",PNM::MagicNumber_p5);

  return 0;
}
