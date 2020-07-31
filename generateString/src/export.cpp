#include "export.h"
#include <time.h>
#include "sha256.h"
#include <sys/time.h>

using namespace std;

string generateSNString(int v_length,bool v_hasbig,bool v_hassmall,bool v_hasnumber ){
  string ret;
  string standerd;
  string big="ABCDEFGHIJKLMNOPQRSTUVWXYZ";
  string small="abcdefghijklmnopqrstuvwxyz";
  string number="0123456789";
  if((!v_hasbig)&&(!v_hassmall)&&(!v_hasnumber)){
    return ret;
  }

  if(v_hasbig){
    standerd+=big;
  }
  if(v_hassmall){
    standerd+=small;
  }
  if(v_hasnumber){
    standerd+=number;
  }
  struct timeval start;
  gettimeofday( &start, NULL);
  srand((unsigned) (start.tv_sec*1000000+start.tv_usec));
  ret.resize(v_length);
  for (size_t i = 0; i < v_length; i++) {
    int tmp=rand()%standerd.size();
    ret[i]=standerd[tmp];
  }
  return ret;

}




string generateEncryptedString(string v_basic,string v_key){
  return picosha2::hash256_hex_string(v_basic+v_key);
}
