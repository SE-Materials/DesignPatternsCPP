//
//  main.cpp
//  CompositeCommand
//
//  Created by Aniket Bhushan on 03/04/20.
//  Copyright © 2020 Aniket Bhushan. All rights reserved.
//

#include <iostream>
#include <vector>
#include <algorithm>

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

struct ICommand {
    virtual ~ICommand() = default;
    virtual void Call() const = 0;
    virtual void Undo() const = 0;
};

struct Command : ICommand {
    BankAccount& m_account;
    enum Action {deposit, withdraw} m_action;
    
    int m_amount;
    
    Command(BankAccount& account, const Action action, const int amount) :
    m_account(account), m_action(action), m_amount(amount)
    {
    }
    
    void Call() const override
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
    
    void Undo() const override
    {
        switch (m_action) {
            case withdraw:
                m_account.Deposit(m_amount);
                break;
            case deposit:
                m_account.WithDraw(m_amount);
                break;
            default:
                break;
        }
    }
};

struct CommandList : vector<Command>, ICommand {
    CommandList(const initializer_list<value_type>& iList) : vector<Command>(iList)
    {
    }
    
    void Call() const override
    {
        for (auto& cmd : *this)
        {
            cmd.Call();
        }
    }
    
    void Undo() const override
    {
        for_each(rbegin(), rend(),
                 [](const Command& cmd) { cmd.Undo(); });
    }
};

int main(int argc, const char * argv[]) {
    BankAccount ba;
    CommandList commands {
        Command{ba, Command::deposit, 100},
        Command{ba, Command::withdraw, 200}
    };
    
    commands.Call();
    commands.Undo();
    
    
    return 0;
}
