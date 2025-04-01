#include "bank.hpp"

int main() {
    Bank bank;
    bank.createAccount(1, "123");
    bank.deposit(2, "123", 100);
    bank.withdraw(3, "123", 50);
    bank.createAccount(4, "456");
    bank.scheduledTransfer(5, "123", "456", 10, 5);
    cout << bank.transfer(10, "123", "456", 20) << endl;
    return 0;
}