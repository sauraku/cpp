#pragma once
#include "Issue.hpp"
#include "Agent.hpp"
#include "AssignStrategy.hpp"
#include <vector>

using namespace std;

class AnyFreeAgentStrategy : public AssignStrategy {
public:
    Agent* assign(Issue* issue, const vector<Agent*>& agents) override;
};