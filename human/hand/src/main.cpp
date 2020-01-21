#include <iostream>
#include "hand.h"
#include "basic.h"
#include "handgesturegame.h"

using namespace std;
int main() {

    Hand hand_0(GameGesture_scissors);
    Hand hand_1(GameGesture_paper);


    GameResult result=HandGestureGame::isWin(hand_0,hand_1);
    cout<<"hand_0 "<<result<<" hand_1"<<endl;


    return 0;

}

