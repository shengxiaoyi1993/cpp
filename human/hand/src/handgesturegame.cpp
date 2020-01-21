

#include "handgesturegame.h"


ostream & operator <<(ostream & out,GameResult &d)
{
    static const char *maps[4]={"win","lose","draw","invalid"};
    return out<<maps[d];
}


ostream & operator <<(ostream & out,TestType &d)
{
    static const char *maps[2]={"input","output"};
    return out<<maps[d];
}
