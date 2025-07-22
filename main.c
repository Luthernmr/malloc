#include <stdio.h>
#include <string.h>
#include <assert.h>
#include "includes/malloc.h"

void test_basic_malloc() {
    printf("=== Test Basic Malloc ===\n");
    
    // Test allocation simple
    void *ptr1 = malloc(100);
    printf("malloc(100): %s\n", ptr1 ? "SUCCESS" : "FAILED");
    assert(ptr1 != NULL);
    
    // Test écriture dans la mémoire allouée
    strcpy((char*)ptr1, "Hello, World!");
    printf("Writing to allocated memory: %s\n", (char*)ptr1);
    
    // Test allocation de taille 0
    void *ptr2 = malloc(0);
    printf("malloc(0): %s\n", ptr2 == NULL ? "SUCCESS (returned NULL)" : "FAILED");
    
    printf("Basic malloc tests: PASSED\n\n");
}

void test_different_sizes() {
    printf("=== Test Different Sizes ===\n");
    
    // Test TINY (< 512 bytes)
    void *tiny = malloc(256);
    printf("malloc(256 - TINY): %s\n", tiny ? "SUCCESS" : "FAILED");
    assert(tiny != NULL);
    
    // Test SMALL (< 4096 bytes)
    void *small = malloc(2048);
    printf("malloc(2048 - SMALL): %s\n", small ? "SUCCESS" : "FAILED");
    assert(small != NULL);
    
    // Test LARGE (>= 4096 bytes)
    void *large = malloc(8192);
    printf("malloc(8192 - LARGE): %s\n", large ? "SUCCESS" : "FAILED");
    assert(large != NULL);
    
    printf("Different sizes tests: PASSED\n\n");
}

void test_multiple_allocations() {
    printf("=== Test Multiple Allocations ===\n");
    
    void *ptrs[10];
    int i;
    
    // Allouer plusieurs blocs
    for (i = 0; i < 10; i++) {
        ptrs[i] = malloc(64 + i * 10);
        printf("malloc(%d): %s\n", 64 + i * 10, ptrs[i] ? "SUCCESS" : "FAILED");
        assert(ptrs[i] != NULL);
        
        // Écrire quelque chose dans chaque bloc
        sprintf((char*)ptrs[i], "Block %d", i);
    }
    
    // Vérifier que les données sont toujours là
    for (i = 0; i < 10; i++) {
        printf("Block %d contains: %s\n", i, (char*)ptrs[i]);
    }
    
    printf("Multiple allocations tests: PASSED\n\n");
}

void test_edge_cases() {
    printf("=== Test Edge Cases ===\n");
    
    // Test allocation très petite
    void *ptr1 = malloc(1);
    printf("malloc(1): %s\n", ptr1 ? "SUCCESS" : "FAILED");
    assert(ptr1 != NULL);
    
    // Test allocation exactement à la limite TINY
    void *ptr2 = malloc(512);
    printf("malloc(512): %s\n", ptr2 ? "SUCCESS" : "FAILED");
    assert(ptr2 != NULL);
    
    // Test allocation exactement à la limite SMALL
    void *ptr3 = malloc(4096);
    printf("malloc(4096): %s\n", ptr3 ? "SUCCESS" : "FAILED");
    assert(ptr3 != NULL);
    
    // Test allocation très grande
    void *ptr4 = malloc(1024 * 1024); // 1MB
    printf("malloc(1MB): %s\n", ptr4 ? "SUCCESS" : "FAILED");
    assert(ptr4 != NULL);
    
    printf("Edge cases tests: PASSED\n\n");
}

void test_memory_content() {
    printf("=== Test Memory Content Integrity ===\n");
    
    char *ptr1 = (char*)malloc(100);
    char *ptr2 = (char*)malloc(200);
    
    assert(ptr1 != NULL && ptr2 != NULL);
    
    // Remplir avec des données de test
    strcpy(ptr1, "First allocation");
    strcpy(ptr2, "Second allocation with more data");
    
    // Vérifier que les données ne se chevauchent pas
    printf("ptr1 content: %s\n", ptr1);
    printf("ptr2 content: %s\n", ptr2);
    
    assert(strcmp(ptr1, "First allocation") == 0);
    assert(strcmp(ptr2, "Second allocation with more data") == 0);
    
    printf("Memory content integrity: PASSED\n\n");
}

int main() {
    printf("Starting malloc tests...\n\n");
    
    test_basic_malloc();
    test_different_sizes();
    test_multiple_allocations();
    test_edge_cases();
    test_memory_content();
    
    printf("=== ALL TESTS PASSED ===\n");
    printf("Your malloc implementation seems to be working correctly!\n");
    
    return 0;
}
