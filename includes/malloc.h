#ifndef MALLOC_H
#define MALLOC_H

#include <stddef.h>
#include <string.h>
#include <unistd.h>
#include <sys/mman.h>
#include <pthread.h>

typedef enum { TINY, SMALL, LARGE } zone_type;

typedef struct s_block {
    size_t size;
    int is_free;
    struct s_block *next;
} t_block;

extern t_block *g_free_blocks_list;

typedef struct s_zone {
    void *start;
    zone_type type;
    t_block *blocks;
    struct s_zone *next;
} t_zone;


void *malloc(size_t size);
void *realloc(void *ptr, size_t size);
void free(void *ptr);

#endif
