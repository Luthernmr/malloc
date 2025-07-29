#include "malloc.h"

extern pthread_mutex_t g_malloc_mutex;
extern t_zone *g_zones[3];

static size_t get_zone_size_for_free(zone_type type) {
    size_t page_size = getpagesize();
    size_t raw_zone_size;

    if (type == TINY) {
        raw_zone_size = sizeof(t_zone) + MIN_ZONE_ALLOC * (sizeof(t_block) + TINY_LIMIT);
    } else if (type == SMALL) {
        raw_zone_size = sizeof(t_zone) + MIN_ZONE_ALLOC * (sizeof(t_block) + SMALL_LIMIT);
    } else {
        return 0; // LARGE zones sont gérées différemment
    }

    size_t pages = (raw_zone_size + page_size - 1) / page_size;
    return pages * page_size;
}

static int all_blocks_free(t_zone *zone) {
    t_block *block = zone->blocks;
    while (block) {
        if (!block->is_free)
            return 0;
        block = block->next;
    }
    return 1;
}

static void remove_zone(t_zone **head, t_zone *to_remove) {
    if (!head || !*head || !to_remove)
        return;

    if (*head == to_remove) {
        *head = to_remove->next;
    } else {
        t_zone *prev = *head;
        while (prev && prev->next != to_remove)
            prev = prev->next;
        if (prev)
            prev->next = to_remove->next;
    }
}

static void free_block(void *ptr) {
    for (int i = 0; i < 3; i++) {
        t_zone *zone = g_zones[i];
        while (zone) {
            t_block *block = zone->blocks;
            while (block) {
                if ((void *)((char *)block + sizeof(t_block)) == ptr) {
                    block->is_free = 1;

                    // FREE LARGE ZONE DIRECTLY
                    if (zone->type == LARGE) {
                        size_t zone_size = sizeof(t_zone) + sizeof(t_block) + block->size;
                        remove_zone(&g_zones[i], zone);
                        munmap(zone, zone_size);
                        return;
                    }

                    // FREE WHOLE ZONE IF ALL BLOCKS ARE FREE
                    if (all_blocks_free(zone)) {
                        size_t zone_size = get_zone_size_for_free(zone->type);
                        remove_zone(&g_zones[i], zone);
                        munmap(zone, zone_size);
                    }
                    return;
                }
                block = block->next;
            }
            zone = zone->next;
        }
    }
}

void free(void *ptr) {
    if (!ptr)
        return;

    // Ajouter à l'historique avant de libérer
    add_to_history(ptr, 0, 'F');

    pthread_mutex_lock(&g_malloc_mutex);
    free_block(ptr);
    pthread_mutex_unlock(&g_malloc_mutex);
}
