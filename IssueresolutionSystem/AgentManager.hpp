#pragma once
#include "Agent.hpp"
#include <map>
#include <vector>

using namespace std;

class AgentManager {
private:
    map<string, Agent*> agents;
    int agentCounter = 1;

public:
    Agent* addAgent(const string& name, const string& email,
                    const set<IssueType>& expertise);
    vector<Agent*> getAllAgents();
    map<string, vector<string>> viewAgentHistory();
};