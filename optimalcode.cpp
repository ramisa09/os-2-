#include<bits/stdc++.h> // সব স্ট্যান্ডার্ড লাইব্রেরি ইনক্লুড করা হয়
using namespace std; // std নামস্পেস ব্যবহার করা হচ্ছে

int main()
{
    int n, f, hits = 0; // n = মোট পেজ, f = ফ্রেম সংখ্যা, hits = হিট কাউন্ট
    cin>> n; // পেজ সংখ্যা ইনপুট নেওয়া হচ্ছে

    vector<int> p(n), fms; // p = পেজ রেফারেন্স লিস্ট, fms = মেমোরি ফ্রেম
    for(auto &x : p) cin>>x; // পেজ রেফারেন্স ইনপুট নেওয়া হচ্ছে
    cin>>f; // ফ্রেম সংখ্যা ইনপুট নেওয়া হচ্ছে

    for(int i = 0; i < n; i++){ // প্রতিটি পেজ রেফারেন্সের জন্য লুপ
        if (find(fms.begin(), fms.end(), p[i]) != fms.end()) hits++;
        // যদি পেজটি আগে থেকেই মেমোরিতে থাকে, তাহলে হিট কাউন্ট বাড়ে
        else
        {
            if(fms.size() < f) fms.push_back(p[i]);
            // যদি মেমোরিতে জায়গা থাকে, তবে পেজ যুক্ত করা হয়
            else
            {
                int idx = 0, far = -1; // idx = যেটা রিপ্লেস হবে, far = সবচেয়ে দূরের রেফারেন্স
                for(int j = 0; j < fms.size(); j++) // প্রতিটি মেমোরি ফ্রেম যাচাই
                {
                    int k = find(p.begin() + i + 1, p.end(), fms[j]) - p.begin();
                    // মেমোরিতে থাকা পেজটি পরবর্তীতে কখন আবার আসবে তা খোঁজা হচ্ছে
                    if(k > far) far = k, idx = j;
                    // সবচেয়ে পরে যেটা আসবে সেটি রিপ্লেস করার জন্য রাখা হচ্ছে
                }
                fms[idx] = p[i]; // মেমোরির সেই ফ্রেমে নতুন পেজ রিপ্লেস করা হচ্ছে
            }
        }
    }

    cout<<"Total page hit: " << hits << endl; // মোট হিট সংখ্যা প্রিন্ট করা হচ্ছে
    cout<<"Total page faults: " << n - hits << endl; // মোট পেজ ফল্ট = মোট রেফারেন্স - হিট সংখ্যা

    double hit_ratio = (double) hits / n; // হিট রেশিও গণনা
    double miss_ratio = 1.0 - hit_ratio; // মিস রেশিও = ১ - হিট রেশিও

    cout<< fixed << setprecision(2); // দশমিকের পরে ২ ঘর পর্যন্ত দেখাবে
    cout<<"Hit ratio: " << hit_ratio << endl; // হিট রেশিও প্রিন্ট
    cout<<"Miss ratio: " << miss_ratio << endl; // মিস রেশিও প্রিন্ট

    return 0; // প্রোগ্রাম সফলভাবে শেষ
}
