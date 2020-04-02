//
//  main.cpp
//  Memento
//
//  Created by Aniket Bhushan on 01/04/20.
//  Copyright © 2020 Aniket Bhushan. All rights reserved.
//

#include <iostream>

using namespace std;

class Memento {
    int m_balance;
    
public:
    Memento(int balance) : m_balance{balance}{}
    friend class BankAccount;
};

class BankAccount {
    int m_balance;
    
public:
    BankAccount(int balance) : m_balance {balance}
    {}
    
    void Restore(Memento& m)
    {
        m_balance = m.m_balance;
    }
    
    Memento Deposit(int amount)
    {
        m_balance += amount;
        return {m_balance};
    }
    
    friend ostream& operator<<(ostream& os, const BankAccount& ob)
    {
        return os << "Balance : " << ob.m_balance;
    }
};
            
int main(int argc, const char * argv[]) {
    BankAccount ba{100};

    auto m1 = ba.Deposit(10);
    auto m2 = ba.Deposit(50);

    cout << ba << endl;

    ba.Restore(m1);
    cout << ba << endl;
        
        ba.Restore(m2);
    cout << ba << endl;
    return 0;
}
