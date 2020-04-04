#pragma once

#include <secs/secs.h>
#include "Components.h"


class ConfineInScreenSystem : public secs::TypedEntitySystem<PlayerComponent, TransformComponent, SpriteComponent>
{
public:

    void process(double delta, const secs::Entity& e, PlayerComponent& pc, TransformComponent& tc, SpriteComponent& sc) override;

};

