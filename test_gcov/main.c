// main.c
#include <stdio.h>
#include <stdlib.h>

void test(int vount);

int main(int argc, char *argv[])
{
    int i = 0;
    if(argc == 2)
        i = atoi(argv[1]);
    else
        i = 10;

    printf("arg is %d\n", i);

    test(i);

    return EXIT_SUCCESS;
}