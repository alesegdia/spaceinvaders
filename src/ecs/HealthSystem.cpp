#include "HealthSystem.h"


void HealthSystem::process( double delta, const secs::Entity &e, HealthComponent& hc )
{
    SECS_UNUSED(delta);
    if (hc.currentShield < 0)
    {
        hc.currentHealth += hc.currentShield;
        hc.currentShield = 0;
    }
    if (hc.currentShield < hc.maxShield)
    {
        hc.currentShield = hc.currentShield + hc.shieldRecoverPerSecond * delta;
        if (hc.currentShield > hc.maxShield)
        {
            hc.currentHealth = hc.maxShield;
        }
    }
    if( hc.currentHealth <= 0 && !hasComponent<DieComponent>(e))
    {
        addComponent<DieComponent>(e);
    }
}

void HealthSystem::onAdded(const secs::Entity& e)
{
    auto& hc = component<HealthComponent>(e);
    hc.currentHealth = hc.maxHealth;
    hc.currentShield = hc.maxShield;
}


