#include<bits/stdc++.h>
#include <thread>
#include <mutex>
#include <semaphore.h>
#include <queue>
#include <unistd.h>  // for sleep()
using namespace std;

const int BUFFER_SIZE = 5;   // Buffer size
const int MAX_ITEMS = 5;     // Maximum number of items to be produced
queue<int> buffer;           // Shared Buffer

sem_t empt_y;    // Counts empty slots
sem_t full;     // Counts full slots
sem_t mtx;    // Binary semaphore for critical section

// Producer Function
void producer(int id, int& produced_items) {
    int item = 1;
    while (produced_items < MAX_ITEMS) {
        sem_wait(&empt_y);   // Wait for empty slot
        sem_wait(&mtx);   // Wait for mutex (lock)

        // Critical Section
        buffer.push(item);
        cout << "Producer " << id << " produced item " << item << endl;
        produced_items++;

        sem_post(&mtx);   // Release mutex (unlock)
        sem_post(&full);    // Increase full slots

        item++;
        sleep(1);  // Simulate production time
    }
}

// Consumer Function
void consumer(int id, int& consumed_items) {
    while (consumed_items < MAX_ITEMS) {
        sem_wait(&full);    // Wait for full slot
        sem_wait(&mtx);   // Wait for mutex (lock)

        // Critical Section
        int item = buffer.front();
        buffer.pop();
        cout << "Consumer " << id << " consumed item " << item << endl;
        consumed_items++;

        sem_post(&mtx);   // Release mutex (unlock)
        sem_post(&empt_y);   // Increase empty slots

        sleep(2);  // Simulate consumption time
    }
}

int main() {
    int num_producers, num_consumers;
    int produced_items = 0;  // Track the number of items produced
    int consumed_items = 0;  // Track the number of items consumed

    // Ask user for number of producers and consumers
    cout << "Enter number of producers: ";
    cin >> num_producers;
    cout << "Enter number of consumers: ";
    cin >> num_consumers;

    // Initialize semaphores
    sem_init(&empt_y, 0, BUFFER_SIZE);  // Initially buffer has all empty slots
    sem_init(&full, 0, 0);             // Initially buffer has no full slots
    sem_init(&mtx, 0, 1);            // Binary semaphore for mutual exclusion

    vector<thread> producers;
    vector<thread> consumers;

    // Creating Producer Threads
    for (int i = 0; i < num_producers; i++)
    producers.push_back(thread(producer, i + 1, ref(produced_items)));


    // Creating Consumer Threads
    for (int i = 0; i < num_consumers; i++)
    consumers.push_back(thread(consumer, i + 1, ref(consumed_items)));


    // Joining all threads
    for (auto& t : producers)t.join();
    for (auto& t : consumers)t.join();

    // Destroy semaphores after use
    sem_destroy(&empt_y);
    sem_destroy(&full);
    sem_destroy(&mtx);

    return 0;
}
