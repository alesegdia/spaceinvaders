#pragma once

#include "Components.h"

class PlayerInputSystem : public secs::TypedEntitySystem<PlayerComponent, MovementComponent, ShootComponent>
{
public:
	void process(double delta, const secs::Entity& e, PlayerComponent& pc, MovementComponent& aic, ShootComponent& sc) override;
};

