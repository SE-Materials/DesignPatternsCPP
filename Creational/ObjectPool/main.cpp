#include <iostream>
#include <thread>
#include <chrono>

#include "ObjectPool.h"
#include "Missile.h"
#include "Alien.h"

using namespace std::chrono_literals;

std::vector<SharedObjectPtr> objects{};

void Fire()
{
	objects.push_back(ObjectPool::AcquireInstance("missile"));
	objects.push_back(ObjectPool::AcquireInstance("alien"));
}

void Animate()
{
	for (auto& m : objects)
		m->Update();
}

void Explode()
{
	std::cout << "X" << std::endl;
	for (auto& m : objects)
		m->ClearIsUsed();
	
	std::this_thread::sleep_for(1s);
	std::cout << "\n\n";
}

//---------------------------------------------------------------------
void GameLoop()
{
	int loop{ 2 };
	int counter{ 0 };
	
	while (loop != 0) {
		++counter;
		if (counter == 1) 
		{
			Fire();
		}

		if (counter >= 1 && counter <= 5)
		{
			Animate();
		}

		if (counter > 5)
		{
			Explode();
			counter = 0;
			--loop;
		}

		std::this_thread::sleep_for(1s);
	}
}

int main()
{
	ObjectPool::RegisterCreator("missile", []() {return std::make_shared<Missile>(); });
	ObjectPool::RegisterCreator("alien", []() {return std::make_shared<Alien>(); });

	GameLoop();
	return 0;
}