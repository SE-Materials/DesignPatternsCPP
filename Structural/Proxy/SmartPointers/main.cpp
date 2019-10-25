//
//  main.cpp
//  SmartPointers
//
//  Created by Aniket Bhushan on 20/10/19.
//  Copyright © 2019 Aniket Bhushan. All rights reserved.
//

#include <iostream>

struct BankAccount {
    virtual ~BankAccount() = default;
    virtual void deposit(int amount) = 0;
    virtual void withdraw(int amount) = 0;
};

struct CurrentAccount : BankAccount
{
    explicit CurrentAccount(const int balance ) : balance(balance)
    {}
    
    void deposit(int amount) override
    {
        balance += amount;
    }
    
    void withdraw(int amount) override
    {
        if (amount <= balance)
            balance -= amount;
    }

    friend std::ostream& operator<<(std::ostream& os, const CurrentAccount& obj)
    {
        return os << "balance : " << obj.balance;
    }
    
private:
    int balance;
};

void smart_pointers()
{
    BankAccount* a = new CurrentAccount{123};
    a->deposit(321);
    delete a;
    
    // Proxy class shared_ptr
    std::shared_ptr<CurrentAccount> b = std::make_shared<CurrentAccount>(123);
    b->deposit(321);
    CurrentAccount* underlying = b.get();
    
    std::cout << *b << std::endl;
}


int main(int argc, const char * argv[]) {
    smart_pointers();
    return 0;
}
