#include "test_utils.h"

void test_edge_cases() {
    log_test_start("Edge Cases");
    
    void *ptr1 = malloc(1);
    log_malloc_result("malloc(1)", ptr1 != NULL);
    assert_or_exit(ptr1 != NULL, "ptr1 allocation failed");
    
    void *ptr2 = malloc(512);
    log_malloc_result("malloc(512)", ptr2 != NULL);
    assert_or_exit(ptr2 != NULL, "ptr2 allocation failed");
    
    void *ptr3 = malloc(4096);
    log_malloc_result("malloc(4096)", ptr3 != NULL);
    assert_or_exit(ptr3 != NULL, "ptr3 allocation failed");
    
    void *ptr4 = malloc(1024 * 1024);
    log_malloc_result("malloc(1MB)", ptr4 != NULL);
    assert_or_exit(ptr4 != NULL, "ptr4 allocation failed");
    
    free(ptr1);
    free(ptr2);
    free(ptr3);
    free(ptr4);
    log_info("All edge case allocations freed successfully");
    
    log_test_end("Edge Cases");
}
