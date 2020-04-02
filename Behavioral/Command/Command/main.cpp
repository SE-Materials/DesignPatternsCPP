//
//  main.cpp
//  Command
//
//  Created by Aniket Bhushan on 03/04/20.
//  Copyright © 2020 Aniket Bhushan. All rights reserved.
//

#include <iostream>
#include <vector>

using namespace std;

struct BankAccount {
    int m_balance = 0;
    int m_overDraftLimit = -500;
    
    void Deposit(int amount)
    {
        m_balance += amount;
        cout << "Deposited " << amount << ", balance now " << m_balance << endl;
    }
    
    void WithDraw(int amount)
    {
        if (m_balance - amount >= m_overDraftLimit)
        {
            m_balance -= amount;
            cout << "Withdrew " << amount << ", balance now " << m_balance << endl;
        }
    }
};

struct Command {
    BankAccount& m_account;
    enum Action {deposit, withdraw} m_action;
    
    int m_amount;
    
    Command(BankAccount& account, const Action action, const int amount) :
    m_account(account), m_action(action), m_amount(amount)
    {
    }
    
    void Call() const
    {
        switch (m_action) {
            case deposit:
                m_account.Deposit(m_amount);
                break;
            case withdraw:
                m_account.WithDraw(m_amount);
                break;
            default:
                break;
        }
    }
};

int main(int argc, const char * argv[]) {
    BankAccount ba;
    vector<Command> commands {
        Command{ba, Command::deposit, 100},
        Command{ba, Command::withdraw, 200}
    };
    
    for (auto& cmd : commands)
    {
        cmd.Call();
    }
//    ba.Deposit(100);
//    ba.WithDraw(200);

    return 0;
}
