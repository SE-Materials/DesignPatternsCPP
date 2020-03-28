//
//  Coach.cpp
//  SingleResponsiblity
//
//  Created by Aniket Bhushan on 28/03/20.
//  Copyright © 2020 Aniket Bhushan. All rights reserved.
//

#include "Coach.hpp"
#include "PlayerScored.hpp"
#include <iostream>

Coach::Coach(Game &game) : m_game(game){
    game.events.connect([](Event* e){
        PlayerScored* ps = dynamic_cast<PlayerScored*>(e);
        if (ps && ps->GetGoalsScoredSoFar() < 3)
        {
            std::cout << "Coach: Well done, " << ps->GetPlayerName() << std::endl;
        }
    });
}
