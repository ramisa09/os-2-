#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct Process {
    int pid;
    int arrival;
    int burst;
    int completion = 0;
    int turnaround = 0;
    int waiting = 0;
    bool done = false;
};

int main() {
    int n;
    cout << "Enter number of processes: ";
    cin >> n;

    vector<Process> p(n);

    // Input
    for (int i = 0; i < n; i++) {
        p[i].pid = i + 1;
        cout << "Enter Arrival Time for Process " << p[i].pid << ": ";
        cin >> p[i].arrival;
        cout << "Enter Burst Time for Process " << p[i].pid << ": ";
        cin >> p[i].burst;
    }

    int completed = 0, currentTime = 0;
    float totalTAT = 0, totalWT = 0;

    while (completed < n) {
        // Find the next shortest job available
        int idx = -1, minBurst = 1e9;
        for (int i = 0; i < n; i++) {
            if (!p[i].done && p[i].arrival <= currentTime && p[i].burst < minBurst) {
                minBurst = p[i].burst;
                idx = i;
            }
        }

        if (idx == -1) {
            currentTime++; // No process has arrived yet
            continue;
        }

        // Execute the selected process
        p[idx].completion = currentTime + p[idx].burst;
        p[idx].turnaround = p[idx].completion - p[idx].arrival;
        p[idx].waiting = p[idx].turnaround - p[idx].burst;
        p[idx].done = true;

        currentTime = p[idx].completion;

        totalTAT += p[idx].turnaround;
        totalWT += p[idx].waiting;

        completed++;
    }

    // Output
     cout << "\nPID\tAT\tBT\tCT\tTAT\tWT\n";
    for (int i = 0; i < n; i++) {
        cout << p[i].pid << "\t" << p[i].arrival << "\t" << p[i].burst << "\t"
             << p[i].completion << "\t" << p[i].turnaround << "\t" << p[i].waiting << endl;
    }

    cout << "\nAverage Turnaround Time: " << totalTAT / n;
    cout << "Average Waiting Time: " << totalWT / n << endl;

    return 0;
}
