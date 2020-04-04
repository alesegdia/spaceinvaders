#include "ShootingSystem.h"


void ShootingSystem::process(double delta, const secs::Entity& e, ShootComponent& sc)
{
	if (sc.nextShootAvailable)
	{
		sc.nextShootAvailable -= delta;
	}

	if (sc.shootRequested && sc.nextShootAvailable <= 0.0f )
	{
		sc.shootCallback();
		sc.nextShootAvailable = sc.shootingRate;
	}
}

