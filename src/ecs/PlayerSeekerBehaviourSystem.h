#pragma once

#include <secs/secs.h>
#include "Components.h"


class PlayerSeekerBehaviourSystem : public secs::TypedEntitySystem<PlayerSeekerEnemyBehaviour, TransformComponent>
{
public:
    void process(double delta, const secs::Entity& e, PlayerSeekerEnemyBehaviour& pseb, TransformComponent& tc) override;

    void setPlayerEntity(secs::Entity playerEntity)
    {
        m_playerEntity = playerEntity;
    }

private:
    secs::Entity m_playerEntity;

};

