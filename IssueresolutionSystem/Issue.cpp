#include "Issue.hpp"

Issue::Issue(const string& id, const string& txId, IssueType type,
             const string& subject, const string& description,
             const string& email)
    : issueId(id), 
      transactionId(txId), 
      type(type), 
      subject(subject),
      description(description), 
      status(IssueStatus::OPEN), 
      resolution(""),
      customerEmail(email), 
      assignedAgent(nullptr) {}