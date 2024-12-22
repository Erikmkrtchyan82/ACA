#include <stdio.h>
#include <pthread.h>

#define NUM_QUEUE 20
bool entering[NUM_QUEUE] = {false};
int number[NUM_QUEUE] = {0};
int x = 0;

int max(int* arr, int size) {
    int max = arr[0];
    for (int i = 1; i < size; i++) {
        if (arr[i] > max) {
            max = arr[i];
        }
    }
    return max;
}

void bakery_lock(int index) {
    entering[index] = true;
    number[index] = 1 + max(number, NUM_QUEUE);
    entering[index] = false;

    for (int i = 0; i < NUM_QUEUE; i++) {
        while (entering[i]);
        while (number[i] != 0 && (number[i] < number[index] || (number[i] == number[index] && i < index)));
    }
}

void bakery_unlock(int index) {
    number[index] = 0;
}

void* increment(void* arg)
{
	int* i = (int*)arg;
	bakery_lock(*i);
    printf("Thread %d is incrementing x\n", *i);
	x++;
	bakery_unlock(*i);
    printf("Thread %d is done incrementing x\n", *i);
	return NULL;
}

void* decrement(void* arg)
{
	int* i = (int*)arg;
	bakery_lock(*i);
    printf("Thread %d is decrementing x\n", *i);
	x--;
	bakery_unlock(*i);
    printf("Thread %d is done decrementing x\n", *i);
	return NULL;
}


int main() {
    pthread_t threads[NUM_QUEUE];
    int ids[NUM_QUEUE];

    printf("Initial value of x: %d\n", x);

    for (int i = 0; i < NUM_QUEUE; i++) {
        ids[i] = i;
        pthread_create(&threads[i], NULL, increment, (void*)&ids[i]);
        pthread_create(&threads[i], NULL, decrement, (void*)&ids[i]);
    }

    for (int i = 0; i < NUM_QUEUE; i++) {
        pthread_join(threads[i], NULL);
    }

    printf("Final value of x: %d\n", x);

    return 0;
}
