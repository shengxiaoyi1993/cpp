
#include "basic.h"
#include <ctime>
#include <assert.h>
#include <iostream>

using namespace std;

namespace basic {

int getRandomNum(int num_start,int num_end){
    assert(num_start<=num_end);
    int count=num_end-num_start+1;
    int number=rand()%count;
    return number+num_start;
}



}
