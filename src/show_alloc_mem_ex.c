#include "../includes/malloc.h"
#include "../libft/libft.h"
#include <sys/time.h>

// Variables globales pour l'historique
t_alloc_history g_alloc_history[HISTORY_SIZE];
int g_history_index = 0;

// Fonctions utilitaires pour show_alloc_mem_ex
static void print_hex_address(void *ptr) {
    unsigned long addr = (unsigned long)ptr;
    char hex_str[20];
    int i = 0;
    
    ft_putstr_fd("0x", 1);
    
    if (addr == 0) {
        ft_putchar_fd('0', 1);
        return;
    }
    
    // Conversion en hexadécimal
    while (addr > 0) {
        int digit = addr % 16;
        if (digit < 10)
            hex_str[i] = '0' + digit;
        else
            hex_str[i] = 'A' + (digit - 10);
        addr /= 16;
        i++;
    }
    
    // Affichage dans le bon ordre
    while (i > 0) {
        i--;
        ft_putchar_fd(hex_str[i], 1);
    }
}

static void print_hex_byte(unsigned char byte) {
    char hex_digits[] = "0123456789ABCDEF";
    ft_putchar_fd(hex_digits[byte >> 4], 1);
    ft_putchar_fd(hex_digits[byte & 0x0F], 1);
}

static void print_hex_dump(void *ptr, size_t size, size_t max_bytes) {
    unsigned char *data = (unsigned char *)ptr;
    size_t i;
    size_t bytes_to_show = size > max_bytes ? max_bytes : size;
    
    ft_putstr_fd("    Hex dump (first ", 1);
    ft_putnbr_fd(bytes_to_show, 1);
    ft_putstr_fd(" bytes): ", 1);
    
    for (i = 0; i < bytes_to_show; i++) {
        if (i % 16 == 0 && i > 0) {
            ft_putstr_fd("\n                        ", 1);
        }
        print_hex_byte(data[i]);
        ft_putchar_fd(' ', 1);
    }
    
    if (size > max_bytes) {
        ft_putstr_fd("... (", 1);
        ft_putnbr_fd(size - max_bytes, 1);
        ft_putstr_fd(" more bytes)", 1);
    }
    ft_putchar_fd('\n', 1);
}

static void print_ascii_dump(void *ptr, size_t size, size_t max_bytes) {
    unsigned char *data = (unsigned char *)ptr;
    size_t i;
    size_t bytes_to_show = size > max_bytes ? max_bytes : size;
    
    ft_putstr_fd("    ASCII dump: \"", 1);
    
    for (i = 0; i < bytes_to_show; i++) {
        if (data[i] >= 32 && data[i] <= 126) {
            ft_putchar_fd(data[i], 1);
        } else {
            ft_putchar_fd('.', 1);
        }
    }
    
    ft_putchar_fd('"', 1);
    if (size > max_bytes) {
        ft_putstr_fd("... (truncated)", 1);
    }
    ft_putchar_fd('\n', 1);
}

static void show_zone_blocks_ex(t_zone *zone) {
    t_block *block = zone->blocks;
    size_t total_zone = 0;
    int block_count = 0;
    
    while (block) {
        if (!block->is_free) {
            void *user_data = (char *)block + sizeof(t_block);
            
            ft_putstr_fd("  Block #", 1);
            ft_putnbr_fd(++block_count, 1);
            ft_putstr_fd(": ", 1);
            print_hex_address(user_data);
            ft_putstr_fd(" - ", 1);
            print_hex_address((char *)user_data + block->size - 1);
            ft_putstr_fd(" : ", 1);
            ft_putnbr_fd(block->size, 1);
            ft_putendl_fd(" bytes", 1);
            
            // Dump hexadécimal (limité aux premiers 64 octets)
            print_hex_dump(user_data, block->size, 64);
            
            // Dump ASCII (limité aux premiers 128 octets)
            print_ascii_dump(user_data, block->size, 128);
            
            total_zone += block->size;
            ft_putchar_fd('\n', 1);
        }
        block = block->next;
    }
    
    ft_putstr_fd("  Zone total: ", 1);
    ft_putnbr_fd(total_zone, 1);
    ft_putendl_fd(" bytes", 1);
}

