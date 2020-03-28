//
//  main.cpp
//  EventBroker
//
//  Created by Aniket Bhushan on 28/03/20.
//  Copyright © 2020 Aniket Bhushan. All rights reserved.
//

#include <iostream>
#include "Game.h"
#include "Player.hpp"
#include "Coach.hpp"
#include <string>

int main(int argc, const char * argv[]) {
    Game game;
    std::string name = "Aniket";
    
    Player player(name, game);
    Coach coach(game);
    
    player.Score();
    player.Score();
    player.Score();
    player.Score();
    
    return 0;
}

