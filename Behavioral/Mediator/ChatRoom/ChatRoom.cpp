//
//  ChatRoom.cpp
//  SingleResponsiblity
//
//  Created by Aniket Bhushan on 28/03/20.
//  Copyright © 2020 Aniket Bhushan. All rights reserved.
//

#include "ChatRoom.hpp"
#include "Person.hpp"

void ChatRoom::BroadCast(const std::string &origin, const std::string &message) { 
    for (auto& p : m_people)
    {
        if (p.GetName() != origin)
        {
            p.Receive(origin, message);
        }
    }
}

Person ChatRoom::Join(Person &&p) {
    std::string joinMessage = p.GetName() + " joins chat.";
    BroadCast("room", joinMessage);
    
    p.SetRoom(this);
    m_people.emplace_back(p);
    return m_people.back();
}

void ChatRoom::Message(const std::string &origin, const std::string &who, const std::string &message) { 
    auto target = std::find_if(m_people.begin(), m_people.end(), [&](Person& p){
        return p.GetName() == who;
    });
    if (target != m_people.end())
    {
        target->Receive(origin, message);
    }
}


