#include "StandAtPointBehaviourSystem.h"


void StandAtPointBehaviourSystem::process( double delta, const secs::Entity &e, StandAtPointEnemyBehaviour& sap, TransformComponent& tc )
{
	if (sap.timer < sap.timeTraveling)
	{
		auto step = (sap.pointToStand - sap.fromPosition) / sap.timeTraveling;
		tc.position += step * delta;
		sap.timer += delta;
	}
}

