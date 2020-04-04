#include "DestroyOnExitScreen.h"


void DestroyOnExitScreen::process(double delta, const secs::Entity& e, TransformComponent& tc)
{
	if (tc.position.y() < -100.0f || tc.position.y() > 700.0f)
	{
		processor()->removeEntity(e);
		std::cout << "Removing because outside of screen!" << std::endl;
	}
}

