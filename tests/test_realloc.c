#include "test_utils.h"

void test_realloc() {
    log_test_start("Realloc");
    
    void *ptr1 = realloc(NULL, 100);
    log_malloc_result("realloc(NULL, 100)", ptr1 != NULL);
    assert_or_exit(ptr1 != NULL, "realloc(NULL, 100) failed");
    copy_string((char*)ptr1, "Initial data");
    log_content("Realloc content", (char*)ptr1);
    
    if (ptr1) {
        free(ptr1);
        log_info("Realloc memory freed");
    }
    
    void *ptr2 = malloc(50);
    assert_or_exit(ptr2 != NULL, "malloc(50) failed");
    copy_string((char*)ptr2, "Test");
    void *ptr2_realloc = realloc(ptr2, 0);
    log_malloc_result("realloc(ptr, 0)", ptr2_realloc == NULL);
    
    log_test_end("Realloc");
}
