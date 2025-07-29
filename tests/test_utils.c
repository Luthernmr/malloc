#include "test_utils.h"

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
