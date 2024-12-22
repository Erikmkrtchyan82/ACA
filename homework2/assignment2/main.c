#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>

typedef struct {
    int* arr;
    int start;
    int end;
} sum_arr_data_t;

void* sum_arr(void* args) {
    sum_arr_data_t* data = (sum_arr_data_t*)args;
    int sum = 0;
    for (int i = data->start; i < data->end; i++) {
        sum += data->arr[i];
    }

    printf("Sum: %i\n", sum);
    return NULL;
}

int main() {
    int size = 10; 
    int *a = (int*)malloc(size * sizeof(int));

    for (int i = 0; i < size; i++) {
        a[i] = rand() % 100;
    }

    pthread_t thread1, thread2;
    int s1 = 0;
    int e1 = size / 2;
    int s2 = size / 2;
    int e2 = size;

    sum_arr_data_t data1 = {a, s1, e1};
    sum_arr_data_t data2 = {a, s2, e2};

    pthread_create(&thread1, NULL, sum_arr, (void*)&data1);
    pthread_create(&thread2, NULL, sum_arr, (void*)&data2);

    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);

    free(a);
    return 0;
}
