#include "Transaction.h"
using namespace std;

Transaction::Transaction(double amount):amount(amount){}
double Transaction::getAmount()const{
    return amount;
}

Deposit::Deposit(double amount):Transaction(amount){}
Withdrawal::Withdrawal(double amount):Transaction(amount){}

string Deposit::describe() const{
    return "Deposit: +"+to_string(amount);
}
string Withdrawal::describe() const{
    return "Withdrawal: -"+to_string(amount);
}

Transfer::Transfer(double amount, const string& counterpartyAccount, bool isIncoming): Transaction(amount), counterpartyAccount(counterpartyAccount), isIncoming(isIncoming){}
string Transfer::describe() const {
    if (isIncoming) {
        return "Transfer: +" + std::to_string(amount) + " from " + counterpartyAccount;
    }
    return "Transfer: -" + std::to_string(amount) + " to " + counterpartyAccount;
}