#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <iostream>
#include "dvt-uio.h"
#include "out_drv.h"
#include "driver.h"

using namespace std;


int  main(int argc, char *argv[])
{
    Driver driver("/dev/uio0",Driver::DriverMode::DriverMode_IRQ_BLOCK
                  |Driver::DriverMode::DriverMode_IRQ_VALID);
    driver.printPara();

    getchar();
    return 0;
}

