#include "Account.h"
#include <iostream>
#include <stdexcept>
using namespace std;

Account::Account(const string& accNum, const string& owner, double initialamount):AccountNumber(accNum), OwnerName(owner), balance(initialamount) {}

void Account::logTransaction(unique_ptr<Transaction>t){
    history.push_back(move(t));
}//privated method

double Account::getBalance() const {return balance;}
string Account::getAccountNumber() const {return AccountNumber;}
string Account::getOwnerName() const {return OwnerName;}

void Account::deposit(double amount) {
    if (amount<=0) {
        throw invalid_argument("Deposit amount must be positive");
    }
    balance += amount;
    logTransaction(make_unique<Deposit>(amount));
}

bool Account::withdraw(double amount) {
        if (applyWithdrawal(amount)) {
            logTransaction(std::make_unique<Withdrawal>(amount));
            return true;
        }
    return false;

}

void Account::printHistory() const {
    cout << "Transaction history for " << AccountNumber<<"\n";
    if (history.empty()) {
        cout<<"(no transactions yet)\n";
        return;
    }
    for(const auto& t:history){
        /* t is a Transaction*, but describe() resolves to whichever override 
            matches the object type at runtime */
        cout<< t->describe() << "\n";
    }
}

bool Account::applyWithdrawal(double amount) {
    if (amount <= 0) {
        throw invalid_argument("Withdrawal amount must be positive");
    }
    if (amount > balance) {
        return false; // base rule: no overdraft allowed
    }
    balance -= amount;
    return true;
}

bool Account::debitForTransfer(double amount, const string& counterpartyAccount) {
    /* Reuses the SAME rule-checking as withdraw() (via the virtual applyWithdrawal), 
        so a CheckingAccount's overdraft limit is
        still respected during a transfer — but logs a Transfer entry
        instead of a Withdrawal.*/
    if (applyWithdrawal(amount)) {
        logTransaction(make_unique<Transfer>(amount, counterpartyAccount, false));
        return true;
    }
    return false;
}
 
void Account::creditForTransfer(double amount, const string& counterpartyAccount) {
    balance += amount;
    logTransaction(make_unique<Transfer>(amount, counterpartyAccount, true));
}
