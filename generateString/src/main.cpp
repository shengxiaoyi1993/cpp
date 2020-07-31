#include <iostream>
#include "export.h"


using namespace std;
 int main() {
   string sn=generateSNString(16,true,true,true) ;
   string encrypted=generateEncryptedString(sn,"sskj9900");
   std::cout << "sn       :   "<<sn << '\n';
   std::cout << "encrypted:   "<<encrypted << '\n';


  return 0;
}
