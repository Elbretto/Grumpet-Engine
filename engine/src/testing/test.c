#include "test.h"

#include "core/logger.h"
#include <locale.h>

void test() {
    setlocale(LC_ALL, "jp.utf8");

    logger_log(LOG_LEVEL_TRACE, "*囁いて*");
    logger_log(LOG_LEVEL_DEBUG, "こんにちは、世界！");
    logger_assert(1 == 1);
    logger_log(LOG_LEVEL_INFO, "はい");
    logger_log(LOG_LEVEL_WARN, "気を付けて。");
    logger_log(LOG_LEVEL_ERROR, "悪いことは怒っている！");
    logger_log(LOG_LEVEL_FATAL, "なんてことだ？？？？");
    logger_assert(1 == 2);
    logger_log(LOG_LEVEL_DEBUG, "Assertions are turned off.");
}