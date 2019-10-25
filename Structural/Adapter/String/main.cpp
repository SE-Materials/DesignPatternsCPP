//
//  main.cpp
//  String
//
//  Created by Aniket Bhushan on 16/10/19.
//  Copyright © 2019 Aniket Bhushan. All rights reserved.
//

#include <iostream>
#include <vector>
#include <string>
#include <boost/algorithm/string.hpp>

// Instead of this create an adapter class 'String'
/*
 boost::to_lower(s);

std::vector<std::string> parts;
boost::split(parts, s, boost::is_any_of(" "));
*/

class String
{
    std::string s;
    
public:
    
    String(const std::string& other) : s(other) {}
    
    String to_lower()
    {
        boost::to_lower(s);
        return {s};
    }
    
    std::vector<std::string> split(const std::string& delimeter = " ")
    {
        std::vector<std::string> parts;
        boost::split(parts, s, boost::is_any_of(delimeter), boost::token_compress_on);
        return parts;
    }
};

int main(int argc, const char * argv[]) {
    String s {"Hello world"};
    
    auto parts = s.to_lower().split();
    
    for (const auto& p : parts)
        std::cout << p << std::endl;
    
    return 0;
}
