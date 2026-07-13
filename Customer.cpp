#include "Customer.h"

Customer::Customer(const string& customerId, const string& name)
    :CustomerId(customerId), name(name) {}

void Customer::addAccount(unique_ptr<Account> account) {
    accounts.push_back(move(account));
}

Account* Customer::findAccount(const string& accountNumber) const {
    for (const auto& acc:accounts) {
        if (acc->getAccountNumber()==accountNumber) {
            return acc.get();
        }
    }
    return nullptr;
}

string Customer::getName() const{
    return name;
}

string Customer::getCustomerId() const{
    return CustomerId;
}

const vector<unique_ptr<Account>>& Customer::getAccounts() const{
    return accounts;
}
