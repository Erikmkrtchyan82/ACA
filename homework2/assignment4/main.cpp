#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>

void* sqr(void* args) {
    int num = *((int*)args);
    printf("Square of %i is %i\n", num, num * num);
    return NULL;
}

int main() {
    pthread_t threads[5];
    int nums[5] = {1, 2, 3, 4, 5};

    for (int i = 0; i < 5; i++) {
        pthread_create(&threads[i], NULL, sqr, (void*)&nums[i]);
    }

    for (int i = 0; i < 5; i++) {
        pthread_join(threads[i], NULL);
    }

    return 0;
}
