#include "Transaction.hpp"

Transaction::Transaction(const string& id, const string& email, TransactionStatus status)
    : transactionId(id), 
      customerEmail(email), 
      status(status) {}