#include "test_utils.h"

void test_show_alloc_mem_ex() {
    log_test_start("Show Alloc Mem Extended");
    
    // Effectuer plusieurs allocations de différentes tailles
    void *ptr1 = malloc(100);
    void *ptr2 = malloc(2000);
    void *ptr3 = malloc(10000);
    void *ptr4 = malloc(50);
    
    // Écrire des données dans les pointeurs pour tester le dump
    if (ptr1) {
        copy_string((char*)ptr1, "Hello, World! This is test data for TINY allocation.");
    }
    if (ptr2) {
        copy_string((char*)ptr2, "This is a longer string for SMALL allocation testing. It contains more characters to see how the hex dump works with longer data.");
    }
    if (ptr4) {
        copy_string((char*)ptr4, "Short string for testing.");
    }
    
    // Effectuer quelques réallocations et libérations pour l'historique
    void *ptr5 = realloc(NULL, 200);
    if (ptr5) {
        copy_string((char*)ptr5, "Realloc test data");
    }
    
    free(ptr1);
    ptr1 = malloc(150);
    if (ptr1) {
        copy_string((char*)ptr1, "New allocation after free");
    }
    
    log_info("Calling show_alloc_mem_ex() - Extended memory visualization:");
    show_alloc_mem_ex();
    
    // Nettoyer
    free(ptr1);
    free(ptr2);
    free(ptr3);
    free(ptr4);
    free(ptr5);
    
    log_test_end("Show Alloc Mem Extended");
}
