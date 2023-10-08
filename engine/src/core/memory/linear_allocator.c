#include "linear_allocator.h"

#include "memory.h"
#include "core/logger.h"

void linear_allocator_create(u32 size, linear_allocator* out_lallocator) {
    out_lallocator->head = memory_malloc(size);
    out_lallocator->current = out_lallocator->head;

    out_lallocator->size = size;
}

void linear_allocator_destroy(linear_allocator* lallocator) {
    memory_free(lallocator->head);

    lallocator->head = 0;
    lallocator->current = 0;
    lallocator->size = 0;
}

void linear_allocator_reset(linear_allocator* lallocator) {
    memory_zero(lallocator->size, lallocator->head);

    lallocator->current = lallocator->head;
}

void* linear_allocator_allocate(u32 size, linear_allocator* lallocator) {
    u32 remainder = linear_allocator_get_free_space(lallocator);

    if (size > remainder) {
        logger_log(LOG_LEVEL_ERROR, "attempt to allocate %d into linear allocator with %d remaining", size, remainder);
        return NULL;
    }

    void* current = (void*)(lallocator->current+1);
    lallocator->current += size;

    return current;
}

u32 linear_allocator_get_free_space(linear_allocator* lallocator) {
    u32 cur_size = lallocator->current - lallocator->head;
    return lallocator->size - cur_size;
}