//
//  Person.hpp
//  SingleResponsiblity
//
//  Created by Aniket Bhushan on 28/03/20.
//  Copyright © 2020 Aniket Bhushan. All rights reserved.
//

#ifndef Person_hpp
#define Person_hpp

#include "ChatRoom.hpp"
#include <string>
#include <vector>

class Person {
    std::string m_name;
    ChatRoom* m_chatRoom = nullptr;
    std::vector<std::string> m_chatLogs;
    
public:
    explicit Person(const std::string& name);
    
    const std::string& GetName() {return m_name;}

    void SetRoom(ChatRoom* room) {m_chatRoom = room;}
    
    void Say(const std::string& message);
    
    void Receive(const std::string& origin, const std::string& message);
    
    void PM(const std::string& who, const std::string& message);
};

#endif /* Person_hpp */
