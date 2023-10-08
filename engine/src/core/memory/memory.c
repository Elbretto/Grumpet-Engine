#include "memory.h"

#include <stdlib.h>
#include <string.h>


void* memory_malloc(u64 size) {
    return malloc((size_t)size);
}

void memory_realloc(u64 size, void* pointer) {
    realloc(pointer, (size_t)size);
}

void memory_free(void* pointer) {
    free(pointer);
}

void memory_copy(void* dest, void* src, u64 size) {
    memcpy(dest, src, (size_t)size);
}

void memory_zero(u64 size, void* pointer) {
    memset(pointer, 0, size);
}