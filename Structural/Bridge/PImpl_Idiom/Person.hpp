//
//  Person.hpp
//  SingleResponsiblity
//
//  Created by Aniket Bhushan on 17/10/19.
//  Copyright © 2019 Aniket Bhushan. All rights reserved.
//

#ifndef Person_hpp
#define Person_hpp

#include <stdio.h>
#include <string>

struct Person
{
    std::string name;
    
    struct PersonImpl;
    PersonImpl *impl;
    
    Person();
    ~Person();
    
    void greet();
};

#endif /* Person_hpp */
