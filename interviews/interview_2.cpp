#include <cmath>
#include <cstdio>
#include <optional>
#include <tuple>
#include <unordered_map>
#include <vector>
#include <iostream>
#include <algorithm>
#include <thread>
#include <unistd.h>
#include <queue>
#include <list>
#include <optional>
#include <chrono>



using namespace std;

class Cache{
private:
    unordered_map<string, string> map; 
    
public:
    Cache(){
    }

    void put(string key, string val, long long ttl){
        put(key, val);
        thread th([this, key, ttl](){
            this_thread::sleep_for(chrono::milliseconds(ttl));
            this->map.erase(key);
        });
        th.detach();
    }
    
    void put(string key, string val){
        map[key] = val;
    }
    
    optional<string> get(string key){
        if(map.count(key)){
            return map[key];
        }
            
        return std::nullopt;
    }
};


int main() {
    Cache cache;
    cache.put("cat", "dog", 2000);
    this_thread::sleep_for(chrono::milliseconds(500));
    cout << cache.get("cat").has_value() << endl;
    return 0;
}
