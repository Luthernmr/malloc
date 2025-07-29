#include "test_utils.h"

void test_basic_malloc() {
    log_test_start("Basic Malloc");
    
    void *ptr1 = malloc(100);
    log_malloc_result("malloc(100)", ptr1 != NULL);
    assert_or_exit(ptr1 != NULL, "ptr1 allocation failed");
    
    copy_string((char*)ptr1, "Hello, World!");
    log_content("Written to memory", (char*)ptr1);
    
    void *ptr2 = malloc(0);
    log_malloc_result("malloc(0)", ptr2 == NULL);
    
    free(ptr1);
    log_info("Memory freed successfully");
    
    log_test_end("Basic Malloc");
}
