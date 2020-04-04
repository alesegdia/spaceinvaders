#pragma once

#include "Components.h"


class ShootingSystem : public secs::TypedEntitySystem<ShootComponent>
{
public:
	void process(double delta, const secs::Entity& e, ShootComponent& sc) override;
};
