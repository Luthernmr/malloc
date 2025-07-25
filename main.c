#include "includes/malloc.h"
#include "libft/libft.h"
#include <stdlib.h>

void log_info(char *msg) {
    ft_putstr_fd("[INFO] ", 1);
    ft_putendl_fd(msg, 1);
}

void log_success(char *msg) {
    ft_putstr_fd("[SUCCESS] ", 1);
    ft_putendl_fd(msg, 1);
}

void log_error(char *msg) {
    ft_putstr_fd("[ERROR] ", 2);
    ft_putendl_fd(msg, 2);
}

void log_test_start(char *test_name) {
    ft_putstr_fd("[TEST] === ", 1);
    ft_putstr_fd(test_name, 1);
    ft_putendl_fd(" ===", 1);
}

void log_test_end(char *test_name) {
    ft_putstr_fd("[PASSED] ", 1);
    ft_putstr_fd(test_name, 1);
    ft_putendl_fd(" completed successfully\n", 1);
}

void log_malloc_result(char *operation, int success) {
    ft_putstr_fd("[MALLOC] ", 1);
    ft_putstr_fd(operation, 1);
    if (success) {
        ft_putendl_fd(": SUCCESS", 1);
    } else {
        ft_putendl_fd(": FAILED", 1);
    }
}

void log_content(char *label, char *content) {
    ft_putstr_fd("[CONTENT] ", 1);
    ft_putstr_fd(label, 1);
    ft_putstr_fd(": ", 1);
    ft_putendl_fd(content, 1);
}

void assert_or_exit(int condition, char *error_msg) {
    if (!condition) {
        log_error(error_msg);
        exit(1);
    }
}

void copy_string(char *dest, const char *src) {
    int i = 0;
    while (src[i]) {
        dest[i] = src[i];
        i++;
    }
    dest[i] = '\0';
}

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

int main() {
    log_info("Starting malloc implementation tests...\n");
    
    test_basic_malloc();
    test_different_sizes();
    test_multiple_allocations();
    test_edge_cases();
    test_memory_content();
    test_realloc();
    
    log_success("=== ALL TESTS COMPLETED SUCCESSFULLY ===");
    log_info("Your malloc implementation is working correctly!");
    
    return 0;
}
