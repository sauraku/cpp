#include <iostream>
#include <bits/stdc++.h>

using namespace std;


int maxLenSubStr(string s){
    unordered_map<char, int> lastOcc;
    int maxSoFar = INT_MIN, i=0, maxTemp = 0;

    for(int i=0;i<s.size();i++){
        char c = s[i];
        if(lastOcc.find(c)==lastOcc.end() || lastOcc[c] < i-maxTemp){
            maxTemp++;
        } else {
            maxSoFar = max(maxSoFar, maxTemp);
            maxTemp = i-lastOcc[c];
        }
        lastOcc[c] = i;
    }
    maxSoFar = max(maxSoFar, maxTemp);
    return maxSoFar;
}

int getConsecutiveCount(vector<int> nums){
    unordered_set<int> numSet(nums.begin(), nums.end());
    int longestStreak = 0;

    for (int num : numSet) {
        if (numSet.find(num - 1) == numSet.end()) {
            int currNum = num;
            int currentStreak = 1;

            while (numSet.find(currNum + 1) != numSet.end()) {
                currNum++;
                currentStreak++;
            }

            longestStreak = max(longestStreak, currentStreak);
        }
    }
    return longestStreak;
}


int main() {
    // vector<string> vec{"abcdefabcdef","aabbccddee", "dvdf", "tmmzuxt"};

    // for(auto str: vec){
    //     cout << maxLenSubStr(str) << endl;
    // }

    cout << getConsecutiveCount({100,4,200,1,3,2}) << endl;


    return 0;
}
