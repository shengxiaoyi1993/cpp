#include<iostream>
#include "licenseGenerator/licensegenerator.h"
#define SECONDS_PER_YEAR  60*60*24*365UL
using namespace std;

 int main() {
   int count =0;
   int num =1000000;

//   while (count<=1000) {
////     cout<<count<<":"<<LicenseGenerator::generatorRandomLicense()<<endl;
//     cout<<count<<":"<<num<<endl;
//     num/=2;
//     count++;
//   }
   int a[]={100000,10000,1000};
   int nums=3;
   vector<int> list;
   for(int i=0;i<nums;i++){
     list.push_back(a[i]);
   }
   LicenseGenerator generator(1000,1000000,list);
   generator.print();

//   for(uint i=0;i<1000000;i++){
//     cout<<i<<":"<<generator.getOnePlateAndRm()<<endl;
//   }

  return 0;
}
