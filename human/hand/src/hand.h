#ifndef HAND_H
#define HAND_H

#include<iostream>
#include "finger.h"


enum GameGesture{
    GameGesture_rock=0,
    GameGesture_paper,
    GameGesture_scissors,
    GameGesture_notready
};

class Hand{


public:


    Hand();
    Hand(GameGesture v_gamegesture);
    GameGesture getGameGesture();
    void printGesture();
    void setGameGesture(GameGesture v_type);

    bool isRock(){
        if(        _finger_thumb.isBend()&&
                   _finger_index.isBend()&&
                   _finger_middle.isBend()&&
                   _finger_ring.isBend()&&
                   _finger_little.isBend()){
            return true;
        }
        else{
            return false;
        }
    }

    bool isPaper(){
        if(        _finger_thumb.isStraight()&&
                   _finger_index.isStraight()&&
                   _finger_middle.isStraight()&&
                   _finger_ring.isStraight()&&
                   _finger_little.isStraight()){
            return true;
        }
        else{
            return false;
        }
    }

    bool isScissors(){
        if(        _finger_thumb.isBend()&&
                   _finger_index.isStraight()&&
                   _finger_middle.isStraight()&&
                   _finger_ring.isBend()&&
                   _finger_little.isBend()){
            return true;
        }
        else{
            return false;
        }
    }

    bool isReady(){
        if(isRock()||isPaper()||isScissors()
                ){
            return true;
        }
        else{
            return false;
        }

    }


private:
    Finger _finger_thumb;
    Finger _finger_index;
    Finger _finger_middle;
    Finger _finger_ring;
    Finger _finger_little;
    GameGesture _gamegesture;




};



#endif
