#ifndef TRANSACTION_H
#define TRANSACTION_H

#include <iostream>
#include <vector>
#include <string>
#include <memory>    
#include <algorithm> 
using namespace std;

class Transaction{
    protected:
    double amount;

    public:
    explicit Transaction(double amount);
    virtual ~Transaction()=default;

    virtual string describe() const=0;
    /* purely virtual as it varies for various types of transactions, followed below*/

    double getAmount() const;
};

class Deposit : public Transaction {
public:
    explicit Deposit(double amount);
    string describe() const override;
};

class Withdrawal : public Transaction {
public:
    explicit Withdrawal(double amount);
    string describe() const override;
};

class Transfer : public Transaction {
private:
    string counterpartyAccount;
    bool isIncoming; // true if money arrived from counterparty account, false if money left to it

public:
    Transfer(double amount, const string& counterpartyAccount, bool isIncoming);
    string describe() const override;
};
#endif