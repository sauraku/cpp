#pragma once
#include "Issue.hpp"
#include "Transaction.hpp"
#include "AssignStrategy.hpp"
#include "AgentManager.hpp"
#include <map>
#include <vector>
#include <stdexcept>
#include <stdexcept>
#include <stdexcept>

using namespace std;

class IssueManager {
private:
    map<string, Issue*> issues;
    map<string, Transaction*> transactions;
    AssignStrategy* strategy;
    AgentManager* agentManager;
    int issueCounter = 1;

    static IssueManager* instance;
    IssueManager(AssignStrategy* strategy, AgentManager* agentManager)
    : strategy(strategy),
      agentManager(agentManager) {}


public:
    static IssueManager* getInstance(AssignStrategy* strategy = nullptr, AgentManager* agentManager = nullptr);

    Issue* createIssue(const string& transactionId, IssueType type,
                       const string& subject, const string& description,
                       const string& email);
    Agent* addAgent(const string& name, const string& email,
                       const set<IssueType>& expertise);
    void assignIssue(const string& issueId);
    void updateIssue(const string& issueId, IssueStatus status, const string& resolution);
    void resolveIssue(const string& issueId, const string& resolution);
    vector<Issue*> getIssuesByEmail(const string& email);
    vector<Issue*> getIssuesByType(IssueType type);
    vector<Agent*> getAllAgents();
    map<string, vector<string>> viewAgentHistory();
    void addTransaction(Transaction* transaction);
};