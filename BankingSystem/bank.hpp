#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>

using namespace std;

class Trans {
public:
    string from;
    string to;
    double amount;

    Trans(string f, string t, double a) :
        from(f),
        to(t),
        amount(a)
        {}
};

class Bank {
public:
    unordered_map<string, double> accounts;
    unordered_map<int, vector<Trans>> ppt;
    int tsc = 1;

    Bank();
    ~Bank();

    // return true if account is created successfully, false if account already exists
    bool createAccount(int ts, string account_id);

    // return amount remaining in account after withdrawal, -1 if account does not exist, -1 if insufficient funds
    int withdraw(int ts, string account_id, double amount);

    // return amount remaining in account after deposit, -1 if account does not exist
    int deposit(int ts, string account_id, double amount);

    // return transaction id of scheduled withdrawal, -1 if account does not exist, -1 if insufficient funds, tansaction id is unique and starts with ts1, ts2 ...
    string scheduledTransfer(int ts, string from_account_id, string to_account_id, double amount, int interval);

    // return amount remaining in account after transfer, -1 if any of the accounts does not exist, -1 if insufficient funds
    int transfer(int ts, string from_account_id, string to_account_id, double amount);

    void executeScheduled(int ts);
};