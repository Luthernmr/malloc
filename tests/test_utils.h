#ifndef TEST_UTILS_H
#define TEST_UTILS_H

#include "../includes/malloc.h"
#include "../libft/libft.h"
#include <stdlib.h>
#include <pthread.h>

// Logging functions
void log_info(char *msg);
void log_success(char *msg);
void log_error(char *msg);
void log_test_start(char *test_name);
void log_test_end(char *test_name);
void log_malloc_result(char *operation, int success);
void log_content(char *label, char *content);

// Utility functions
void assert_or_exit(int condition, char *error_msg);
void copy_string(char *dest, const char *src);

// Test functions
void test_basic_malloc(void);
void test_different_sizes(void);
void test_multiple_allocations(void);
void test_edge_cases(void);
void test_memory_content(void);
void test_realloc(void);
void test_show_alloc_mem(void);
void test_show_alloc_mem_ex(void);
void test_multithread(void);

#endif
