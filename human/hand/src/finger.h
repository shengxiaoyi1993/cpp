#ifndef FINGER_H
#define FINGER_H

#include <iostream>

using namespace std;

enum FingerStatus{
    FingerStatus_straight=0,
    FingerStatus_bend
};

ostream & operator <<(ostream & out,FingerStatus &d);



class Finger{


private:
    FingerStatus _status;

public:
    Finger();
    Finger(FingerStatus v_status);
    void setStraight();
    void setBend();
    bool isStraight();
    bool isBend();
    FingerStatus status(){
        return _status;
    }

};





#endif
