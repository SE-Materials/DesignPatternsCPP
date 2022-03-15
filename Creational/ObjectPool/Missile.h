#pragma once
#include "SharedObject.h"

class Missile : public SharedObject
{
public:
	Missile();
	void Update();
	~Missile();
};

