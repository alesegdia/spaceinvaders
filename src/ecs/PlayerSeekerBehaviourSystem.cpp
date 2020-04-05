#include "PlayerSeekerBehaviourSystem.h"


void PlayerSeekerBehaviourSystem::process( double delta, const secs::Entity &e, PlayerSeekerEnemyBehaviour& pseb, TransformComponent& tc )
{
	auto& ptc = component<TransformComponent>(m_playerEntity);
	auto deltaPos = ptc.position.x() - tc.position.x();
	tc.position.x(tc.position.x() + deltaPos * 0.02f);
}

