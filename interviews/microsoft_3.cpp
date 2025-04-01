// [3,4,5,1,2,10,6]
#include <bits/stdc++.h>

u

map<pair<int,int>, int> memo;

int getMaxSubSeq(vector<int> &nums, int idx, int prev)
{
    if(idx >= nums.size()) 
        return 0;

    if(memo.find({idx, prev})!=memo.end()){
        return memo[{idx, prev}];
    }
    int s1 = INT_MIN, s2 = INT_MIN;
    if (prev > nums[idx]){
        s1 = getMaxSubSeq(nums, idx+1, prev);
    } else {
        s2 = 1 + getMaxSubSeq(nums, idx+1, nums[idx]);
    }

    int result = max(s1, s2);
    memo[{idx, prev}] = result;
    return result;
}


// assumption int arr[i] > INT_MIN
// strictly incresing subsequece
int main(){
    getMaxSubSeq({3,4,5,1,2,10,6}, 0, INT_MIN);
    return 0;
}



// you can use includes, for example:
// #include <algorithm>

// you can write to stdout for debugging purposes, e.g.
// cout << "this is a debug message" << endl;

int solve(string &s1, string &s2){
    int n = s1.size();

    int dp1 = 0, dp2 = 0;

    for(int i=0;i<n;i++){
        if(s1[i]==s2[i]){
            if (s1[i]=='x'){
                dp1++;
                dp2++;
            }
            else {
                dp1 = dp2 = max(dp1, dp2);
            }
        }
        else {
            if(s1[i]=='x'){
                dp1 = max(dp1, dp2);
                dp2++;
            } 
            else {
                dp2 = max(dp1, dp2);
                dp1++;
            }
        }
    }
    return max(dp1, dp2);
}

int solution(string &L1, string &L2) {
    // Implement your solution here
    return solve(L1, L2);
}
