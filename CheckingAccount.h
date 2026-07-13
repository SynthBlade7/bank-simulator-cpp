#ifndef CHECKING_ACCOUNT_H
#define CHECKING_ACCOUNT_H

#include <string>
#include "Account.h"

using namespace std;
class CheckingAccount:public Account{
    private:
    double overdraftLimit;
    bool applyWithdrawal(double amount) override;
    /* allows the balance to go negative, down to -overdraftLimit, 
    instead of blocking the withdrawal outright like the base Account::applyWithdrawal.
    Because this is the piece both withdraw() AND debitForTransfer() call, the
    overdraft rule is respected in both a normal withdrawal and a transfer*/

    public:
    CheckingAccount(const string& accountNumber, const string& ownerName, double initialBalance, double overdraftLimit);


    double calculateInterest() const override; //completely virtual account function
};
#endif