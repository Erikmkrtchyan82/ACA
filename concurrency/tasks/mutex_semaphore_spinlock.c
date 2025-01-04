#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <semaphore.h>
#include <sys/time.h>
#include <time.h>


#define NUM_ITERATIONS 100000000
#define NUM_THREADS 2

// Shared counter
volatile int counter = 0;

pthread_mutex_t mutex;
pthread_spinlock_t spinlock;
sem_t semaphore;


// Function for incrementing the counter (Critical Section)
void *increment_counter(void *arg) {
    for (int i = 0; i < NUM_ITERATIONS / NUM_THREADS; i++) {
        // Critical Section: Increment the shared counter
	    // Use all 3 mechanisms to sync this section. Keep two of them commented out.
        
        {
            pthread_spin_lock(&spinlock);
            counter++;
            pthread_spin_unlock(&spinlock);
        }
        {
            // sem_wait(&semaphore);
            // counter++;
            // sem_post(&semaphore);
        }
        {
            // pthread_mutex_lock(&mutex);
            // counter++;
            // pthread_mutex_unlock(&mutex);
        }
    }
    return NULL;
}


int main() {
    sem_init(&semaphore, 0, 1); // initialize semaphore with value 1

    pthread_t threads[NUM_THREADS];
    struct timeval start, end;
    gettimeofday(&start, NULL);

    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_create(&threads[i], NULL, increment_counter, NULL);
    }

    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }

    gettimeofday(&end, NULL);

    // Calculate execution time in milliseconds
    double execution_time = (end.tv_sec - start.tv_sec) * 1000.0;
    execution_time += (end.tv_usec - start.tv_usec) / 1000.0;

    // Print the final value of the counter
    printf("Final Counter: %d\n", counter);
    printf("Time: %.2f ms\n", execution_time);
    return 0;
}
