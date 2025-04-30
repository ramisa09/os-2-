#include<bits/stdc++.h>
using namespace std;

void Best_Fit(int n, int block[], int m, int process[]) {
    int allocation[m];
    for (int i = 0; i < m; i++) {
        int bestIdx = -1;
        for (int j = 0; j < n; j++) {
            if (block[j] >= process[i]) {
                if (bestIdx == -1 || block[j] < block[bestIdx])
                    bestIdx = j;
            }
        }

        if (bestIdx != -1) {
            allocation[i] = bestIdx + 1;
            block[bestIdx] -= process[i];
        }
        else {
            allocation[i] = -1;
        }
    }

    int extra = 0;
    for (int i = 0; i < n; i++) {
        extra += block[i];
    }

    cout << "External Fragmentation is: " << extra;
    cout << "\nBest Fit Algorithm\n";
    cout << "PID\tProcess Size\tBlock NO.\n";

    for (int i = 0; i < m; i++) {
        cout << i + 1 << "\t" << process[i] << "\t\t";
        if (allocation[i] == -1) {
            int total_free = 0;
            for (int k = 0; k < n; k++) total_free += block[k];
            if (total_free >= process[i])
                cout << "Not Allocation (External Fragmentation)\n";
            else
                cout << "Not Allocation (Insufficient Memory)\n";
        } else {
            cout << allocation[i] << endl;
        }
    }
}

int main() {
    cout << "Enter Number of Block: ";
    int n; cin >> n;
    int block[n];
    cout << "Enter " << n << " Block Sizes: ";
    for (int i = 0; i < n; i++) cin >> block[i];

    cout << "Enter number of processes: ";
    int m; cin >> m;
    int process[m];
    cout << "Enter " << m << " Process Sizes: ";
    for (int i = 0; i < m; i++) cin >> process[i];

    Best_Fit(n, block, m, process);
}

