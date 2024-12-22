#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <semaphore.h>
#include <sys/time.h>
#include <time.h>


#define USER_COUNT 10
#define ALLOWED_USER 5

sem_t semaphore;

void* sign_in(void* arg) {
    int user_id = *((int*)arg);
    printf("[WAITING] User: %i\n", user_id);
    sem_wait(&semaphore);
    printf("  [SIGNIN] User: %i\n", user_id);
    int sleep_count = rand() % 5;
    printf("    [SLEEP] User: %i, seconds: %i\n", user_id, sleep_count);
    sleep(sleep_count);
    sem_post(&semaphore);
    printf("[SIGNOUT] User: %i\n", user_id);
    return NULL;
}


int main() {
    sem_init(&semaphore, 0, ALLOWED_USER);
    pthread_t threads[USER_COUNT];
    int ids[USER_COUNT];

    for (int i = 0; i < USER_COUNT; i++) {
        ids[i] = i;
        pthread_create(&threads[i], NULL, sign_in, (void*)&ids[i]);
    }

    for (int i = 0; i < USER_COUNT; i++) {
        pthread_join(threads[i], NULL);
    }

    return 0;
}
