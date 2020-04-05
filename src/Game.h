#pragma once

#include <aether/aether.h>
#include <memory>

#include "screens/GameplayScreen.h"
#include "screens/MenuScreen.h"
#include "ecs/Systems.h"


void set_hiscore(int hiscore);
int get_hiscore();

class Game : public aether::core::Application
{
public:
	Game(int w, int h)
		: aether::core::Application(w, h)
	{

	}

	virtual int ready(int argc, char** argv)
	{
		setScreen(std::make_shared<MenuScreen>(*this));
		return 0;
	}

};


