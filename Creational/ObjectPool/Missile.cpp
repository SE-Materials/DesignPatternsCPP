#include "Missile.h"
#include <iostream>


Missile::Missile()
{
	//std::cout << "+++++ Missile Created" << std::endl;
}


Missile::~Missile()
{
	//std::cout << "~~~~~ Missile Destroyed" << std::endl;
}

void Missile::Update()
{
	std::cout << "->";
}

