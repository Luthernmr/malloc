#include "malloc.h"

extern pthread_mutex_t g_malloc_mutex;
extern t_zone *g_zones[3];

static void print_hex(size_t value) {
    char hex_digits[] = "0123456789ABCDEF";
    char buffer[20];
    int i = 0;
    
    if (value == 0) {
        write(1, "0x0", 3);
        return;
    }
    
    while (value > 0) {
        buffer[i++] = hex_digits[value % 16];
        value /= 16;
    }
    
    write(1, "0x", 2);
    while (i > 0) {
        write(1, &buffer[--i], 1);
    }
}

static void print_number(size_t value) {
    char buffer[20];
    int i = 0;
    
    if (value == 0) {
        write(1, "0", 1);
        return;
    }
    
    while (value > 0) {
        buffer[i++] = '0' + (value % 10);
        value /= 10;
    }
    
    while (i > 0) {
        write(1, &buffer[--i], 1);
    }
}

static void show_zone_blocks(t_zone *zone) {
    t_block *block = zone->blocks;
    
    while (block) {
        if (!block->is_free) {
            void *start = (void *)((char *)block + sizeof(t_block));
            void *end = (void *)((char *)start + block->size);
            
            print_hex((size_t)start);
            write(1, " - ", 3);
            print_hex((size_t)end);
            write(1, " : ", 3);
            print_number(block->size);
            write(1, " bytes\n", 7);
        }
        block = block->next;
    }
}

static size_t get_total_allocated() {
    size_t total = 0;
    
    for (int i = 0; i < 3; i++) {
        t_zone *zone = g_zones[i];
        while (zone) {
            t_block *block = zone->blocks;
            while (block) {
                if (!block->is_free) {
                    total += block->size;
                }
                block = block->next;
            }
            zone = zone->next;
        }
    }
    
    return total;
}

void show_alloc_mem(void) {
    pthread_mutex_lock(&g_malloc_mutex);
    
    // Show TINY zones
    t_zone *zone = g_zones[0]; // TINY
    if (zone) {
        write(1, "TINY : ", 7);
        print_hex((size_t)zone);
        write(1, "\n", 1);
        while (zone) {
            show_zone_blocks(zone);
            zone = zone->next;
        }
    }
    
    // Show SMALL zones
    zone = g_zones[1]; // SMALL
    if (zone) {
        write(1, "SMALL : ", 8);
        print_hex((size_t)zone);
        write(1, "\n", 1);
        while (zone) {
            show_zone_blocks(zone);
            zone = zone->next;
        }
    }
    
    // Show LARGE zones
    zone = g_zones[2]; // LARGE
    if (zone) {
        write(1, "LARGE : ", 8);
        print_hex((size_t)zone);
        write(1, "\n", 1);
        while (zone) {
            show_zone_blocks(zone);
            zone = zone->next;
        }
    }
    
    // Show total
    write(1, "Total : ", 8);
    print_number(get_total_allocated());
    write(1, " bytes\n", 7);
    
    pthread_mutex_unlock(&g_malloc_mutex);
}