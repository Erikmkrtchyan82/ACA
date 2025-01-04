#include <stdio.h>
#include <thread>
#include <semaphore>

#define PHILOSOPHER_COUNT 5

enum class State {
    THINKING,
    HUNGRY,
    EATING
};

std::array<std::binary_semaphore, PHILOSOPHER_COUNT> forks{
    std::binary_semaphore(0), 
    std::binary_semaphore(0), 
    std::binary_semaphore(0), 
    std::binary_semaphore(0), 
    std::binary_semaphore(0)
};
std::array<State, PHILOSOPHER_COUNT> states{
    State::THINKING, 
    State::THINKING, 
    State::THINKING, 
    State::THINKING, 
    State::THINKING
};
std::mutex mutex;

void eat() {
    std::this_thread::sleep_for(std::chrono::seconds(rand() % 10));
}

void think() {
    std::this_thread::sleep_for(std::chrono::seconds(rand() % 10));
}

int next(int i) {
    return (i + 1 + PHILOSOPHER_COUNT) % PHILOSOPHER_COUNT;
}

int prev(int i) {
    return (i - 1 + PHILOSOPHER_COUNT) % PHILOSOPHER_COUNT;
}

void test_ping(int i) {
    if (states[i] == State::HUNGRY && 
        states[next(i)] != State::EATING && 
        states[prev(i)] != State::EATING) {

        states[i] = State::EATING;
        forks[i].release();
    }
}

void take_forks(int i) {
    mutex.lock();
    states[i] = State::HUNGRY;
    test_ping(i);
    mutex.unlock();
    forks[i].acquire();
}

void put_forks(int i) {
    mutex.lock();
    states[i] = State::THINKING;
    test_ping(next(i));
    test_ping(prev(i));
    mutex.unlock();
}

void philosopher(int i) {
    while (true) {
        think();
        take_forks(i);
        printf("Philosopher %d is eating\n", i);
        eat();
        printf("Philosopher %d is done eating\n", i);
        put_forks(i);
    }
}

int main() {
    std::array<std::thread, PHILOSOPHER_COUNT> threads;
    for (int i = 0; i < PHILOSOPHER_COUNT; i++) {
        threads[i] = std::thread(philosopher, i);
    }
    for (int i = 0; i < PHILOSOPHER_COUNT; i++) {
        threads[i].join();
    }
    return 0;
}
