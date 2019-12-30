#include <iostream>
#include"syslogger.h"
//#include"syslog.h"

using namespace std;

int main()
{
    cout << "Hello World!" << endl;
    SysLogger logger;
    logger.InitLogger("log.txt",0);
    SysLogger logger1;

    logger1.InitLogger("log1.txt",1);
    logger1.WriteLog(1,"log1.txt",1,0,"txt","hello");


    logger.WriteLog(0,"log.txt",1,0,"txt","hello");
    return 0;
}
