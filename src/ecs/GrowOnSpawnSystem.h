#pragma once

#include <secs/secs.h>
#include "Components.h"


class AsteroidSystem : public secs::TypedEntitySystem<AsteroidComponent, TransformComponent>
{
public:
    void onAdded(const secs::Entity& e) override
    {
        component<TransformComponent>(e).scale = component<AsteroidComponent>(e).startScale;
    }

    void process(double delta, const secs::Entity& e, AsteroidComponent& gc, TransformComponent& tc) override;

};

