//
//  main.cpp
//  Expression
//
//  Created by Aniket Bhushan on 17/10/19.
//  Copyright © 2019 Aniket Bhushan. All rights reserved.
//

#include <iostream>
#include <vector>
#include <boost/accumulators/accumulators.hpp>
#include <boost/accumulators/statistics.hpp>

using namespace boost::accumulators;

struct Expression
{
    virtual double eval() = 0;
    virtual void collect(std::vector<double>& v) = 0;
};

struct Literal : Expression
{
    double value;
    
    explicit Literal(const double value) : value(value)
    {
        
    }
    
    double eval() override
    {
        return value;
    }
    
    void collect(std::vector<double>& v) override
    {
        v.push_back(value);
    }
    
};

struct AdditionExpression : Expression
{
    std::shared_ptr<Expression> left, right;
    
    AdditionExpression(const std::shared_ptr<Expression>& left, const std::shared_ptr<Expression>& right) : left{left}, right{right}
    {
        
    }
    
    double eval() override
    {
        return left->eval() + right->eval();
    }
    
    void collect(std::vector<double>& v) override
    {
        left->collect(v);
        right->collect(v);
    }
};

int main(int argc, const char * argv[]) {
    
    AdditionExpression sum {
        std::make_shared<Literal>(2),
        std::make_shared<AdditionExpression>(std::make_shared<Literal>(3), std::make_shared<Literal>(4))
    };
    
    std::cout << "Sum : " << sum.eval() << std::endl;
    
    std::vector<double> elements;
    sum.collect(elements);
    
    for (const auto& v : elements)
        std::cout << v << " ";
    std::cout << std::endl;
    
    accumulator_set<double, stats<tag::mean>> acc;
    for (auto x : elements)
        acc(x);

    std::cout << "Average is " << mean(acc) << std::endl;
     
    return 0;
}
