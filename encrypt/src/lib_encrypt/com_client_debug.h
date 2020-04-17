#ifndef DEBUG_H
#define DEBUG_H

//#define COM_CLIEN_DEBUG

#ifdef COM_CLIEN_DEBUG

#define COM_CLIENT_Print(x,...)\
printf("[COM CLIENT DEBUG] [%s][%s:%d] ",__FILE__,__FUNCTION__,__LINE__);\
printf(x,##__VA_ARGS__);\
printf("\n");
#else
#define COM_CLIENT_Print(x,...)
#endif

#endif // DEBUG_H
