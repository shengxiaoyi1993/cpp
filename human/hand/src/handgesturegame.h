#ifndef HANDGESTUREGAME_H
#define HANDGESTUREGAME_H

#include <iostream>
#include "hand.h"


using namespace std;
enum GameResult{
    GameResult_win=0,
    GameResult_lose,
    GameResult_draw,
    GameResult_invalid

};

enum TestType{
    TestType_output=0,
    TestType_input
};
ostream & operator <<(ostream & out,TestType &d);


ostream & operator <<(ostream & out,GameResult &d);



class HandGestureGame{

    public:
    static GameResult isWin(Hand v_sub,Hand v_obj){
        switch (v_sub.getGameGesture()) {
        case GameGesture_rock:{
            switch (v_obj.getGameGesture()) {
            case GameGesture_rock:{
                return GameResult_draw;
            }
            case GameGesture_paper:{
                return GameResult_lose;
            }
            case GameGesture_scissors:{
                return GameResult_win;
            }
            case GameGesture_notready:{
                return GameResult_invalid;
            }
            }
            break;
        }
        case GameGesture_paper:{
            switch (v_obj.getGameGesture()) {
            case GameGesture_rock:{
                return GameResult_win;
            }
            case GameGesture_paper:{
                return GameResult_draw;
            }
            case GameGesture_scissors:{
                return GameResult_lose;
            }
            case GameGesture_notready:{
                return GameResult_invalid;
            }
            }
            break;

        }
        case GameGesture_scissors:{
            switch (v_obj.getGameGesture()) {
            case GameGesture_rock:{
                return GameResult_lose;
            }
            case GameGesture_paper:{
                return GameResult_win;
            }
            case GameGesture_scissors:{
                return GameResult_draw;
            }
            case GameGesture_notready:{
                return GameResult_invalid;
            }
            }
            break;
        }
        case GameGesture_notready:{
            return GameResult_invalid;

        }
        }
    }


};




#endif
