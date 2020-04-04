#pragma once

#include <secs/secs.h>
#include "Components.h"


class DestroyOnExitScreen : public secs::TypedEntitySystem<TransformComponent>
{
public:

    void process(double delta, const secs::Entity& e, TransformComponent& tc) override;

};

