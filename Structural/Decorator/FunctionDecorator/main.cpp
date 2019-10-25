//
//  main.cpp
//  FunctionDecorator
//
//  Created by Aniket Bhushan on 19/10/19.
//  Copyright © 2019 Aniket Bhushan. All rights reserved.
//

#include <iostream>
#include <string>

struct Logger
{
    std::function<void()> func;
    std::string name;
    
    Logger(const std::function<void()>& func, const std::string& name) : func{func}, name{name}
    {
    }
    
    void operator()()
    {
        std::cout << "Entering" << std::endl;
        func();
        std::cout << "Exiting" << std::endl;
    }
};

template <typename Func>
struct Logger2
{
    Func func;
    std::string name;
    
    Logger2(const Func& func, const std::string& name) : func{func}, name{name}
    {
    }
    
    void operator()()
    {
        std::cout << "Entering" << std::endl;
        func();
        std::cout << "Exiting" << std::endl;
    }
};

template <typename> struct Logger3;

template <typename R, typename... Args>
struct Logger3<R(Args...)>
{
    std::function<R(Args...)> func;
    std::string name;
    
    Logger3(const std::function<R(Args...)>& func, const std::string& name) : func{func}, name{name}
    {
    }
    
    R operator()(Args ...args)
    {
        std::cout << "Entering " << name << std::endl;
        R result = func(args...);
        std::cout << "Exiting " << name << std::endl;
        return result;
    }
};

template<typename Func>
auto make_logger2(Func func, const std::string& name)
{
    return Logger2<Func> {func, name};
}

template <typename R, typename... Args>
auto make_logger3(R (*func)(Args...), const std::string& name)
{
    return Logger3<R(Args...)> {
        std::function<R(Args...)>(func), name
    };
}

double add(double a, double b)
{
    std::cout << a << "+" << b << "=" << (a+b) << std::endl;
    return a+b;
}

int main(int argc, const char * argv[]) {
    
    Logger logger {[](){std::cout << "Hello" << std::endl;}, "HelloFunc" };
    logger();
    std::cout << std::endl;
    
    auto logger2 = make_logger2([](){std::cout << "Hello" << std::endl;}, "HelloFunc");
    logger2();
    std::cout << std::endl;
    
    auto logger3 = make_logger3(add, "Add");
    auto result = logger3(2, 4);
    std::cout << result << std::endl;
    
    return 0;
}
