#pragma once

#include <secs/secs.h>
#include "Components.h"


class SinusoidalEnemyBehaviourSystem : public secs::TypedEntitySystem<SinusoidalEnemyBehaviour, TransformComponent>
{
public:
    void process(double delta, const secs::Entity& e, SinusoidalEnemyBehaviour& seb, TransformComponent& tc) override;
};

