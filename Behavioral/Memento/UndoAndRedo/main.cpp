//
//  main.cpp
//  UndoAndRedo
//
//  Created by Aniket Bhushan on 01/04/20.
//  Copyright © 2020 Aniket Bhushan. All rights reserved.
//

#include <iostream>
#include <vector>
#include <memory>

using namespace std;

// Serialize it to database, in case it is heavier
class Memento {
    int m_balance;
    
public:
    Memento(int balance) : m_balance{balance} {}
    
    friend class BankAccount1;
    friend class BankAccount2;
};

class BankAccount1 {
    int m_balance;
    
public:
    BankAccount1(int balance) : m_balance{balance} {}
    Memento Deposit(int amount) { m_balance += amount; return {m_balance};}
    void Restore(const Memento& m)
    {
        m_balance = m.m_balance;
    }
    friend ostream& operator<<(ostream& os, const BankAccount1 ob)
    {
        return os << "Balance : " << ob.m_balance;
    }
};
        
class BankAccount2 {
    int m_balance;
    vector<shared_ptr<Memento>> m_changes;
    int m_current;
        
public:
    BankAccount2(int balance) : m_balance{balance}
    {
        m_changes.emplace_back(make_shared<Memento>(m_balance));
        m_current = 0;
    }
    shared_ptr<Memento> Deposit(int amount)
    {
        m_balance += amount;
        auto m = make_shared<Memento>(m_balance);
        m_changes.push_back(m);
        ++m_current;
        return m;
    }
     
    shared_ptr<Memento> Undo()
    {
        if (m_current > 0)
        {
            --m_current;
            auto m = m_changes[m_current];
            m_balance = m->m_balance;
            return m;
        }
        return {};
    }
        
    shared_ptr<Memento> Redo()
    {
        if (m_current + 1 < m_changes.size())
        {
            ++m_current;
            auto m = m_changes[m_current];
            m_balance = m->m_balance;
            return m;
        }
        return {};
    }
        
    friend ostream& operator<<(ostream& os, const BankAccount2 ob)
    {
        return os << "Balance : " << ob.m_balance;
    }
};

int main(int argc, const char * argv[]) {
        
        BankAccount2 ba{100};
        ba.Deposit(50);
        ba.Deposit(25);
        
        cout << ba << endl;
        
        ba.Undo();
        cout << "Undo1 : " << ba << endl;
        ba.Undo();
        cout << "Undo2 : " << ba << endl;
        
        ba.Redo();
        cout << "Redo1 : " << ba << endl;
    return 0;
}
