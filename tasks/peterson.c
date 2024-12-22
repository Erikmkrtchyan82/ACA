#include <pthread.h>
#include <stdio.h>

int x = 5;
bool T1 = false;
bool T2 = false;
int fav = 0;

void* increment(void* arg) {
    T1 = true;
    fav = 1;
    while (T2 && fav == 1);
        x++;
    T1 = false;
    return NULL;
}

void* decrement(void* arg) {
    T2 = true;
    fav = 2;
    while (T1 && fav == 2);
        x--;
    T2 = false;
    return NULL;
}

int main() {
    pthread_t tid1, tid2;

    for(int i = 0; i < 10; i++)
    {
        // Create threads
        pthread_create(&tid1, NULL, increment, NULL);
        pthread_create(&tid2, NULL, decrement, NULL);

        // Wait for threads to complete
        pthread_join(tid1, NULL);
        pthread_join(tid2, NULL);

        // Print the final value of x
        printf("Final value of x: %d\n", x);
    }

    return 0;
}
