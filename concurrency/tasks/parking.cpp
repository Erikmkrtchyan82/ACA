#include <stdio.h>
#include <thread>
#include <semaphore>

#define CAR_COUNT 30
#define PARKING_SLOTS 10
#define ENTRANCE_COUNT 2
#define EXIT_COUNT 2

std::counting_semaphore<PARKING_SLOTS> parking_sem{PARKING_SLOTS};
std::counting_semaphore<ENTRANCE_COUNT> enter_sem{ENTRANCE_COUNT};
std::counting_semaphore<EXIT_COUNT> exit_sem{EXIT_COUNT};

void park_car(int car_id) {
    printf("[WAITING] Car: %i\n", car_id);
    enter_sem.acquire();
    printf("[WAITING TO ENTER] Car: %i\n", car_id);
    parking_sem.acquire();
    printf("  [PARKED] Car: %i\n", car_id);
    enter_sem.release();
    int sleep_count = rand() % 5;
    printf("    [SLEEP] Car: %i, seconds: %i\n", car_id, sleep_count);
    sleep(sleep_count);
    printf("[WAITING TO EXIT] Car: %i\n", car_id);
    exit_sem.acquire();
    printf("[LEFT] Car: %i\n", car_id);
    parking_sem.release();
    exit_sem.release();
}

int main() {
    
    std::thread cars[CAR_COUNT];
    for (int i = 0; i < CAR_COUNT; i++) {
        cars[i] = std::thread(park_car, i);
    }

    for (int i = 0; i < CAR_COUNT; i++) {
        cars[i].join();
    }

    return 0;
}
