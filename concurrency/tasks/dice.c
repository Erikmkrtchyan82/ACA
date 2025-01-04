#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <semaphore.h>
#include <sys/time.h>
#include <time.h>

#define GAMERS 5
#define NUM_ROUNDS 3

pthread_barrier_t ready_barrier;
pthread_barrier_t next_round_ready_barrier;
pthread_mutex_t mutex;

bool end = false;
int arr[GAMERS];

void* dice(void* arg) {
    while (1) {
        pthread_mutex_lock(&mutex);
        if (end) {
            pthread_mutex_unlock(&mutex);
            break;
        }
        pthread_mutex_unlock(&mutex);
        int id = *((int*)arg);
        arr[id] = rand() % 6 + 1;
        pthread_barrier_wait(&ready_barrier);
        pthread_barrier_wait(&next_round_ready_barrier);
    }
    return NULL;
}

int main() {
    pthread_t threads[GAMERS];
    int ids[GAMERS];

    // +1 for main thread
    pthread_barrier_init(&ready_barrier, NULL, GAMERS+1);
    pthread_barrier_init(&next_round_ready_barrier, NULL, GAMERS+1);
    pthread_mutex_init(&mutex, NULL);

    for (int i = 0; i < GAMERS; i++) {
        ids[i] = i;
        pthread_create(&threads[i], NULL, dice, &ids[i]);
    }

    for (int i = 0; i < NUM_ROUNDS; i++) {
        pthread_barrier_wait(&ready_barrier);
        for (int i = 0; i < GAMERS; i++) {
            printf("Gamer %d: %d\n", i, arr[i]);
        }

        int max = arr[0];
        int max_id = 0;
        for (int i = 1; i < GAMERS; i++) {
            if (arr[i] > max) {
                max = arr[i];
                max_id = i;
            }
        }
        printf("Winner is %d (%d)\n", max_id, max);

        if (i == NUM_ROUNDS-1) {
            pthread_mutex_lock(&mutex);
            end = true;
            pthread_mutex_unlock(&mutex);
        }

        pthread_barrier_wait(&next_round_ready_barrier);
    }

    for (int i = 0; i < GAMERS; i++) {
        pthread_join(threads[i], NULL);
    }

    pthread_barrier_destroy(&ready_barrier);
    pthread_barrier_destroy(&next_round_ready_barrier);
    pthread_mutex_destroy(&mutex);
    return 0;
}
