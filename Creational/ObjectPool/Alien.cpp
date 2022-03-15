#include "Alien.h"

#include <iostream>

Alien::Alien()
{
	//std::cout << "+++++ Alien constructed" << std::endl;
}


Alien::~Alien()
{
	//std::cout << "~~~~~ Alien destroyed" << std::endl;
}


void Alien::Update()
{
	std::cout << "@";
}

