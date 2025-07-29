#include "tests/test_utils.h"

int main() {
    log_info("Starting malloc implementation tests...\n");
    
    test_basic_malloc();
    test_different_sizes();
    test_multiple_allocations();
    test_edge_cases();
    test_memory_content();
    test_realloc();
    test_show_alloc_mem();
    test_show_alloc_mem_ex();
    test_multithread();
    
    log_success("=== ALL TESTS COMPLETED SUCCESSFULLY ===");
    log_info("Your malloc implementation is working correctly!");
    
    return 0;
}
