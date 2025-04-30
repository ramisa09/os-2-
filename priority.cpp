#include <iostream>
#include <vector>
using namespace std;

struct Process {
    int pid;
    int arrival;
    int burst;
    int priority;
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

    for (int i = 0; i < n; i++) {
        p[i].pid = i + 1;
        cout << "AT BT Priority for P" << p[i].pid << ": ";
        cin >> p[i].arrival >> p[i].burst >> p[i].priority;
    }

    int time = 0, completed = 0;
    float totalTAT = 0, totalWT = 0;

    while (completed < n) {
        int idx = -1, bestPri = 1e9;
        for (int i = 0; i < n; i++) {
            if (!p[i].done && p[i].arrival <= time && p[i].priority < bestPri) {
                bestPri = p[i].priority;
                idx = i;
            }
        }

        if (idx == -1) { time++; continue; }

        p[idx].completion = time + p[idx].burst;
        p[idx].turnaround = p[idx].completion - p[idx].arrival;
        p[idx].waiting = p[idx].turnaround - p[idx].burst;
        p[idx].done = true;

        time = p[idx].completion;

        totalTAT += p[idx].turnaround;
        totalWT += p[idx].waiting;

        completed++;
    }

       cout<<"\nPID\tAT\tBT\tCT\tTAT\tWT\n";
    for(int i = 0; i < n; i++)
    {
        cout<< p[i].pid << "\t" << p[i].arrival << "\t" << p[i].burst << "\t" << p[i].completion << "\t" <<p[i].turnaround << "\t" << p[i].waiting << endl;
    }

    cout<< "\n Average Turn around Time: " << totalTAT / n;
    cout<< "\n Average Waiing Time: " << totalWT / n;

    return 0;




}
