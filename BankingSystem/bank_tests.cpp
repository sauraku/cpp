// gtests for the Bank class

#include <gtest/gtest.h>
#include "bank.hpp"


// Test case for createAccount
TEST(BankTest, createAccount) {
    Bank bank;
    EXPECT_EQ(true, bank.createAccount(1, "123"));
    EXPECT_EQ(false, bank.createAccount(2, "123"));
}

// Test case for withdraw
TEST(BankTest, withdraw) {
    Bank bank;
    bank.createAccount(1, "123");
    bank.deposit(2, "123", 100);
    EXPECT_EQ(50, bank.withdraw(3, "123", 50));
    EXPECT_EQ(-1, bank.withdraw(4, "123", 100));
    EXPECT_EQ(-1, bank.withdraw(5, "456", 100));
}

// Test case for deposit
TEST(BankTest, deposit) {
    Bank bank;
    bank.createAccount(1, "123");
    EXPECT_EQ(100, bank.deposit(2, "123", 100));
    EXPECT_EQ(-1, bank.deposit(3, "456", 100));
}

// Test case for scheduledTransfer
TEST(BankTest, scheduledTransfer) {
    Bank bank;
    bank.createAccount(1, "123");
    bank.createAccount(2, "456");
    bank.deposit(3, "123", 100);
    bank.scheduledTransfer(4, "123", "456", 10, 5);
    bank.executeScheduled(5);
    EXPECT_EQ(90, bank.accounts["123"]);
    EXPECT_EQ(10, bank.accounts["456"]);
}

// Test case for transfer
TEST(BankTest, transfer) {
    Bank bank;
    bank.createAccount(1, "123");
    bank.createAccount(2, "456");
    bank.deposit(3, "123", 100);
    EXPECT_EQ(80, bank.transfer(4, "123", "456", 20));
    EXPECT_EQ(-1, bank.transfer(5, "123", "456", 100));
}

// Test case for all functions - 1
TEST(BankTest, allFunctions1) {
    Bank bank;
    bank.createAccount(1, "123");
    bank.deposit(2, "123", 100);
    bank.withdraw(3, "123", 50);
    bank.createAccount(4, "456");
    bank.scheduledTransfer(5, "123", "456", 10, 5);
    bank.executeScheduled(5);
    EXPECT_EQ(40, bank.accounts["123"]);
    EXPECT_EQ(10, bank.accounts["456"]);
}

// Test case for all functions - 2
TEST(BankTest, allFunctions2) {
    Bank bank;
    bank.createAccount(1, "123");
    bank.deposit(2, "123", 100);
    bank.withdraw(3, "123", 50);
    bank.createAccount(4, "456");
    bank.scheduledTransfer(5, "123", "456", 10, 5);
    bank.executeScheduled(5);
    bank.scheduledTransfer(6, "123", "456", 10, 5);
    bank.executeScheduled(6);
    EXPECT_EQ(30, bank.accounts["123"]);
    EXPECT_EQ(20, bank.accounts["456"]);
}

// Test case for all functions - 3
TEST(BankTest, allFunctions3) {
    Bank bank;
    bank.createAccount(1, "123");
    bank.deposit(2, "123", 100);
    bank.withdraw(3, "123", 50);
    bank.createAccount(4, "456");
    bank.scheduledTransfer(5, "123", "456", 10, 5);
    bank.executeScheduled(5);
    bank.scheduledTransfer(6, "123", "456", 10, 5);
    bank.executeScheduled(6);
    bank.scheduledTransfer(7, "123", "456", 10, 5);
    bank.executeScheduled(7);
    EXPECT_EQ(20, bank.accounts["123"]);
    EXPECT_EQ(30, bank.accounts["456"]);
}


int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

