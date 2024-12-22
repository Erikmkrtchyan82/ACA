#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>

void* print(void* args) {
    int num = *((int*)args);
    for (int i = 1; i < 6; i++) {
        printf("Thread %i: %i\n", num, i);
    }

    return NULL;
}

int main() {
    pthread_t threads[3];
    int ids[3] = {1, 2, 3};

    pthread_create(&threads[0], NULL, print, (void*)&ids[0]);
    pthread_create(&threads[1], NULL, print, (void*)&ids[1]);
    pthread_create(&threads[2], NULL, print, (void*)&ids[2]);

    for (int i = 0; i < 3; i++) {
        pthread_join(threads[i], NULL);
    }

    return 0;
}
