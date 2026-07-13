# Bank Account Management System (C++)

A command-line bank account management system built in C++ to practice and demonstrate core object-oriented design principles-inheritance, polymorphism, abstraction, and composition.

## Features

- Create and manage multiple customers, each with multiple accounts
- Two account types with genuinely different behavior: **Savings** (no overdraft, earns interest) and **Checking** (allows overdraft up to a limit, no interest)
- Deposit, withdraw, check balance, and view per-account transaction history
- Fund transfers between any two accounts, with atomic all-or-nothing semantics (if the withdrawal side fails, the deposit side never happens)
- Interest calculation, resolved polymorphically per account type
- Menu-driven CLI-create accounts and customers interactively, or seed data on startup

## OOP Concepts Demonstrated

| Concept | Where |
|---|---|
| **Encapsulation** | `balance` and transaction history are protected/private, only reachable through class methods |
| **Inheritance** | `SavingsAccount`, `CheckingAccount` extend `Account`; `Deposit`, `Withdrawal`, `Transfer` extend `Transaction` |
| **Abstraction** | `Account` and `Transaction` are abstract base classes (pure virtual methods) — neither can be instantiated directly |
| **Polymorphism** | `applyWithdrawal()` and `calculateInterest()` are virtual, so the correct account-specific rule runs even when called through a base `Account*` |
| **Composition** | `Bank` owns `Customer`s, `Customer` owns `Account`s, `Account` owns its `Transaction` history — each via `std::vector<std::unique_ptr<T>>` |

## Project Structure

```
├── main.cpp              # CLI entry point and menu loop
├── Bank.h / Bank.cpp      # Owns all customers; cross-account operations (transfers, lookups)
├── Customer.h / .cpp      # Owns a customer's accounts; per-customer account lookup
├── Account.h / .cpp       # Abstract base class — balance, deposit/withdraw core logic, history
├── SavingsAccount.h / .cpp   # No overdraft, earns interest
├── CheckingAccount.h / .cpp  # Allows overdraft up to a limit, earns no interest
└── Transaction.h / .cpp   # Abstract Transaction base + Deposit, Withdrawal, Transfer
```

## Getting Started

### Prerequisites

- A C++17-compatible compiler (e.g. `g++` 7 or newer)

### Build

```bash
g++ -std=c++17 -Wall -Wextra *.cpp -o bank_demo
```

### Run

```bash
./bank_demo
```

## Usage

On startup, the program seeds a couple of demo customers and accounts so the menu has something to operate on immediately. From there:

```
== Bank Management System ==
1. Deposit
2. Withdraw
3. Check Balance
4. Transfer Funds
5. View Transaction History
6. Calculate Interest
7. Create New Account
8. List All Accounts
9. Exit
```

Accounts are looked up by account number, which you'll be prompted for in each operation. Option 7 lets you create a brand-new customer on the spot (if the ID you enter doesn't already exist) and open a Savings or Checking account under them.

## Design Notes

A few decisions worth calling out, since they weren't accidents:

- **`Account` is abstract on purpose.** Every account has to be *some* concrete type (Savings or Checking); a bare, typeless `Account` doesn't make sense as a real object, so the language enforces that at compile time via a pure virtual method (`calculateInterest()`).
- **Only the piece that actually varies per account type is virtual.** `applyWithdrawal()` is virtual (Savings blocks overdraft, Checking allows it); `withdraw()` itself just calls that and logs the result. It doesn't need to be virtual, because logging behavior never differs by account type.
- **Transfers don't reuse `withdraw()`/`deposit()` directly.** They go through `debitForTransfer()`/`creditForTransfer()` instead, which share the exact same rule-checking (so a `CheckingAccount`'s overdraft limit is still respected mid-transfer) but log a single `Transfer` entry instead of a `Withdrawal` + `Deposit` pair, so history reads cleanly with no duplicate lines.
- **Ownership is modeled with `std::unique_ptr`, not because of polymorphism alone.** `Customer`'s accounts need pointer stability, code that creates a `Customer`, keeps a raw pointer to it, and then inserts it into `Bank`'s customer list needs that pointer to stay valid even if the underlying vector reallocates. `vector<unique_ptr<T>>` guarantees that; `vector<T>` does not.

## Known Limitations

- All data lives in memory for the duration of one run. Any customer or account created through the menu disappears when the program exits, only the hardcoded seed data reappears on the next run.
- Interest is calculated on demand, not automatically applied to the balance over time.

## Possible Future Improvements

- Save/load accounts and transaction history to a file (or a real database) so data survives between runs
- Input validation hardening (e.g. rejecting non-numeric account IDs more gracefully)
- Account closing / deletion
- Unit tests for the account and transfer logic
