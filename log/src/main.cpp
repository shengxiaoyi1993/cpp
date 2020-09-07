#include"syslogger/syslogger.h"
#include <iostream>
//#include"syslog.h"

using namespace std;

#ifndef DEBUG
#define DEBUG 2
#endif


int main()
{

  cout<<"DEBUG:"<<DEBUG<<endl;
    cout << "Hello World!" << endl;
    SysLogger logger;
    logger.InitLogger("log.txt",0);
    logger.WriteLog(0,"log.txt",1,0,"txt:%s","hello");

    SysLogger logger1;

    logger1.InitLogger("log1.txt",1);
    logger1.WriteLog(1,"log1.txt",1,0,"txt:%s","hello");
    logger1.GetInstance();
    LOG_INFO_NOLOCK("INFO:%s","hhh");


    return 0;
}
