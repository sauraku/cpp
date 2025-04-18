#include "Agent.hpp"

Agent::Agent(const string& id, const string& name, const string& email,
             const set<IssueType>& expertise)
    : agentId(id), 
      name(name), 
      email(email), 
      expertise(expertise), 
      status(AgentStatus::FREE) {}

void Agent::assignIssue(Issue* issue) {
    if (status == AgentStatus::FREE) {
        issue->assignedAgent = this;
        workHistory.push_back(issue);
        status = AgentStatus::BUSY;
    } else {
        waitingIssues.push(issue);
    }
}

void Agent::resolveCurrentIssue() {
    if (!waitingIssues.empty()) {
        Issue* next = waitingIssues.front();
        waitingIssues.pop();
        next->assignedAgent = this;
        workHistory.push_back(next);
        status = AgentStatus::BUSY;
    } else {
        status = AgentStatus::FREE;
    }
}

// bool Agent::test_resolveCurrentIssue() {
//     If(status == AgentStatus::BUSY) {
//         issue *currentIssue = workHistory.back();
//         currentIssue->status = IssueStatus::RESOLVED;
//         currentIssue->assignedAgent = nullptr;
//         status = AgentStatus::FREE;
//         return true;
//     }
// }