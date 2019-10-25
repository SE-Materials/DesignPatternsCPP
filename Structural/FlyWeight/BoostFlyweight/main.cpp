//
//  main.cpp
//  BoostFlyweight
//
//  Created by Aniket Bhushan on 20/10/19.
//  Copyright © 2019 Aniket Bhushan. All rights reserved.
//

#include <iostream>
#include <boost/flyweight.hpp>

struct User2
{
    boost::flyweight<std::string> firstName, lastName;
    
    User2(const std::string& firstName, const std::string& lastName) : firstName{firstName}, lastName{lastName} {}
    
    friend std::ostream& operator<<(std::ostream& os, const User2& obj)
    {
        return os << "First Name : " << obj.firstName << " last name : " << obj.lastName << std::endl;
    }
    
};

int main(int argc, const char * argv[]) {
    
    User2 johnDoe {"John", "Doe"};
    User2 janeDoe {"Jane", "Doe"};
    
    std::cout << johnDoe << std::endl;
    std::cout << janeDoe << std::endl;
    
    std::cout << std::boolalpha << (&janeDoe.lastName.get() == &johnDoe.lastName.get()) << std::endl;
    
    return 0;
}
