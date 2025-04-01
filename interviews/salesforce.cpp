#include <bits/stdc++.h>
#include <numeric>

using namespace std;

#include <bits/stdc++.h>
using namespace std;

vector<long> getProcessTime(vector<int> &time) {
    long long sm = accumulate(time.begin(), time.end(), 0);
    int target = sm / 2;

    // Use bitset to track possible sums
    bitset<10001> dp;
    dp[0] = 1; // Base case: sum 0 is always possible

    for (int t : time) {
        dp |= dp << t;  // Shift bits to mark new achievable sums
    }

    // Find the closest sum <= target
    int best = target;
    while (!dp[best]) best--;

    return {best, sm - best};
}

int main() {
    int time_count;
    cin >> time_count;
    vector<int> time(time_count);

    for (int i = 0; i < time_count; i++) {
        cin >> time[i];
    }

    vector<long> result = getProcessTime(time);
    cout << result[0] << "\n" << result[1] << "\n";

    return 0;
}


// string ltrim(const string &);
// string rtrim(const string &);

 
// long long getSum(vector<int> &time, long long target, int i, int sf){
//     if(i>=time.size()){
//         return sf;
//     }
    
//     if(sf > target){
//         return sf;
//     }

//     long long t = getSum(time, target, i+1, sf+time[i]);
//     long long nt = getSum(time, target, i+1, sf);
    
//     cout << t << " " << nt;
//     return max(t, nt);
    
// }

// vector<long> getProcessTime(vector<int> time) {
//     sort(time.begin(), time.end());
    
//     long long sm = accumulate(time.begin(), time.end(), 0);
    
//     long long a = getSum(time, sm/2, 0, 0);
    

    
//     return {a,sm -a};
// }

// int main()
// {
//     ofstream fout(getenv("OUTPUT_PATH"));

//     string time_count_temp;
//     getline(cin, time_count_temp);

//     int time_count = stoi(ltrim(rtrim(time_count_temp)));

//     vector<int> time(time_count);

//     for (int i = 0; i < time_count; i++) {
//         string time_item_temp;
//         getline(cin, time_item_temp);

//         int time_item = stoi(ltrim(rtrim(time_item_temp)));

//         time[i] = time_item;
//     }

//     vector<long> result = getProcessTime(time);

//     for (size_t i = 0; i < result.size(); i++) {
//         fout << result[i];

//         if (i != result.size() - 1) {
//             fout << "\n";
//         }
//     }

//     fout << "\n";

//     fout.close();

//     return 0;
// }

// string ltrim(const string &str) {
//     string s(str);

//     s.erase(
//         s.begin(),
//         find_if(s.begin(), s.end(), not1(ptr_fun<int, int>(isspace)))
//     );

//     return s;
// }

// string rtrim(const string &str) {
//     string s(str);

//     s.erase(
//         find_if(s.rbegin(), s.rend(), not1(ptr_fun<int, int>(isspace))).base(),
//         s.end()
//     );

//     return s;
// }
