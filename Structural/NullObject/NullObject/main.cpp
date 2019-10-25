//
//  main.cpp
//  NullObject
//
//  Created by Aniket Bhushan on 20/10/19.
//  Copyright © 2019 Aniket Bhushan. All rights reserved.
//

#include <iostream>
#include <boost/lexical_cast.hpp>

struct Logger {
    virtual ~Logger() = default;
    virtual void info(const std::string& s) = 0;
    virtual void warn(const std::string& s) = 0;
};


struct BankAccount
{
    std::shared_ptr<Logger> log;
    
    std::string name;
    int balance {0};
    
    BankAccount(const std::shared_ptr<Logger>& log, const std::string& name, int balance) : log{log}, name{name}, balance{balance} {}
    
    void deposit(int amount)
    {
        balance += amount;
        log->info("Desposited $" + boost::lexical_cast<std::string>(amount) + " to " + name + ", balance is now $" + boost::lexical_cast<std::string>(balance));
    }
    
    void withdraw(int amount)
    {
        if (balance >= amount)
        {
            balance -= amount;
            log->info("Withdrew $" + boost::lexical_cast<std::string>(amount) + " from " + name + ", balance is now  $" + boost::lexical_cast<std::string>(balance));
        }
        else
        {
            log->warn("Tried to Withdraw $" + boost::lexical_cast<std::string>(amount) + " from " + name + ", but couldn't due to low balance");
        }
    }
    
};

struct ConsoleLogger : Logger {
    void info(const std::string& s) override
    {
        std::cout << "INFO : " << s << std::endl;
    }
    
    void warn(const std::string& s) override
    {
        std::cout << "** WARNING : " << s << std::endl;
    }
};

struct NullLogger : Logger {
    void info(const std::string& s) override
    {
        
    }
    
    void warn(const std::string& s) override
    {
        
    }
};

int main(int argc, const char * argv[]) {
        auto logger = std::make_shared<ConsoleLogger>();
    
    // We can't do ! Null exception
    //    std::shared_ptr<Logger> logger;
    
    // This will work
    //    auto logger = std::make_shared<NullLogger>();
    
    // What if we want count of number of warnings ?
    // We can return int from warn method
    BankAccount bankAccount{logger, "primary account", 1000};
    
    bankAccount.deposit(1000);
    bankAccount.withdraw(2500);
    bankAccount.withdraw(1000);
    return 0;
}
