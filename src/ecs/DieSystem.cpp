#include "DieSystem.h"


void DieSystem::process(double delta, const secs::Entity &e, DieComponent &dc)
{
    SECS_UNUSED(delta);
    SECS_UNUSED(dc);
    if( hasComponent<OnDeathActionComponent>(e) )
    {
        auto& odac = component<OnDeathActionComponent>(e);
        odac.action(e);
    }
    processor()->removeEntity(e);
}

