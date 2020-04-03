#pragma once

#include <secs/secs.h>

#include "Components.h"


class DieSystem : public secs::TypedEntitySystem<DieComponent>
{
public:
    void process(double delta, const secs::Entity& e, DieComponent& dc);

};
