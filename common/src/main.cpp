#include <iostream>
#include "cpp/string_manipulation.hpp"

using namespace common::string_manipulation;

 int main() {
   BinaryData bdata(64,BinaryData::BinaryDataDirection_left);
   bdata.print();
   try {
     bdata.appendData<unsigned>(65535,1);
     bdata.print();

     bdata.appendData<unsigned>(65535,8);
     bdata.print();

     bdata.appendData<unsigned>(65535,8);
     bdata.print();

     bdata.endAppend(true);
     bdata.print();



   } catch (const char * msg) {
     cout<<"msg:"<<msg<<endl;

   }
   bdata.print();
//   unsigned int tmp= bdata.getSheld<unsigned>(7,9,true);



  return 0;
}
