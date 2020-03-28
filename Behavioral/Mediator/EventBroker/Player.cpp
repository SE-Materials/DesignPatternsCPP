//
//  Player.cpp
//  SingleResponsiblity
//
//  Created by Aniket Bhushan on 28/03/20.
//  Copyright © 2020 Aniket Bhushan. All rights reserved.
//

#include "Player.hpp"
#include "PlayerScored.hpp"

Player::Player(std::string &name, Game &game) : m_name(name), m_game(game){
    
}

void Player::Score() { 
    m_goalsScored++;
    PlayerScored ps(m_name, m_goalsScored);
    m_game.events(&ps);
}

