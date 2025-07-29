#include "test_utils.h"

void test_memory_content() {
    log_test_start("Memory Content Integrity");
    
    char *ptr1 = (char*)malloc(100);
    char *ptr2 = (char*)malloc(200);
    
    assert_or_exit(ptr1 != NULL && ptr2 != NULL, "allocation failed");
    
    copy_string(ptr1, "First allocation");
    copy_string(ptr2, "Second allocation with more data");
    
    log_content("ptr1", ptr1);
    log_content("ptr2", ptr2);
    
    assert_or_exit(ft_strncmp(ptr1, "First allocation", 16) == 0, "ptr1 content mismatch");
    assert_or_exit(ft_strncmp(ptr2, "Second allocation with more data", 32) == 0, "ptr2 content mismatch");
    log_success("Memory content integrity verified");
    
    free(ptr1);
    free(ptr2);
    log_info("Memory freed successfully");
    
    log_test_end("Memory Content Integrity");
}
