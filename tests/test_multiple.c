#include "test_utils.h"

void create_block_name(char *dest, int i) {
    copy_string(dest, "Block ");
    dest[6] = '0' + i;
    dest[7] = '\0';
}

void test_multiple_allocations() {
    log_test_start("Multiple Allocations");
    
    void *ptrs[10];
    int i;
    
    for (i = 0; i < 10; i++) {
        ptrs[i] = malloc(64 + i * 10);
        log_malloc_result("malloc block", ptrs[i] != NULL);
        assert_or_exit(ptrs[i] != NULL, "allocation failed");
        
        create_block_name((char*)ptrs[i], i);
    }
    
    for (i = 0; i < 10; i++) {
        log_content("Block content", (char*)ptrs[i]);
    }
    
    for (i = 0; i < 10; i++) {
        free(ptrs[i]);
    }
    log_info("All blocks freed successfully");
    
    log_test_end("Multiple Allocations");
}
