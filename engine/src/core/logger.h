#pragma once

#include <definitions.h>
#include <stdlib.h>

typedef enum log_level {
    LOG_LEVEL_FATAL,
    LOG_LEVEL_ERROR,
    LOG_LEVEL_WARN,
    LOG_LEVEL_INFO,
    LOG_LEVEL_DEBUG,
    LOG_LEVEL_TRACE,
    LOG_LEVEL_ASSERT
} log_level;

void logger_log(log_level level, const char* message, ...);

//#define NDEBUG

#ifdef NDEBUG
    #define logger_assert(expression) ((void)0)
#else
    #define logger_assert(expression)  ((void)(!(expression) && (logger_log(LOG_LEVEL_ASSERT, "%s; file: %s, line %d", #expression, __FILE__, __LINE__), 1) && (exit(0), 1)))
#endif