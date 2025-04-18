#pragma once
#include <string>

using namespace std;

enum class IssueType {
    PAYMENT_RELATED,
    MUTUAL_FUND_RELATED,
    GOLD_RELATED,
    INSURANCE_RELATED
};

enum class IssueStatus {
    OPEN,
    IN_PROGRESS,
    RESOLVED
};

class Agent;
class Transaction;

class Issue {
public:
    string issueId;
    string transactionId;
    IssueType type;
    string subject;
    string description;
    IssueStatus status;
    string resolution;
    string customerEmail;
    Agent* assignedAgent;

    Issue(const string& id, const string& txId, IssueType type,
          const string& subject, const string& description,
          const string& email);
};