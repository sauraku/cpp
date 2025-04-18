#include <iostream>
#include <set>
#include "AgentManager.hpp"
#include "issueManager.hpp"
#include "AnyFreeAgentStrategy.hpp"
#include "Transaction.hpp"

using namespace std;

int main() {
    AgentManager* agentManager = new AgentManager();
    AssignStrategy* strategy = new AnyFreeAgentStrategy();
    IssueManager* issueManager = IssueManager::getInstance(strategy, agentManager);

    issueManager->addAgent("Aditi", "aditi@example.com", {IssueType::PAYMENT_RELATED, IssueType::GOLD_RELATED});
    issueManager->addAgent("Raj", "raj@example.com", {IssueType::MUTUAL_FUND_RELATED});
    issueManager->addAgent("Sneha", "sneha@example.com", {IssueType::INSURANCE_RELATED, IssueType::PAYMENT_RELATED});

    issueManager->addTransaction(new Transaction("TXN1001", "customer1@example.com", TransactionStatus::FAILED));
    issueManager->addTransaction(new Transaction("TXN1002", "customer1@example.com", TransactionStatus::PENDING));
    issueManager->addTransaction(new Transaction("TXN1003", "customer2@example.com", TransactionStatus::SUCCESS));

    Issue* issue1 = issueManager->createIssue("TXN1001", IssueType::PAYMENT_RELATED, "Payment Failed", "Payment did not go through", "customer1@example.com");
    issueManager->assignIssue(issue1->issueId);

    Issue* issue2 = issueManager->createIssue("TXN1002", IssueType::INSURANCE_RELATED, "Policy Delay", "Haven't received policy yet", "customer1@example.com");
    issueManager->assignIssue(issue2->issueId);

    Issue* issue3 = issueManager->createIssue("TXN1003", IssueType::GOLD_RELATED, "Gold amount mismatch", "Incorrect gold quantity", "customer2@example.com");
    issueManager->assignIssue(issue3->issueId);

    issueManager->resolveIssue(issue1->issueId, "Refund processed");

    cout << "Issues for customer1@example.com:" << endl;
    auto customerIssues = issueManager->getIssuesByEmail("customer1@example.com");
    for (auto issue : customerIssues) {
        cout << "Issue ID: " << issue->issueId << ", Subject: " << issue->subject << ", Status: " << static_cast<int>(issue->status) << "" << endl;
    }

    cout << "GOLD_RELATED issues:" << endl;
    auto goldIssues = issueManager->getIssuesByType(IssueType::GOLD_RELATED);
    for (auto issue : goldIssues) {
        cout << "Issue ID: " << issue->issueId << ", Subject: " << issue->subject << ", Assigned Agent: " << (issue->assignedAgent ? issue->assignedAgent->name : "None") << "" << endl;
    }

    cout << "Agent Histories:" << endl;
    auto history = issueManager->viewAgentHistory();
    for (const auto& [agentId, issues] : history) {
        cout << "Agent " << agentId << " handled issues: ";
        for (const auto& issueId : issues)
            cout << issueId << " ";
        cout << "" << endl;
    }

    delete strategy;
    return 0;
}
