#include "test_utils.h"

void test_show_alloc_mem() {
    log_test_start("Show Alloc Mem");
    
    void *ptr1 = malloc(100);
    void *ptr2 = malloc(2000);
    void *ptr3 = malloc(10000);
    
    log_info("Calling show_alloc_mem():");
    show_alloc_mem();
    
    free(ptr1);
    free(ptr2);
    free(ptr3);
    
    log_test_end("Show Alloc Mem");
}
