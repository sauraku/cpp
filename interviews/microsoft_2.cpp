// a function to check duplicate letters in string, salesforce -> [s, e]



vector<char> getDuplicates(string str){

    unordered_set<char> set;
    unordered_set<char> results;

    for(auto ch: str) {
        if(set.find(ch)==set.end()){
            set.insert(ch);
        } else {
            results.insert(ch);
        }
    }

    return vector<char>(results.begin(), results.end());

}