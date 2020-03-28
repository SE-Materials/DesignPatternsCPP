//
//  Coach.hpp
//  SingleResponsiblity
//
//  Created by Aniket Bhushan on 28/03/20.
//  Copyright © 2020 Aniket Bhushan. All rights reserved.
//

#ifndef Coach_hpp
#define Coach_hpp

#include <stdio.h>
#include "Game.h"

struct Coach {
    Game& m_game;
    
    explicit Coach(Game& game);
    
};

#endif /* Coach_hpp */
