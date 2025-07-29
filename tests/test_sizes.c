#include "test_utils.h"

void test_different_sizes() {
    log_test_start("Different Sizes");
    
    void *tiny = malloc(256);
    log_malloc_result("malloc(256 - TINY)", tiny != NULL);
    assert_or_exit(tiny != NULL, "tiny allocation failed");
    
    void *small = malloc(2048);
    log_malloc_result("malloc(2048 - SMALL)", small != NULL);
    assert_or_exit(small != NULL, "small allocation failed");
    
    void *large = malloc(8192);
    log_malloc_result("malloc(8192 - LARGE)", large != NULL);
    assert_or_exit(large != NULL, "large allocation failed");
    
    free(tiny);
    free(small);
    free(large);
    log_info("All allocations freed successfully");
    
    log_test_end("Different Sizes");
}
