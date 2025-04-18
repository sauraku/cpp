#include "IssueManager.hpp"

IssueManager* IssueManager::instance = nullptr;

IssueManager* IssueManager::getInstance(AssignStrategy* strategy, AgentManager* agentManager) {
    if (!instance) {
        if (!strategy || !agentManager) {
            throw std::runtime_error("IssueManager must be initialized with strategy and agentManager the first time.");
        }
        instance = new IssueManager(strategy, agentManager);
    }
    return instance;
}

void IssueManager::addTransaction(Transaction* tx) {
    transactions[tx->transactionId] = tx;
}

Issue* IssueManager::createIssue(const string& transactionId, IssueType type,
                                 const string& subject, const string& description,
                                 const string& email) {
    string id = "I" + to_string(issueCounter++);
    auto* issue = new Issue(id, transactionId, type, subject, description, email);
    issues[id] = issue;
    return issue;
}

void IssueManager::assignIssue(const string& issueId) {
    Issue* issue = issues[issueId];
    Agent* agent = strategy->assign(issue, agentManager->getAllAgents());
    if (agent) 
        agent->assignIssue(issue);
}

void IssueManager::updateIssue(const string& issueId, IssueStatus status, const string& resolution) {
    Issue* issue = issues[issueId];
    issue->status = status;
    issue->resolution = resolution;
}

void IssueManager::resolveIssue(const string& issueId, const string& resolution) {
    Issue* issue = issues[issueId];
    issue->status = IssueStatus::RESOLVED;
    issue->resolution = resolution;
    if (issue->assignedAgent) 
        issue->assignedAgent->resolveCurrentIssue();
}

vector<Issue*> IssueManager::getIssuesByEmail(const string& email) {
    vector<Issue*> result;
    for (auto& [_, issue] : issues)
        if (issue->customerEmail == email) result.push_back(issue);
    return result;
}

vector<Issue*> IssueManager::getIssuesByType(IssueType type) {
    vector<Issue*> result;
    for (auto& [_, issue] : issues)
        if (issue->type == type) result.push_back(issue);
    return result;
}

Agent* IssueManager::addAgent(const string& name, const string& email, const set<IssueType>& expertise){
    return agentManager->addAgent(name, email, expertise);
}

vector<Agent*> IssueManager::getAllAgents(){
    return agentManager->getAllAgents();
}

map<string, vector<string>> IssueManager::viewAgentHistory(){
    return agentManager->viewAgentHistory();
}