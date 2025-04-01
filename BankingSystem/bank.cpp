#include "bank.hpp"

Bank::Bank() {
    // Constructor
}

Bank::~Bank() {
    // Destructor
}

bool Bank::createAccount(int ts, string account_id) {
    executeScheduled(ts);
    if(accounts.find(account_id)==accounts.end()){
        accounts[account_id] = 0;
        return true;
    }
    return false;
}

int Bank::withdraw(int ts, string account_id, double amount) {
    executeScheduled(ts);
    if(accounts.find(account_id)!=accounts.end() && accounts[account_id] >= amount){
        accounts[account_id] -= amount;
        return accounts[account_id];
    }

    return -1;
}

int Bank::deposit(int ts, string account_id, double amount) {
    executeScheduled(ts);
    if(accounts.find(account_id)!=accounts.end()){
        accounts[account_id] += amount;
        return accounts[account_id];
    }
    return -1;
}

void Bank::executeScheduled(int ts){
    for(auto a: ppt[ts]){
        if(accounts.find(a.from) != accounts.end() && accounts.find(a.to) != accounts.end() && accounts[a.from] > a.amount ){
            accounts[a.from] -= a.amount;
            accounts[a.to] += a.amount;
        }
    }
}

string Bank::scheduledTransfer(int ts, string from_account_id, string to_account_id, double amount, int interval) {
    executeScheduled(ts);
    ppt[ts + interval].push_back(Trans{from_account_id, to_account_id, amount});

    return "ts" + to_string(tsc++);
}

int Bank::transfer(int ts, string from_account_id, string to_account_id, double amount) {
    executeScheduled(ts);
    if(accounts.find(from_account_id)!=accounts.end() && accounts.find(to_account_id)!=accounts.end()){
        if(accounts[from_account_id] >= amount){
            accounts[from_account_id] -= amount;
            accounts[to_account_id] += amount;
            return accounts[from_account_id];
        }
    }
    return -1;
}

