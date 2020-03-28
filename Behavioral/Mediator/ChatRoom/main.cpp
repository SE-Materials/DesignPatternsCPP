//
//  main.cpp
//  ChatRoom
//
//  Created by Aniket Bhushan on 28/03/20.
//  Copyright © 2020 Aniket Bhushan. All rights reserved.
//

#include <iostream>
#include "Person.hpp"
#include "ChatRoom.hpp"

int main(int argc, const char * argv[]) {
    ChatRoom room;
    
    auto aniket = room.Join(Person{"Aniket"});
    auto anchit = room.Join(Person("Anchit"));
    auto ankita = room.Join(Person("Ankita"));
    
    aniket.Say("Hi Everyone!");
    aniket.PM("Ankita", "Hi ankita!");
    
    return 0;
}
