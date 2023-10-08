#include "test.h"

#include "core/logger.h"
#include <locale.h>
#include "core/memory/memory.h"
#include "core/memory/freelist.h"

#include <time.h>
#include <stdlib.h>

void test() {
    setlocale(LC_ALL, "jp.utf8");

    srand(time(NULL));

    logger_log(LOG_LEVEL_DEBUG, "node size: %d", sizeof(freelist_node));

    freelist the_data;
    freelist_create(1024*1024*1024, &the_data);

    const int DATA_COUNT = 10000;

    void* datas[DATA_COUNT];

    for (u32 i = 0; i < DATA_COUNT; i++) {
        datas[i] = freelist_allocate(rand() % 3000, &the_data);

        if (datas[i]) {
            freelist_node* node = (freelist_node*)(datas[i]-sizeof(freelist_node));
            logger_log(LOG_LEVEL_INFO, "#%d: size: %d, pointer: %p, dist: %d", i+1, node->size, (void*)((void*)node), (((void*)node+sizeof(freelist_node))-the_data.memory));
        }

        if (rand() % 10 < 3 && i != 0) {
            u32 cur_pos = rand() % i;
            if (datas[cur_pos]) {
                freelist_free(&the_data, datas[cur_pos]);
                datas[cur_pos] = NULL;
                logger_log(LOG_LEVEL_INFO, "#%d freed", cur_pos+1);
            }
        }
    }

    freelist_destroy(&the_data);
}