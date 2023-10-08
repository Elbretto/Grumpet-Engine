#pragma once

#include <definitions.h>

typedef struct linear_allocator
{
    u32 size;
    void* current;
    void* head;
} linear_allocator;

void linear_allocator_create(u32 size, linear_allocator* out_lallocator);

void linear_allocator_destroy(linear_allocator* lallocator);

void linear_allocator_reset(linear_allocator* lallocator);

void* linear_allocator_allocate(u32 size, linear_allocator* lallocator);

u32 linear_allocator_get_free_space(linear_allocator* lallocator);