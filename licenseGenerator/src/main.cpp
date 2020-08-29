#include<iostream>
#include "licenseGenerator/licensegenerator.h"
#define SECONDS_PER_YEAR  60*60*24*365UL
using namespace std;

 int main() {
   int count =0;
   while (true) {
     cout<<count<<":"<<LicenseGenerator::generatorRandomLicense()<<endl;
     count++;

   }
  return 0;
}
