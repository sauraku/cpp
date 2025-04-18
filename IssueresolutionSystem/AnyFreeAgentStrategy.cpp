#include "AnyFreeAgentStrategy.hpp"

Agent* AnyFreeAgentStrategy::assign(Issue* issue, const vector<Agent*>& agents) {
    for (auto agent : agents) {
        if (agent->status == AgentStatus::FREE &&
            agent->expertise.count(issue->type)) {
            return agent;
        }
    }
    return nullptr;
}