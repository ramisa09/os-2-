#include <bits/stdc++.h>
using namespace std;

queue<int> q;
vector<int> s = {7, 0, 1, 2, 0, 3, 0, 4, 2, 3, 0, 3, 2};
int frame_size = 3;
int fault = 0;
int hit = 0;

bool exists(queue<int>& q, int value) {
    queue<int> temp = q;  // copy to preserve original
    while (!temp.empty()) {
        if (temp.front() == value) return true;
        temp.pop();
    }
    return false;
}

void solve() {
    for (int i = 0; i < s.size(); i++) {
        if (frame_size > 0 && frame_size <= 3) {
            if (exists(q, s[i])) {
                hit++;
                continue;
            }
            q.push(s[i]);
            fault++;
            frame_size--;  // reduce free slot count
        } else {
            if (exists(q, s[i])) {
                hit++;
            } else {
                fault++;
                q.pop();       // remove oldest
                q.push(s[i]);  // add new
            }
        }
    }
}

int main() {
    solve();
    cout << "Hit = " << hit << endl;
    cout << "Fault = " << fault << endl;
    return 0;
}
