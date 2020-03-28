//
//  ChatRoom.hpp
//  SingleResponsiblity
//
//  Created by Aniket Bhushan on 28/03/20.
//  Copyright © 2020 Aniket Bhushan. All rights reserved.
//

#ifndef ChatRoom_hpp
#define ChatRoom_hpp

#include <vector>

class Person;

class ChatRoom {
    std::vector<Person> m_people;
    
public:
    
    void BroadCast(const std::string& origin, const std::string& message);
    Person Join(Person&& p);
    void Message(const std::string& origin, const std::string& who, const std::string& message);
};

#endif /* ChatRoom_hpp */
