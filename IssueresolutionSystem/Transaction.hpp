#pragma once
#include <string>

using namespace std;

enum class TransactionStatus {
    SUCCESS,
    FAILED,
    PENDING
};

class Transaction {
public:
    string transactionId;
    string customerEmail;
    TransactionStatus status;

    Transaction(const string& id, const string& email, TransactionStatus status);
};