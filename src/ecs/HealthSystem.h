#pragma once

#include <secs/secs.h>
#include "Components.h"


class HealthSystem : public secs::TypedEntitySystem<HealthComponent>
{
public:

    void process(double delta, const secs::Entity& e, HealthComponent& hc) override;
    void onAdded(const secs::Entity& e) override;

};

