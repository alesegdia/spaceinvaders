#include <memory>

#include "ECSWorld.h"
#include "Components.h"
#include "Systems.h"


ECSWorld::ECSWorld()
{
	pushSystem(std::make_shared<RenderTextSystem>());
	pushSystem(std::make_shared<RenderTextureSystem>());
	pushSystem(std::make_shared<StarFieldSystem>());
}

secs::Entity ECSWorld::MakeEnemyShip(float x, float y)
{
	return processor().addEntity();
}

secs::Entity ECSWorld::MakePlayerShip(float x, float y)
{
	return processor().addEntity();
}

