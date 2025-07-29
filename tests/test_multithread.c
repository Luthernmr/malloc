#include "test_utils.h"

typedef struct {
    int thread_id;
    int num_allocs;
} thread_data_t;

void *thread_malloc_test(void *arg) {
    thread_data_t *data = (thread_data_t *)arg;
    void *ptrs[100];
    int i;
    
    for (i = 0; i < data->num_allocs && i < 100; i++) {
        ptrs[i] = malloc(64 + i * 2);
        if (ptrs[i]) {
            copy_string((char*)ptrs[i], "Thread data");
        }
    }
    
    for (i = 0; i < data->num_allocs && i < 100; i++) {
        if (ptrs[i]) {
            free(ptrs[i]);
        }
    }
    
    return NULL;
}

void test_multithread() {
    log_test_start("Multithread");
    
    const int num_threads = 4;
    pthread_t threads[4];
    thread_data_t thread_data[4];
    int i;
    
    log_info("Creating 4 threads with concurrent malloc/free operations");
    
    for (i = 0; i < num_threads; i++) {
        thread_data[i].thread_id = i;
        thread_data[i].num_allocs = 50;
        
        if (pthread_create(&threads[i], NULL, thread_malloc_test, &thread_data[i]) != 0) {
            log_error("Failed to create thread");
            assert_or_exit(0, "pthread_create failed");
        }
    }
    
    for (i = 0; i < num_threads; i++) {
        if (pthread_join(threads[i], NULL) != 0) {
            log_error("Failed to join thread");
            assert_or_exit(0, "pthread_join failed");
        }
    }
    
    log_success("All threads completed successfully");
    log_test_end("Multithread");
}
