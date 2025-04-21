#include <bits/stdc++.h>
#include <semaphore.h>
using namespace std;

int read_count = 0;
mutex print_mutex;  // For clean output only
sem_t rw_mutex;     // Writer lock
sem_t queue_mutex;  // For fair order
sem_t mtx;          // Semaphore instead of mutex for read_count

void reader(int id, int read_time) {
    sem_wait(&queue_mutex);  // Wait in queue

    sem_wait(&mtx);  // Lock read_count update
    read_count++;
    if (read_count == 1)
        sem_wait(&rw_mutex);  // First reader locks writer
    sem_post(&mtx);  // Unlock read_count update

    sem_post(&queue_mutex);  // Let next thread enter queue

    {
        lock_guard<mutex> lock(print_mutex);
        cout << "Reader " << id << " is reading..." << endl;
    }

    this_thread::sleep_for(chrono::seconds(read_time));

    {
        lock_guard<mutex> lock(print_mutex);
        cout << "Reader " << id << " finished reading." << endl;
    }

    sem_wait(&mtx);  // Lock read_count update
    read_count--;
    if (read_count == 0)
        sem_post(&rw_mutex);  // Last reader unlocks writer
    sem_post(&mtx);  // Unlock read_count update
}

void writer(int id, int write_time) {
    sem_wait(&queue_mutex);  // Wait in queue
    sem_wait(&rw_mutex);     // Lock for writing
    sem_post(&queue_mutex);  // Let next thread enter queue

    {
        lock_guard<mutex> lock(print_mutex);
        cout << "Writer " << id << " is writing..." << endl;
    }

    this_thread::sleep_for(chrono::seconds(write_time));

    {
        lock_guard<mutex> lock(print_mutex);
        cout << "Writer " << id << " finished writing." << endl;
    }

    sem_post(&rw_mutex);  // Unlock writer
}

int main() {
    int num_readers, num_writers;
    cout << "Enter number of readers: ";
    cin >> num_readers;
    cout << "Enter number of writers: ";
    cin >> num_writers;

    sem_init(&rw_mutex, 0, 1);
    sem_init(&queue_mutex, 0, 1);
    sem_init(&mtx, 0, 1);  // Semaphore initialized for read_count critical section

    vector<thread> readers, writers;

    for (int i = 1; i <= num_readers; i++)
        readers.push_back(thread(reader, i, 2));

    for (int i = 1; i <= num_writers; i++)
        writers.push_back(thread(writer, i, 3));

    for (auto &r : readers) r.join();
    for (auto &w : writers) w.join();

    sem_destroy(&rw_mutex);
    sem_destroy(&queue_mutex);
    sem_destroy(&mtx);
}
