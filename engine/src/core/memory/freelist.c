#include "freelist.h"

#include "memory.h"
#include "core/logger.h"

freelist_node* find_free_node(u64 size, freelist* flist, freelist_node* cur_node);

#define MIN_FREE_BLOCK_SPLIT 16

u8 freelist_create(u64 size, freelist* out_freelist) {
    logger_assert(out_freelist != NULL);

    out_freelist->memory = memory_malloc(size);
    memory_zero(size, out_freelist->memory);

    freelist_node* head = out_freelist->memory;
    head->prev = NULL;
    head->next = NULL;
    head->is_free = true;
    head->size = size-sizeof(freelist_node);

    logger_log(LOG_LEVEL_TRACE, "free list of size %d bytes created at %p", size, out_freelist->memory);

    return true;
}

void freelist_destroy(freelist* flist) {
    logger_assert(flist != NULL);

    memory_free(flist->memory);

    logger_log(LOG_LEVEL_TRACE, "free list destroyed");
}

freelist_node* freelist_allocate_node(u64 size, freelist* flist) {
    logger_assert(flist != NULL);

    if (size == 0) {
        logger_log(LOG_LEVEL_WARN, "%s", "attempted to allocate 0 bytes to free list");
        return NULL;
    }

    freelist_node* head = (freelist_node*)flist->memory;
    freelist_node* free_node = find_free_node(size, flist, head);

    if (!free_node) {
        logger_log(LOG_LEVEL_ERROR, "could not allocate %d bytes in free list", size);
        return NULL;
    } 

    u64 split_size = (free_node->size-size);
    if (split_size > sizeof(freelist_node)+MIN_FREE_BLOCK_SPLIT) {
        freelist_node* split_node = (freelist_node*)((void*)free_node+sizeof(freelist_node)+size);
        split_node->is_free = true;
        split_node->prev = free_node;
        split_node->next = free_node->next;
        split_node->size = split_size-sizeof(freelist_node);

        if (free_node->next) {
            free_node->next->prev = split_node;
        }

        free_node->next = split_node;

        free_node->size = size;
    }

    free_node->is_free = false;

    return free_node;
}

void* freelist_allocate(u64 size, freelist* flist) {
    freelist_node* node = freelist_allocate_node(size, flist);

    if(node) {
        return (void*)((void*)node+sizeof(freelist_node));
    }

    return NULL;
}

void freelist_free_node(freelist* flist, freelist_node* node) {
    u8 merged = false;
    if (node->next && node->next->is_free) {
        node->size += sizeof(freelist_node);

        u64 next_size = node->next->size;

        freelist_node* new_next = node->next->next;
        if (new_next) {
            new_next->prev = node;
        }

        memory_zero(node->size, (void*)((void*)node+sizeof(freelist_node)));

        node->size += next_size;

        node->next = new_next;

        node->is_free = true;

        merged = true;
    }

    if (node->prev && node->prev->is_free) {
        node->prev->size += node->size+sizeof(freelist_node);

        node->prev->next = node->next;

        if (node->next) {
            node->next->prev = node->prev;
        }

        memory_zero(node->size+sizeof(freelist_node), node);

        return;
    }
    
    if (!merged) {
        memory_zero(node->size, (void*)((void*)node+sizeof(freelist_node)));

        node->is_free = true;
    }
}

void freelist_free(freelist* flist, void* data) {
    logger_assert(flist != NULL && data != NULL);

    freelist_node* node = (freelist_node*)(data-sizeof(freelist_node));

    if (!node->is_free) {
        freelist_free_node(flist, node);
    } else {
        logger_log(LOG_LEVEL_WARN, "attempted to free already free block of memory in linked list");
    }
}

freelist_node* find_free_node(u64 size, freelist* flist, freelist_node* cur_node) {
    if (cur_node->is_free && cur_node->size >= size) {
        return cur_node;
    }

    if (cur_node->next && cur_node->next->size == 0) {
        logger_log(LOG_LEVEL_FATAL, "corruption at %p", (void*)cur_node->next);
    }

    if (!cur_node->next) {
        return NULL;
    }

    return find_free_node(size, flist, cur_node->next);
}