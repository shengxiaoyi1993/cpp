#include "finger.h"
#include "basic.h"


Finger::Finger(){
    if(basic::getRandomNum(0,1)==0){
        _status=FingerStatus_straight;

    }
    else{
        _status=FingerStatus_bend;
    }

}

Finger::Finger(FingerStatus v_status):_status(v_status){

}



void Finger::setStraight(){
    _status=FingerStatus_straight;

}

void Finger::setBend(){
    _status=FingerStatus_bend;

}


bool Finger::isStraight(){
    return _status==FingerStatus_straight;
}

bool Finger::isBend(){
    return _status==FingerStatus_bend;

}

ostream & operator <<(ostream & out,FingerStatus &d)
{
    static const char *maps[2]={"straight","bend"};
    return out<<maps[d];
}
