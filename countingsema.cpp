
#include <iostream>
#include <queue>
using namespace std;

queue<int> permits;

void init(int count) {
    while (count--) permits.push(1);
}

void wait_sem() {
    while (permits.empty()); // busy wait
    permits.pop();
}

void signal_sem() {
    permits.push(1);
}

int main() {
    init(2);

    cout << "Getting 2 permits..." << endl;
    wait_sem();
    wait_sem();
    cout << "Got 2 permits!" << endl;

    cout << "Releasing 1..." << endl;
    signal_sem();

    cout << "Getting 1 permit..." << endl;
    wait_sem();
    cout << "Got it!" << endl;

    return 0;
}
