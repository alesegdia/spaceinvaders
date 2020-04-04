#pragma once

#include "Components.h"


class MovementSystem : public secs::TypedEntitySystem<MovementComponent, TransformComponent>
{
public:
	void process(double delta, const secs::Entity& e, MovementComponent& mc, TransformComponent& tc) override;
};
