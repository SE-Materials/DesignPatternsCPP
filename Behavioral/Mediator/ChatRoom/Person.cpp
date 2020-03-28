//
//  Person.cpp
//  SingleResponsiblity
//
//  Created by Aniket Bhushan on 28/03/20.
//  Copyright © 2020 Aniket Bhushan. All rights reserved.
//

#include "Person.hpp"
#include <iostream>

Person::Person(const std::string& name) : m_name(name)
{
}

void Person::Say(const std::string &message)
{
    m_chatRoom->BroadCast(m_name, message);
}

void Person::Receive(const std::string &origin, const std::string &message)
{ 
    std::string displayMessage;
    displayMessage += "[" + m_name + "'s chat session] " + origin + ": \"" + message + "\"";
    std::cout << displayMessage << std::endl;
}


void Person::PM(const std::string& who, const std::string &message)
{
    m_chatRoom->Message(m_name, who, message);
}
