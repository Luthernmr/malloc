#include "malloc.h"

extern pthread_mutex_t g_malloc_mutex;
extern t_zone *g_zones[3];

static t_block *find_block_by_ptr(void *ptr, t_zone **out_zone) {
    for (int i = 0; i < 3; i++) {
        t_zone *zone = g_zones[i];
        while (zone) {
            t_block *block = zone->blocks;
            while (block) {
                if ((void *)((char *)block + sizeof(t_block)) == ptr) {
                    if (out_zone)
                        *out_zone = zone;
                    return block;
                }
                block = block->next;
            }
            zone = zone->next;
        }
    }
    return NULL;
}

void *realloc(void *ptr, size_t size) {
    if (!ptr)
        return malloc(size);
    if (size == 0) {
        free(ptr);
        return NULL;
    }


    pthread_mutex_lock(&g_malloc_mutex);

    t_zone *zone = NULL;
    t_block *block = find_block_by_ptr(ptr, &zone);

    if (!block) {
        pthread_mutex_unlock(&g_malloc_mutex);
        return NULL; 
    }

    if (block->size >= size) {
        pthread_mutex_unlock(&g_malloc_mutex);
        return ptr;
    }

    pthread_mutex_unlock(&g_malloc_mutex);

    void *new_ptr = malloc(size);
    if (!new_ptr)
        return NULL;

    memcpy(new_ptr, ptr, block->size);
    free(ptr);

    // Ajouter à l'historique
    add_to_history(new_ptr, size, 'R');

    return new_ptr;
}
