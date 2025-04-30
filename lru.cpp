#include <bits/stdc++.h>
using namespace std;

vector<int> q;
vector<int> s = {7, 0, 1, 2, 0, 3, 0, 4, 2, 3, 0, 3, 2};

int frame_size = 3; //max capacity
int fault = 0;
int hit = 0;

int pos;
bool exist(int value){
    auto it = find(q.begin(), q.end(), value);
    if(it != q.end()){
        pos = distance(q.begin(), it);  // Getting the position of the element
        return true;
    }
    else{
        return false;
    }


}
void solve() {
    for(int i = 0; i<s.size(); i++){
        if(frame_size>0 && frame_size<=3){
            if(exist(s[i])){
                hit++;
                q.erase(q.begin() + pos);
                q.push_back(s[i]); //recently used
                continue;
            }

            fault++;
            q.push_back(s[i]);
            frame_size--;
        }
        else{
            if(exist(s[i])){
                hit++;
                q.erase(q.begin() + pos);
                q.push_back(s[i]); //recently used
            }
            else{
                q[0] = s[i]; //replace with least recent
                fault++;
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
