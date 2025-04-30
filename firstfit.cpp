#include<bits/stdc++.h> // সব স্ট্যান্ডার্ড লাইব্রেরি ইনক্লুড করা হচ্ছে
using namespace std; // স্ট্যান্ডার্ড নামস্পেস ব্যবহার করা হচ্ছে

// First Fit অ্যালগরিদম সংজ্ঞা
void First_Fit(int n, int block[], int m, int process[]){
    int allocation[m]; // প্রতিটি প্রসেস কোন ব্লকে এলোকেট হয়েছে, তা সংরক্ষণে ব্যবহৃত অ্যারে

    for(int i = 0; i < m; i++){ // প্রতিটি প্রসেসের জন্য
        int k = 0; // ফ্ল্যাগ, যদি এলোকেশন হয় তাহলে 1 হবে
        for(int j = 0; j < n; j++){ // প্রতিটি ব্লকের জন্য
            if(process[i] <= block[j]){ // যদি ব্লকের সাইজ প্রসেসের চেয়ে বড় বা সমান হয়
                allocation[i] = j + 1; // প্রসেসটি j+1 নম্বর ব্লকে এলোকেট করা হলো
                block[j] -= process[i]; // ব্লকের অবশিষ্ট জায়গা আপডেট করা হচ্ছে
                k = 1; // এলোকেশন হয়েছে
                break; // একটি ব্লকে এলোকেট হয়ে গেলে লুপ থেমে যায়
            }
        }
        if(k == 0) allocation[i] = -1; // যদি কোন ব্লকে এলোকেট না হয়
    }

    int extra = 0; // এক্সটার্নাল ফ্র্যাগমেন্টেশন গণনার জন্য ভেরিয়েবল
    for(int i = 0; i < n; i++){ // সব ব্লকের অবশিষ্ট জায়গা যোগ করা হচ্ছে
        extra += block[i];
    }

    cout << "External Fragmentation is: " << extra; // এক্সটার্নাল ফ্র্যাগমেন্টেশন দেখানো হচ্ছে
    cout << "\nFirst Fit Algorithm\n"; // অ্যালগরিদমের নাম প্রিন্ট
    cout << "PID\t" << "Process Size\t" << "Block NO.\n"; // টেবিল হেডার

    for(int i = 0; i < m; i++){ // প্রতিটি প্রসেসের জন্য আউটপুট
        cout << i + 1 << "\t" << process[i] << "\t\t"; // প্রসেস আইডি এবং সাইজ প্রিন্ট
        if(allocation[i] == -1){ // যদি এলোকেশন না হয়
            int total_free = 0;
            for(int k = 0; k < n; k++) total_free += block[k]; // মোট ফ্রি মেমোরি হিসাব করা হচ্ছে
            if(total_free >= process[i])
                cout << "Not Allocation (External Fragmentation)\n"; // ফ্রি মেমোরি যথেষ্ট কিন্তু ছড়িয়ে আছে
            else
                cout << "Not Allocation (Insufficient Memory)\n"; // ফ্রি মেমোরি কম
        } else {
            cout << allocation[i] << endl; // যেই ব্লকে এলোকেট হয়েছে তা প্রিন্ট
        }
    }
}

// প্রোগ্রামের মূল ফাংশন
int main(){
    cout << "Enter Number of Block :"; // ব্লকের সংখ্যা ইনপুট চাওয়া হচ্ছে
    int n; cin >> n;
    int block[n]; // ব্লক সাইজ সংরক্ষণের জন্য অ্যারে

    cout << "Enter " << n << " Block Size: "; // প্রতিটি ব্লকের সাইজ ইনপুট
    for(int i = 0; i < n; i++) cin >> block[i];

    cout << "Enter number of process:"; // প্রসেসের সংখ্যা ইনপুট
    int m; cin >> m;
    int process[m]; // প্রসেস সাইজ সংরক্ষণের জন্য অ্যারে

    cout << "Enter " << m << " Process Size:"; // প্রতিটি প্রসেসের সাইজ ইনপুট
    for(int i = 0; i < m; i++) cin >> process[i];

    First_Fit(n, block, m, process); // First Fit ফাংশন কল করা হচ্ছে
}
