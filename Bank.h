#ifndef BANK_H
#define BANK_H

#include <iostream>
#include <vector>
#include <string>
#include <memory>    
#include <algorithm> 
#include "Customer.h"
using namespace std;

class Bank{
    private:
    vector<unique_ptr<Customer>> customers; //the bank's customers

    public:
    void AddCustomer(unique_ptr<Customer>customer);
    void printaccounts() const;

    Account* findAccount(const string& accountNumber) const; //finding account by the number, across all customers
    Customer* findCustomer(const string& customerId) const; // by ID, nullptr if none

    bool transferfunds(const string& fromAcc, const string& toAcc, double amount);
    // bool to return false if either account doesn't exist, else if withdrawal over limit/balance

    const vector<unique_ptr<Customer>>&getCustomers() const;
};
#endif