#include <aether/aether.h>
#include <memory>

#include "ecs/ECSWorld.h"
#include "ecs/Systems.h"
#include "Game.h"


int main(int argc, char** argv)
{
	return Game(800, 600).exec(argc, argv);
}
