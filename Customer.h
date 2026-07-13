#ifndef CUSTOMER_H
#define CUSTOMER_H

#include <iostream>
#include <vector>
#include <string>
#include <memory>    
#include <algorithm> 
#include "Account.h"
using namespace std;

class Customer{
    private:
    string CustomerId;
    string name;
    vector<unique_ptr<Account>>accounts; //accounts owned

    public:
    Customer(const string& CustomerId, const string& name);
    void addAccount(unique_ptr<Account> account);
    //takes ownership of the account via move()

    Account* findAccount(const string& AccountNumber) const;
    /* returns a non-owning pointer for callers, customer still owns
        the account's lifetime through the above uniqueptr */

    string getName() const;
    string getCustomerId() const;
    const vector<unique_ptr<Account>>& getAccounts() const;
};
#endif
