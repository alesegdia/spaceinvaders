#include "SinusoidalEnemyBehaviourSystem.h"


void SinusoidalEnemyBehaviourSystem::process( double delta, const secs::Entity &e, SinusoidalEnemyBehaviour& seb, TransformComponent& tc )
{
	seb.time += delta;
	tc.position.x(seb.offset + seb.amplitude * sin(seb.time * seb.period * 1e-6));
}

