#pragma once

#include <definitions.h>

void* memory_malloc(u64 size);

void memory_realloc(u64 size, void* pointer);

void memory_free(void* pointer);

void memory_copy(void* dest, void* src, u64 size);

void memory_zero(u64 size, void* pointer);