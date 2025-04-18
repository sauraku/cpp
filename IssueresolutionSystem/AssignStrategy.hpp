#pragma once
#include "Issue.hpp"
#include "Agent.hpp"
#include <vector>

using namespace std;

class AssignStrategy {
public:
    virtual Agent* assign(Issue* issue, const vector<Agent*>& agents) = 0;
    virtual ~AssignStrategy() = default;
};