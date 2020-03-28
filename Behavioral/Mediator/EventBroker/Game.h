//
//  Game.h
//  DesignPatterns
//
//  Created by Aniket Bhushan on 28/03/20.
//  Copyright © 2020 Aniket Bhushan. All rights reserved.
//

#ifndef Game_h
#define Game_h

#include <boost/signals2.hpp>
#include "Event.h"

struct Game {
    boost::signals2::signal<void(Event*)> events;
};

#endif /* Game_h */
