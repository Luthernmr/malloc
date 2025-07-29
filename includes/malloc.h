#ifndef MALLOC_H
#define MALLOC_H

#include <stddef.h>
#include <string.h>
#include <unistd.h>
#include <sys/mman.h>
#include <pthread.h>

#define TINY_LIMIT   512
#define SMALL_LIMIT  4096
#define MIN_ZONE_ALLOC 100
#define HISTORY_SIZE 1000

typedef struct s_alloc_history {
    void *ptr;
    size_t size;
    char operation; // 'M' for malloc, 'F' for free, 'R' for realloc
    unsigned int timestamp;
} t_alloc_history;

extern t_alloc_history g_alloc_history[HISTORY_SIZE];
extern int g_history_index;



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
void show_alloc_mem(void);
void show_alloc_mem_ex(void);
void add_to_history(void *ptr, size_t size, char operation);

#endif
