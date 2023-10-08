#pragma once

#include <definitions.h>

typedef struct freelist_node {
    u8 is_free;
    u64 size;
    struct freelist_node* next;
    struct freelist_node* prev;
} freelist_node;

typedef struct freelist {
    freelist_node* first_free;
    freelist_node* head_prev; // dummy tail for head node
    void* memory;
} freelist;

u8 freelist_create(u64 size, freelist* out_freelist);
void freelist_destroy(freelist* flist);

void* freelist_allocate(u64 size, freelist* flist);
void freelist_free(freelist* flist, void* data);