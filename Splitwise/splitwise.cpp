// given a list of transaction <from, to, amount>, I have to settle them and return who will pay whom, how much. just like splitwise
// the system will take users involved in transaction and ration in which the amount will be distributed


#include <iostream>
#include <vector>
#include <unordered_map>
#include <utility> // for std::pair

using namespace std;

class User {
private:
    string name;
    unordered_map<string, float> balances; // user, balance
    // This map will keep track of how much each user owes to this user


public:
    User(string _name) : name(_name) {}

    string getName() const {
        return name;
    }

    void addBalance(string user, float amount) {
        balances[user] += amount;
    }
    
    void settleBalance(string user, float amount) {
        if (balances.find(user) != balances.end()) {
            balances[user] -= amount;
            if (balances[user] <= 0) {
                balances.erase(user);
            }
        }
    }
    float getBalance(string user) const {
        if (balances.find(user) != balances.end()) {
            return balances.at(user);
        }
        return 0.0;
    }
    void printBalances() const {
        cout << "Balances for " << name << ":" << endl;
        for (const auto& pair : balances) {
            cout << "  " << pair.first << ": " << pair.second << endl;
        }
    }
};


class Transaction{
private:
    float amount;
    User *userwhoPaid;
    // This will keep track of how much each user owes to this user
    vector<pair<User*, float>> users; // user, ratio

public:
    Transaction(float _amount, User *_userwhoPaid, vector<pair<User*, float>> _users) : amount(_amount), userwhoPaid(_userwhoPaid), users(_users)  {}

    void distribute() {
        for (const auto& user : users) {
            float userShare = user.second * amount;
            user.first->addBalance(userwhoPaid->getName(), userShare);
            cout << user.first->getName() << " owes " <<  userwhoPaid->getName() << " : " << userShare << endl;
        }
    }
};


class Splitwise {
private:
    vector<User*> users;
    vector<Transaction*> transactions;

public:
    void addUser(User* user) {
        users.push_back(user);
    }

    void addTransaction(Transaction* transaction) {
        transactions.push_back(transaction);
        transaction->distribute();
    }

    void printBalances() const {
        for (const auto& user : users) {
            user->printBalances();
        }
    }
};


int main() {
    Splitwise splitwise;

    User* alice = new User("Alice");
    User* bob = new User("Bob");
    User* charlie = new User("Charlie");
    splitwise.addUser(alice);
    splitwise.addUser(bob);
    splitwise.addUser(charlie);

    // create transaction
    vector<pair<User*, float>> users = { {alice, 0.5}, {charlie, 0.5} };
    Transaction* transaction1 = new Transaction(100, alice, users);
    splitwise.addTransaction(transaction1);
    // create another transaction
    vector<pair<User*, float>> users2 = { {alice, 0.1}, {charlie, 0.9} };
    Transaction* transaction2 = new Transaction(200, alice, users2);
    splitwise.addTransaction(transaction2);

    // print balances
    splitwise.printBalances();
    // clean up
    delete alice;
    delete bob;
    delete charlie;
    delete transaction1;   
    delete transaction2;   
    return 0;
}



