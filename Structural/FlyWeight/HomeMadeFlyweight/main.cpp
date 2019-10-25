//
//  main.cpp
//  HomeMadeFlyweight
//
//  Created by Aniket Bhushan on 20/10/19.
//  Copyright © 2019 Aniket Bhushan. All rights reserved.
//
#include <iostream>
#include <boost/bimap.hpp>
using namespace boost;

typedef uint32_t key;

struct User
{
    User(const std::string& firstName, const std::string& lastName) : firstName{add(firstName)}, lastName{add(lastName)} {}
    
    const std::string& getFirstName() const
    {
        return names.left.find(firstName)->second;
    }
    
    const std::string& getLastName() const
    {
        return names.left.find(lastName)->second;
    }
    
    friend std::ostream& operator<<(std::ostream& os, const User& obj)
    {
        os << "First name : " << obj.firstName << " " << obj.getFirstName() << " last name : " << obj.lastName << " " << obj.getLastName() << std::endl;
        return os;
    }
    
protected:
    static bimap<key, std::string> names;
    static int seed;
    
    static key add(const std::string& s)
    {
        auto it = names.right.find(s);
        if (it == names.right.end())
        {
            key id = ++seed;
            names.insert(bimap<key, std::string>::value_type(seed, s));
            return id;
        }
        return it->second;
    }
    
    key firstName, lastName;
};

int User::seed {};
bimap<key, std::string> User::names{};

int main(int argc, const char * argv[]) {
    User johnDoe {"John", "Doe"};
    User janeDoe {"Jane", "Doe"};
    
    std::cout << "John : " << johnDoe << std::endl;
    std::cout << "Jane : " << janeDoe << std::endl;
    
    return 0;
}
