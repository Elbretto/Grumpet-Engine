#include "test.h"

#include "core/logger.h"

void test() {
    logger_log(LOG_LEVEL_TRACE, "*Whispers*");
    logger_log(LOG_LEVEL_DEBUG, "Hello World!");
    logger_assert(1 == 1);
    logger_log(LOG_LEVEL_INFO, "Hi");
    logger_log(LOG_LEVEL_WARN, "Stay frosty.");
    logger_log(LOG_LEVEL_ERROR, "Something really bad is happening!");
    logger_log(LOG_LEVEL_FATAL, "OH MY HEAVENS!!!!");
    logger_assert(1 == 2);
    logger_log(LOG_LEVEL_DEBUG, "Assertions are turned off.");
}