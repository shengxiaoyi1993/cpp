#include <stdio.h>
#include <unistd.h>
#include <iostream>
#include <fstream>

int main()
{
  while (true) {
    std::ostream ostream("sayhello.log",std::ios::app);
    ostream<<"hello "<<endl;



    /* code */
  }
    // PidfileRemove(pidfile);
    return 0;
}
