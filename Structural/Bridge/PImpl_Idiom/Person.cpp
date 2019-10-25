//
//  Person.cpp
//  SingleResponsiblity
//
//  Created by Aniket Bhushan on 17/10/19.
//  Copyright © 2019 Aniket Bhushan. All rights reserved.
//

#include "Person.hpp"

struct Person::PersonImpl
{
    void greet();
};

void Person::PersonImpl::greet()
{
    std::cout << "Hello, My name is " << name << std::endl;
}

Person::Person() : impl(new PersonImpl)
{
    
}

Person::~Person()
{
    delete impl;
}

void Person::greet()
{
    impl->greet();
}
