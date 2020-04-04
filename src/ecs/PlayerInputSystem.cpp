#include "PlayerInputSystem.h"


void PlayerInputSystem::process(double delta, const secs::Entity& e,
	PlayerComponent& pc, MovementComponent& mc, ShootComponent& sc)
{
	sc.shootRequested = aether::core::is_key_down(aether::core::KeyCode::Space);

	bool u, d, l, r;
	u = aether::core::is_key_down(aether::core::KeyCode::Up);
	d = aether::core::is_key_down(aether::core::KeyCode::Down);
	l = aether::core::is_key_down(aether::core::KeyCode::Left);
	r = aether::core::is_key_down(aether::core::KeyCode::Right);

	auto& axis = mc.axis;

	if (u && d) axis.y(0);
	else if (u) axis.y(-1.0f);
	else if (d) axis.y(1.0f);
	else axis.y(0);

	if (l && r) axis.x(0);
	else if (r) axis.x(1.0f);
	else if (l) axis.x(-1.0f);
	else axis.x(0);
}


