//
//  Player.hpp
//  SingleResponsiblity
//
//  Created by Aniket Bhushan on 28/03/20.
//  Copyright © 2020 Aniket Bhushan. All rights reserved.
//

#ifndef Player_hpp
#define Player_hpp

#include <stdio.h>
#include <string>
#include "Game.h"

struct Player {
    std::string m_name;
    int m_goalsScored;
    Game& m_game;
    
    explicit Player(std::string& name, Game& game);
    
    void Score();
};

#endif /* Player_hpp */
