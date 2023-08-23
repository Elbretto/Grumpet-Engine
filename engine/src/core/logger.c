#include "logger.h"

#include <stdio.h>
#include <stdarg.h>
#include <string.h>

#include "platform/platform.h"

const char* log_level_strings[7] = {"[fatal] ", "[error] ", "[warning] ", "[info] ", "[debug] ","[trace] ","[assertion] "};

const u8 MAX_LOG_LEVEL = LOG_LEVEL_TRACE; // assertions show up regardless

void logger_log(log_level level, const char* message, ...) {
    if (level > MAX_LOG_LEVEL && level != LOG_LEVEL_ASSERT) {return;}

    char buffer_message[8192];
    memset(buffer_message, 0, sizeof(buffer_message));

    va_list va_arg;
    va_start(va_arg, message);

    vsnprintf(buffer_message, sizeof(buffer_message), message, va_arg);

    va_end(va_arg);

    char out_message[8192];
    sprintf(out_message, "%s%s\n", log_level_strings[level], buffer_message);

    platform_out(level, out_message);
}