#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

#include <pthread.h>

typedef struct {
    int thread_id;
} thread_data_t;


void* func(void* arg) {
    thread_data_t* data = (thread_data_t*)arg;
    printf("Thread %i is running\n", data->thread_id);
    return NULL;
}

int main() {
    pthread_t threads[3];
    thread_data_t thread_data[3];

    for (int i = 0; i < 3; i++) {
        thread_data[i].thread_id = i;
        pthread_create(&threads[i], NULL, func, (void*)&thread_data[i]);
    }

    for (int i = 0; i < 3; i++) {
        pthread_join(threads[i], NULL);
    }

    return 0;
}
