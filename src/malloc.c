#include "malloc.h"

#define TINY_LIMIT   512
#define SMALL_LIMIT  4096
#define MIN_ZONE_ALLOC 100

pthread_mutex_t g_malloc_mutex = PTHREAD_MUTEX_INITIALIZER;
t_zone *g_zones[3] = {NULL, NULL, NULL}; // TINY, SMALL, LARGE
t_block *g_free_blocks_list = NULL;

static zone_type get_zone_type(size_t size) {
    if (size <= TINY_LIMIT)
        return TINY;
    if (size <= SMALL_LIMIT)
        return SMALL;
    return LARGE;
}

static size_t get_zone_size(zone_type type, size_t size) {
    size_t page_size = getpagesize();
    size_t raw_zone_size;

    if (type == TINY) {
        raw_zone_size = sizeof(t_zone) + MIN_ZONE_ALLOC * (sizeof(t_block) + TINY_LIMIT);
    } else if (type == SMALL) {
        raw_zone_size = sizeof(t_zone) + MIN_ZONE_ALLOC * (sizeof(t_block) + SMALL_LIMIT);
    } else if (type == LARGE) {
        return sizeof(t_block) + size;
    } else {
        return 0;
    }

    size_t pages = (raw_zone_size + page_size - 1) / page_size;
    return pages * page_size;
}
static t_block *find_free_block(t_zone *zone, size_t size) {
    t_block *block = zone->blocks;
    while (block) {
        if (block->is_free && block->size >= size)
            return block;
        block = block->next;
    }
    return NULL;
}

static t_zone *create_zone(zone_type type, size_t size) {
    size_t zone_size;
    zone_size = get_zone_size(type, size);
    void *mem = mmap(NULL, zone_size, PROT_READ | PROT_WRITE,
                     MAP_ANON | MAP_PRIVATE, -1, 0);
    if (mem == MAP_FAILED)
        return NULL;

    t_zone *zone = (t_zone *)mem;
    zone->start = mem;
    zone->type = type;
    zone->next = g_zones[type];
    g_zones[type] = zone;

    t_block *first_block = (t_block *)((char *)mem + sizeof(t_zone));
    first_block->size = zone_size - sizeof(t_zone) - sizeof(t_block);
    first_block->is_free = 1;
    first_block->next = NULL;
    zone->blocks = first_block;

    return zone;
}

static void *allocate_block(t_zone *zone __attribute__((unused)), 
                           t_block *block, 
                           size_t size __attribute__((unused))) {
    block->is_free = 0;
    return (void *)((char *)block + sizeof(t_block));
}

void *malloc(size_t size) {
    if (size == 0)
        return NULL;

    pthread_mutex_lock(&g_malloc_mutex);

    zone_type type = get_zone_type(size);
    t_zone *zone = g_zones[type];
    t_block *block = NULL;

    while (zone) {
        block = find_free_block(zone, size);
        if (block)
            break;
        zone = zone->next;
    }

    if (!block) {
        zone = create_zone(type, size);
        if (!zone) {
            pthread_mutex_unlock(&g_malloc_mutex);
            return NULL;
        }
        block = zone->blocks;
    }

    void *ptr = allocate_block(zone, block, size);
    pthread_mutex_unlock(&g_malloc_mutex);
    return ptr;
}
