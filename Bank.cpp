#include "Bank.h"
#include <iostream>

void Bank::AddCustomer(unique_ptr<Customer> customer) {
    customers.push_back(move(customer));
}

const vector<unique_ptr<Customer>>& Bank::getCustomers() const {
    return customers;
}

Account* Bank::findAccount(const string& accountNumber) const {
    for (const auto& cust : customers) {
        Account* acc = cust->findAccount(accountNumber); // findAccount of customer class
        if (acc != nullptr) {
            return acc;
        }
    }
    return nullptr;
}

Customer* Bank::findCustomer(const string& customerId) const {
    for (const auto& cust : customers) {
        if (cust->getCustomerId() == customerId) {
            return cust.get();
        }
    }
    return nullptr;
}

void Bank::printaccounts() const {
    cout << "All customers & accounts \n";
    if (customers.empty()) {
        cout<< "(no customers yet)\n";
        return;
    }
    for (const auto& cust : customers) {
        cout << cust->getCustomerId() << "-" << cust->getName() << "\n";
        for (const auto& acc : cust->getAccounts()) {
            cout<<"   "<<acc->getAccountNumber() << " | balance: " << acc->getBalance() << "\n";
        }
    }
}

bool Bank::transferfunds(const string& fromAccNum, const string& toAccNum, double amount) {
    Account* fromAcc = findAccount(fromAccNum);
    Account* toAcc = findAccount(toAccNum);

    if (fromAcc == nullptr||toAcc == nullptr) {
        return false;
    }

    /* withdrawal first, fromAcc->withdraw(amount) is a virtual call, so it
    calls  whatever rule the ACTUAL account type enforces 
    (Savings blocks overdraft, Checking allows it up to its limit)
     without Bank needing to know which one it is.*/

    if (!fromAcc->debitForTransfer(amount, toAccNum))  {
        return false; // nothing touched on the other side
    }
    //inorder to avoid double logging we do not use withdraw and deposit, but rather new functions

    toAcc->creditForTransfer(amount, fromAccNum);

    // fromAcc->logTransfer(amount, toAccNum, false);
    // toAcc->logTransfer(amount, fromAccNum, true);

    return true;
}