static void show_allocation_history(void) {
    int i, start_index;
    int entries_to_show = g_history_index < HISTORY_SIZE ? g_history_index : HISTORY_SIZE;
    
    ft_putendl_fd("\n=== ALLOCATION HISTORY ===", 1);
    ft_putstr_fd("Showing last ", 1);
    ft_putnbr_fd(entries_to_show, 1);
    ft_putendl_fd(" operations:", 1);
    
    // Détermine l'index de départ pour afficher les dernières entrées
    if (g_history_index < HISTORY_SIZE) {
        start_index = 0;
    } else {
        start_index = g_history_index % HISTORY_SIZE;
    }
    
    for (i = 0; i < entries_to_show; i++) {
        int index = (start_index + i) % HISTORY_SIZE;
        t_alloc_history *entry = &g_alloc_history[index];
        
        ft_putstr_fd("[", 1);
        ft_putnbr_fd(entry->timestamp, 1);
        ft_putstr_fd("] ", 1);
        
        switch (entry->operation) {
            case 'M':
                ft_putstr_fd("MALLOC(", 1);
                ft_putnbr_fd(entry->size, 1);
                ft_putstr_fd(") -> ", 1);
                print_hex_address(entry->ptr);
                break;
            case 'F':
                ft_putstr_fd("FREE(", 1);
                print_hex_address(entry->ptr);
                ft_putstr_fd(")", 1);
                break;
            case 'R':
                ft_putstr_fd("REALLOC(", 1);
                print_hex_address(entry->ptr);
                ft_putstr_fd(", ", 1);
                ft_putnbr_fd(entry->size, 1);
                ft_putstr_fd(")", 1);
                break;
        }
        ft_putchar_fd('\n', 1);
    }
}

static unsigned int get_timestamp(void) {
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return (unsigned int)(tv.tv_sec % 10000); // Utilise les 4 derniers chiffres des secondes
}

void add_to_history(void *ptr, size_t size, char operation) {
    int index = g_history_index % HISTORY_SIZE;
    g_alloc_history[index].ptr = ptr;
    g_alloc_history[index].size = size;
    g_alloc_history[index].operation = operation;
    g_alloc_history[index].timestamp = get_timestamp();
    g_history_index++;
}

extern t_zone *g_zones[3]; // TINY, SMALL, LARGE

void show_alloc_mem_ex(void) {
    size_t total_allocated = 0;
    int zone_count = 0;
    
    ft_putendl_fd("\n=== EXTENDED MEMORY ALLOCATION MAP ===", 1);
    
    // Parcourir les trois types de zones
    for (int type = 0; type < 3; type++) {
        t_zone *current_zone = g_zones[type];
        
        while (current_zone) {
            zone_count++;
            ft_putstr_fd("\n--- ZONE #", 1);
            ft_putnbr_fd(zone_count, 1);
            ft_putstr_fd(" (", 1);
            
            switch (type) {
                case TINY:
                    ft_putstr_fd("TINY", 1);
                    break;
                case SMALL:
                    ft_putstr_fd("SMALL", 1);
                    break;
                case LARGE:
                    ft_putstr_fd("LARGE", 1);
                    break;
            }
            
            ft_putstr_fd(") : ", 1);
            print_hex_address(current_zone->start);
            ft_putendl_fd(" ---", 1);
            
            if (current_zone->blocks) {
                show_zone_blocks_ex(current_zone);
            } else {
                ft_putendl_fd("  No allocated blocks in this zone", 1);
            }
            
            current_zone = current_zone->next;
        }
    }
    
    // Calculer le total
    for (int type = 0; type < 3; type++) {
        t_zone *current_zone = g_zones[type];
        while (current_zone) {
            t_block *block = current_zone->blocks;
            while (block) {
                if (!block->is_free) {
                    total_allocated += block->size;
                }
                block = block->next;
            }
            current_zone = current_zone->next;
        }
    }
    
    ft_putstr_fd("\nTotal allocated: ", 1);
    ft_putnbr_fd(total_allocated, 1);
    ft_putendl_fd(" bytes", 1);
    
    ft_putstr_fd("Total zones: ", 1);
    ft_putnbr_fd(zone_count, 1);
    ft_putendl_fd("", 1);
    
    // Afficher l'historique des allocations
    show_allocation_history();
    
    ft_putendl_fd("\n=== END OF EXTENDED MEMORY MAP ===\n", 1);
}
