#include "AgentManager.hpp"

Agent* AgentManager::addAgent(const string& name, const string& email,
                              const set<IssueType>& expertise) {
    string id = "A" + to_string(agentCounter++);
    auto* agent = new Agent(id, name, email, expertise);
    agents[id] = agent;
    return agent;
}

vector<Agent*> AgentManager::getAllAgents() {
    vector<Agent*> result;
    for (const auto& [_, agent] : agents) 
        result.push_back(agent);

    return result;
}

map<string, vector<string>> AgentManager::viewAgentHistory() {
    map<string, vector<string>> history;
    for (auto& [_, agent] : agents) {
        for (auto issue : agent->workHistory)
            history[agent->agentId].push_back(issue->issueId);
    }

    return history;
}