#include<bits/stdc++.h>
using namespace std;

int main() {
    int p, r;
    cout << "Enter number of processes: ";
    cin >> p;
    cout << "Enter number of resources: ";
    cin >> r;

    int alloc[p][r], maxNeed[p][r], avail[r];

    cout << "Enter Allocation Matrix (row by row):\n";
    for(int i=0; i<p; i++) {
        cout << "Process P" << i << ": ";
        for(int j=0; j<r; j++)
            cin >> alloc[i][j];
    }

    cout << "Enter Maximum Need Matrix (row by row):\n";
    for(int i=0; i<p; i++) {
        cout << "Process P" << i << ": ";
        for(int j=0; j<r; j++)
            cin >> maxNeed[i][j];
    }

    cout << "Enter Available Resources: ";
    for(int j=0; j<r; j++)
        cin >> avail[j];

    // Need Matrix Calculate
    int need[p][r];
    for(int i=0; i<p; i++)
        for(int j=0; j<r; j++)
            need[i][j] = maxNeed[i][j] - alloc[i][j];

    // Print Need Matrix
    cout << "\nNeed Matrix:\n";
    for(int i=0; i<p; i++) {
        cout << "P" << i << ": ";
        for(int j=0; j<r; j++)
            cout << need[i][j] << " ";
        cout << endl;
    }

    // Banker's Algorithm Logic
    bool finish[p] = {false};
    vector<int> safeSeq;

    for(int count = 0; count < p; count++) {
        bool found = false;
        for(int i = 0; i < p; i++) {
            if(!finish[i]) {
                bool canRun = true;
                for(int j = 0; j < r; j++) {
                    if(need[i][j] > avail[j]) {
                        canRun = false;
                        break;
                    }
                }
                if(canRun) {
                    for(int j = 0; j < r; j++)
                        avail[j] += alloc[i][j];
                    finish[i] = true;
                    safeSeq.push_back(i);
                    found = true;
                }
            }
        }
        if(!found) break;
    }

    // Final Output with formatted Safe Sequence
    bool safe = all_of(finish, finish + p, [](bool b){ return b; });

    if(safe) {
        cout << "\nSystem is in a SAFE state.\n";
        cout << "Safe Sequence: ";
        for(size_t i = 0; i < safeSeq.size(); i++) {
            cout << "P" << safeSeq[i];
            if(i != safeSeq.size() - 1) cout << " -> ";
        }
        cout << endl;
    } else {
        cout << "\nSystem is NOT in a safe state.\n";
    }

    return 0;
}
