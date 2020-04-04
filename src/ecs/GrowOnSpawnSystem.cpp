#include "GrowOnSpawnSystem.h"


void AsteroidSystem::process( double delta, const secs::Entity &e,
	AsteroidComponent& gc, TransformComponent& tc )
{
	if (tc.scale < gc.endScale)
	{
		float step = (gc.endScale - gc.startScale) / gc.scalingTime;
		tc.scale = tc.scale + step * delta;
	}
	tc.rotation += gc.rotationSpeed * delta;
}

