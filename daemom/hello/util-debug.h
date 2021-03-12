#ifndef __UTIL_DEBUG_H__
#define __UTIL_DEBUG_H__

#ifndef LOG_PRINT
#define LOG_MAX_LOG_MSG_LEN 2048
#define Log(x, file, func, line, ...)                           \
    do {                                                        \
        char _log_msg[LOG_MAX_LOG_MSG_LEN];                     \
        snprintf(_log_msg, LOG_MAX_LOG_MSG_LEN, __VA_ARGS__);   \
        fprintf(stdout, "<%s> %s\n", x, _log_msg);              \
    } while(0)

#define LogError(...) Log("ERROR", \
        __FILE__, __FUNCTION__, __LINE__, __VA_ARGS__)

#define LogWarning(...) Log("WARNING", \
        __FILE__, __FUNCTION__, __LINE__, __VA_ARGS__)

#define LogInfo(...) Log("INFO", \
        __FILE__, __FUNCTION__, __LINE__, __VA_ARGS__)

#define LogDebug(...) Log("DEBUG", \
        __FILE__, __FUNCTION__, __LINE__, __VA_ARGS__)

#define FatalError(...) do {                                           \
    LogError(__VA_ARGS__);                                             \
    exit(EXIT_FAILURE);                                                \
} while(0)
#endif

#endif //__UTIL_DEBUG_H__
