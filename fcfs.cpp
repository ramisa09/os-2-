#include <iostream>   // ইনপুট ও আউটপুটের জন্য
#include <vector>     // vector ডেটা স্ট্রাকচার ব্যবহারের জন্য
#include <algorithm>  // sort ফাংশন ব্যবহারের জন্য
using namespace std;  // std namespace ব্যবহার করছি যাতে বারবার std:: না লিখতে হয়

// Process struct তৈরি করছি যাতে প্রতিটি প্রসেসের তথ্য সংরক্ষণ করা যায়
struct Process {
    int pid;         // প্রসেস আইডি
    int arrival;     // আরাইভাল টাইম
    int burst;       // বার্স্ট টাইম
    int completion;  // কমপ্লিশন টাইম
    int turnaround;  // টার্নঅ্যারাউন্ড টাইম
    int waiting;     // ওয়েটিং টাইম
};

int main() {
    int n;
    cout << "Enter number of processes: ";
    cin >> n;  // ইউজার থেকে প্রসেসের সংখ্যা নিচ্ছে

    vector<Process> p(n);  // n সংখ্যক প্রসেসের জন্য vector তৈরি

    // প্রতিটি প্রসেসের জন্য ইনপুট নিচ্ছি
    for (int i = 0; i < n; i++) {
        p[i].pid = i + 1;  // PID = 1, 2, 3,...
        cout << "Enter Arrival Time for Process " << p[i].pid << ": ";
        cin >> p[i].arrival;  // আরাইভাল টাইম ইনপুট
        cout << "Enter Burst Time for Process " << p[i].pid << ": ";
        cin >> p[i].burst;    // বার্স্ট টাইম ইনপুট
    }

    // আরাইভাল টাইম অনুযায়ী প্রসেস sort করছি (FCFS অনুযায়ী)
    sort(p.begin(), p.end(), [](Process a, Process b) {
        return a.arrival < b.arrival;
    });

    // সময় গণনার জন্য ভ্যারিয়েবল
    int currentTime = 0;
    float totalTAT = 0, totalWT = 0;  // মোট টার্নঅ্যারাউন্ড ও ওয়েটিং টাইম

    // প্রতিটি প্রসেসের Completion, Turnaround ও Waiting Time বের করছি
    for (int i = 0; i < n; i++) {
        if (currentTime < p[i].arrival)
            currentTime = p[i].arrival;  // প্রসেস আসার আগে যদি CPU ফাঁকা থাকে

        p[i].completion = currentTime + p[i].burst;  // Completion Time = বর্তমান সময় + বার্স্ট টাইম
        p[i].turnaround = p[i].completion - p[i].arrival;  // Turnaround Time = Completion - Arrival
        p[i].waiting = p[i].turnaround - p[i].burst;       // Waiting Time = Turnaround - Burst

        currentTime = p[i].completion;  // পরবর্তী প্রসেসের জন্য সময় আপডেট করছি

        totalTAT += p[i].turnaround;  // মোট টার্নঅ্যারাউন্ড টাইম যোগ করছি
        totalWT += p[i].waiting;      // মোট ওয়েটিং টাইম যোগ করছি
    }

    // টেবিল আকারে আউটপুট দেখাচ্ছি
    cout << "\nPID\tAT\tBT\tCT\tTAT\tWT\n";
    for (int i = 0; i < n; i++) {
        cout << p[i].pid << "\t" << p[i].arrival << "\t" << p[i].burst << "\t"
             << p[i].completion << "\t" << p[i].turnaround << "\t" << p[i].waiting << endl;
    }

    // গড় টার্নঅ্যারাউন্ড ও ওয়েটিং টাইম দেখাচ্ছি
    cout << "\nAverage Turnaround Time: " << totalTAT / n;
    cout << "\nAverage Waiting Time: " << totalWT / n << endl;

    return 0;  // প্রোগ্রামের সমাপ্তি
}
