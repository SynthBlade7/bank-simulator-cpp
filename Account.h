#ifndef ACCOUNT_H
#define ACCOUNT_H

#include <iostream>
#include <vector>
#include <string>
#include <memory>    
#include <algorithm> 
#include "Transaction.h"
using namespace std;

class Account{
    protected://further accessed in checkingaccount.cpp
    string AccountNumber;
    string OwnerName;
    double balance;

    vector<unique_ptr<Transaction>> history;
    void logTransaction(unique_ptr<Transaction> t);
    virtual bool applyWithdrawal(double amount);

    public:

    Account(const string& accNum, const string& owner, double initialamount);
    virtual ~Account() = default;
    /* Since we using Account* or unique_ptr<Account>, deleting a savings account
        would only trigger ~Account(), even though ~SavingsAccount() needs to be 
        performed. Hence we use virtual functions here.
    */

    void deposit(double amount);
    bool withdraw(double amount);
    bool debitForTransfer(double amount, const string& counterpartyAccount);
    void creditForTransfer(double amount, const string& counterpartyAccount);

    virtual double calculateInterest() const = 0; //entirely virtual, hence no bare account possibility

    double getBalance() const;
    string getAccountNumber() const;
    string getOwnerName() const;

    void printHistory() const;

};

#endif