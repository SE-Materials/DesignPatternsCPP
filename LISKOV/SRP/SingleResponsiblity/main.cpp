//
//  main.cpp
//  SingleResponsiblity
//
//  Created by Aniket Bhushan on 14/10/19.
//  Copyright © 2019 Aniket Bhushan. All rights reserved.
//

#include <iostream>

struct Journal
{
    std::string title;
    std::vector<std::string> contents;
    
    explicit Journal(const std::string& name) : title(name) {}
    
    void insert(const std::string& c)
    {
        contents.push_back(c);
    }
}

struct Printer {
    <#struct fields#>
};

int main(int argc, const char * argv[]) {
    // insert code here...
    std::cout << "Hello, World!\n";
    return 0;
}
