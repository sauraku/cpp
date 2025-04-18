#pragma once
#include <string>
#include <set>
#include <queue>
#include <vector>
#include "Issue.hpp"

using namespace std;

enum class AgentStatus {
    FREE,
    BUSY
};

class Agent {
public:
    string agentId;
    string name;
    string email;
    set<IssueType> expertise;
    AgentStatus status;
    queue<Issue*> waitingIssues;
    vector<Issue*> workHistory;

    Agent(const string& id, const string& name, const string& email,
          const set<IssueType>& expertise);

    void assignIssue(Issue* issue);
    void resolveCurrentIssue();
    // bool test_resolveCurrentIssue();
};
