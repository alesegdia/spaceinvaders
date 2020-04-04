#include "HealthSystem.h"


void HealthSystem::process( double delta, const secs::Entity &e, HealthComponent& hc )
{
    SECS_UNUSED(delta);
    if( hc.currentHealth <= 0 && !hasComponent<DieComponent>(e))
    {
        addComponent<DieComponent>(e);
    }
}

void HealthSystem::onAdded(const secs::Entity& e)
{
    auto& hc = component<HealthComponent>(e);
    hc.currentHealth = hc.maxHealth;
}


