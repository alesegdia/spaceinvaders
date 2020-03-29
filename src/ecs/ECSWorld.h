#include <secs/secs.h>

class BoardSystem;

class ECSWorld : public secs::Engine
{
public:
	ECSWorld();

	secs::Entity MakePlayerShip(float x, float y);
	secs::Entity MakeEnemyShip(float x, float y);

};