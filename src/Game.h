#include <aether/aether.h>
#include <memory>

#include "screens/GameplayScreen.h"
#include "ecs/Systems.h"


class Game : public aether::core::Application
{
public:
	Game(int w, int h)
		: aether::core::Application(w, h)
	{

	}

	virtual int ready(int argc, char** argv)
	{
		setScreen(std::make_shared<GameplayScreen>());
		return 0;
	}

};


