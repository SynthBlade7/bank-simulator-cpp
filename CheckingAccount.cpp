#include "CheckingAccount.h"
#include <stdexcept>

CheckingAccount::CheckingAccount(const string& accNum, const string& owner, double initialBalance, double overdraftLimit)
    :Account(accNum, owner, initialBalance), overdraftLimit(overdraftLimit) {}

bool CheckingAccount::applyWithdrawal(double amount) {
    if (amount <= 0) {
        throw invalid_argument("Withdrawal amount must be positive");
    }
    //balance is protected in Account, so a derived class can reach it directly
    if (balance - amount < -overdraftLimit) {
        return false; // would exceed the allowed overdraft
    }
    balance -= amount;
    return true; // no logging here, withdraw() or debitForTransfer() logs
}


double CheckingAccount::calculateInterest() const {
    return 0.0; // checking accounts don't earn interest here
}
