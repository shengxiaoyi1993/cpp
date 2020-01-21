#include "hand.h"
#include <iostream>


using namespace std;

Hand::Hand(){
    _gamegesture=GameGesture_notready;

}


Hand::Hand(GameGesture v_gamegesture):_gamegesture(v_gamegesture){
    setGameGesture(_gamegesture);
}

void Hand::setGameGesture(GameGesture v_type){
    _gamegesture=v_type;
    switch (_gamegesture) {
    case GameGesture_rock:{
        _finger_thumb.setBend();
        _finger_index.setBend();
        _finger_middle.setBend();
        _finger_ring.setBend();
        _finger_little.setBend();
        break;
    }
    case GameGesture_paper:{
        _finger_thumb.setStraight();
        _finger_index.setStraight();
        _finger_middle.setStraight();
        _finger_ring.setStraight();
        _finger_little.setStraight();
        break;
    }
    case GameGesture_notready:{
        break;
    }
    case GameGesture_scissors:{
        _finger_thumb.setBend();
        _finger_index.setStraight();
        _finger_middle.setStraight();
        _finger_ring.setBend();
        _finger_little.setBend();
        break;
    }
    }
}


GameGesture Hand::getGameGesture(){
    if(isRock()){
        return GameGesture_rock;
    }
    else if(isPaper()){
        return GameGesture_paper;
    }
    else if(isScissors()){
        return GameGesture_scissors;
    }
    else{
        return GameGesture_notready;
    }
}


void Hand::printGesture(){

    FingerStatus status_thumb=_finger_thumb.status();
    FingerStatus status_index=_finger_index.status();
    FingerStatus status_middle=_finger_middle.status();
    FingerStatus status_ring=_finger_ring.status();
    FingerStatus status_little=_finger_little.status();
    cout<<"status_thumb: "<<status_thumb<<endl;
    cout<<"status_index: "<<status_index<<endl;
    cout<<"status_middle: "<<status_middle<<endl;
    cout<<"status_ring: "<<status_ring<<endl;
    cout<<"status_little: "<<status_little<<endl;

}
