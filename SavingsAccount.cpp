#include "SavingsAccount.h"

SavingsAccount::SavingsAccount(const string& accNum, const string& owner,double initialBalance, double interestRate)
    :Account(accNum, owner, initialBalance), interest(interestRate) {}

double SavingsAccount::calculateInterest() const {
    return getBalance()*interest;
}
