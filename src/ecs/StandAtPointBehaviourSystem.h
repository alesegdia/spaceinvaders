#pragma once

#include <secs/secs.h>
#include "Components.h"


class StandAtPointBehaviourSystem : public secs::TypedEntitySystem<StandAtPointEnemyBehaviour, TransformComponent>
{
public:
    void process(double delta, const secs::Entity& e, StandAtPointEnemyBehaviour& sap, TransformComponent& tc) override;
};

