//
//  PlayerScored.cpp
//  SingleResponsiblity
//
//  Created by Aniket Bhushan on 28/03/20.
//  Copyright © 2020 Aniket Bhushan. All rights reserved.
//

#include "PlayerScored.hpp"



PlayerScored::PlayerScored(std::string& playerName, int goalScoredSoFar) : m_playerName{playerName}, m_goalsScoredSoFar(goalScoredSoFar)
{
}

void PlayerScored::Print()
{ 
    std::cout << m_playerName <<  " has scored ! (Their " << m_goalsScoredSoFar << " goal.)";
}



