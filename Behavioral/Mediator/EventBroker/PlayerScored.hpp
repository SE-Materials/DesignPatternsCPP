//
//  PlayerScored.hpp
//  SingleResponsiblity
//
//  Created by Aniket Bhushan on 28/03/20.
//  Copyright © 2020 Aniket Bhushan. All rights reserved.
//

#ifndef PlayerScored_hpp
#define PlayerScored_hpp

#include <iostream>
#include "Event.h"
#include <string>

class PlayerScored : public Event{
    
    int m_goalsScoredSoFar;
    std::string m_playerName;
    
public:
    explicit PlayerScored(std::string&, int);
    
    int GetGoalsScoredSoFar() {return m_goalsScoredSoFar;}
    std::string& GetPlayerName() {return m_playerName;}
    
    void Print() override;
};

#endif /* PlayerScored_hpp */
