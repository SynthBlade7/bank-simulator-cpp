#include "Bank.h"
#include "SavingsAccount.h"
#include "CheckingAccount.h"
#include <iostream>
#include <vector>
#include <string>
#include <memory>    
#include <algorithm> 
#include <limits>
using namespace std;

void printMenu() {
    cout << "\n== Bank Management System ==\n";
    cout << "1. Deposit\n";
    cout << "2. Withdraw\n";
    cout << "3. Check Balance\n";
    cout << "4. Transfer Funds\n";
    cout << "5. View Transaction History\n";
    cout << "6. Calculate Interest\n";
    cout << "7. Create New Account\n";
    cout << "8. List All Accounts\n";
    cout << "9. Exit\n";
    cout << "Choose an option: ";
}

string promptAccountNumber(const string& label = "account number") {
    string accNum;
    cout << "Enter "<< label << ": ";
    cin >> accNum;
    return accNum;
}

int main() {
    Bank bank;

    //demo data so the menu has something to operate on right away.
    auto customer1 = make_unique<Customer>("001", "A");
    customer1->addAccount(make_unique<SavingsAccount>("SAV1001", "A", 5000.0, 0.04));
    customer1->addAccount(make_unique<CheckingAccount>("CHK1001", "A", 1000.0, 500.0));
    bank.AddCustomer(move(customer1));

    auto customer2 = make_unique<Customer>("002", "B");
    customer2->addAccount(make_unique<SavingsAccount>("SAV1002", "B", 3000.0, 0.04));
    bank.AddCustomer(move(customer2));

    cout << "Demo accounts loaded: SAV1001, CHK1001 (A), SAV1002 (B)\n";

    int choice = 0;
    while (true) {
        printMenu();
        cin >> choice;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Please enter a number.\n";
            continue;
        }

        if (choice == 9) {
            cout<<"Goodbye!\n";
            break;
        }

        double amount = 0;
        string accNum, toAccNum;
        Account* acc = nullptr;

        switch (choice) {
            case 1:
                accNum = promptAccountNumber();
                acc = bank.findAccount(accNum);
                if (!acc) { cout << "Account not found.\n"; break; }
                cout<<"Enter deposit amount: ";
                cin>>amount;
                try{
                    acc->deposit(amount);
                    cout << "Deposited. New balance: " << acc->getBalance() << "\n";
                } catch (const exception& e) {
                    cout << "Error: " << e.what() << "\n";
                }
                break;

            case 2:
                accNum = promptAccountNumber();
                acc = bank.findAccount(accNum);
                if (!acc) {cout << "Account not found.\n"; break; }
                cout << "Enter withdrawal amount: ";
                cin >> amount;
                try {
                    /* acc is typed as Account*, but this calls whichever
                    withdraw() the object's ACTUAL type defines — decided at runtime*/
                    if (acc->withdraw(amount)) {
                        cout << "Withdrawn. New balance: " << acc->getBalance() << "\n";
                    } else {
                        cout << "Withdrawal denied (insufficient funds / over limit).\n";
                    }
                } catch (const exception& e) {
                    cout << "Error: " << e.what() << "\n";
                }
                break;

            case 3:
                accNum = promptAccountNumber();
                acc = bank.findAccount(accNum);
                if (!acc) { cout << "Account not found.\n"; break; }
                cout << "Balance: " << acc->getBalance() << "\n";
                break;

            case 4:
                accNum = promptAccountNumber("source account number");
                toAccNum = promptAccountNumber("destination account number");
                cout << "Enter transfer amount: ";
                cin >> amount;
                if (bank.transferfunds(accNum, toAccNum, amount)) {
                    cout << "Transfer successful.\n";
                } else {
                    cout << "Transfer failed (check account numbers and balance).\n";
                }
                break;

            case 5:
                accNum = promptAccountNumber();
                acc = bank.findAccount(accNum);
                if (!acc) { cout << "Account not found.\n"; break; }
                acc->printHistory();
                break;

            case 6:
                accNum = promptAccountNumber();
                acc = bank.findAccount(accNum);
                if (!acc) { cout << "Account not found.\n"; break; }
                /* Similar to withdraw(), calculateInterest() is pure
                virtual on Account, so this resolves to SavingsAccount's
                or CheckingAccount's version depending on what acc
                actually points to.*/
                cout << "Interest: " << acc->calculateInterest() << "\n";
                break;

            case 7: {
                string custId;
                cout << "Enter customer ID (existing or new): ";
                cin >> custId;

                Customer* cust = bank.findCustomer(custId);
                if (!cust) {
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    string custName;
                    cout << "No customer with that ID yet. Enter name for new customer: ";
                    getline(cin, custName);
                    auto newCust = make_unique<Customer>(custId, custName);
                    cust = newCust.get(); // keep a raw pointer before ownership moves into bank
                    bank.AddCustomer(move(newCust));
                    cout << "Created new customer " << custId << " (" << custName << ").\n";
                }

                string newAccNum;
                cout << "Enter new account number: ";
                cin >> newAccNum;

                if (bank.findAccount(newAccNum) != nullptr) {
                    cout << "An account with that number already exists.\n";
                    break;
                }

                int type = 0;
                cout << "Account type (1 = Savings, 2 = Checking): ";
                cin >> type;

                double initial = 0;
                cout << "Enter initial balance: ";
                cin >> initial;

                if (type == 1) {
                    double rate = 0;
                    cout << "Enter interest rate (e.g. 0.04 for 4%): ";
                    cin >> rate;
                    cust->addAccount(make_unique<SavingsAccount>(newAccNum, cust->getName(), initial, rate));
                } else {
                    double limit = 0;
                    cout << "Enter overdraft limit: ";
                    cin >> limit;
                    cust->addAccount(make_unique<CheckingAccount>(newAccNum, cust->getName(), initial, limit));
                }

                cout << "Account " << newAccNum << " created for " << cust->getName() << ".\n";
                break;
            }

            case 8:
                bank.printaccounts();
                break;

            default:
                cout << "Invalid option, try again.\n";
        }
    }

    return 0;
}