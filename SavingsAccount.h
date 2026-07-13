#ifndef SAVINGS_ACCOUNT_H
#define SAVINGS_ACCOUNT_H
#include "Account.h"
#include <string>
using namespace std;

class SavingsAccount:public Account{
    private:
    double interest;

    public:
    SavingsAccount(const string& accountNumber, const string& ownerName,double initialBalance, double interestRate);

    double calculateInterest() const override;
    // not overriding withdraw(), calc interest is purely virtual
};
#endif