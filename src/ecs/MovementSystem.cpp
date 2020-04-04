#include "MovementSystem.h"


void MovementSystem::process(double delta, const secs::Entity& e, MovementComponent& mc, TransformComponent& tc)
{
	tc.position += mc.axis * mc.speed;
}

