#pragma once

#include <secs/secs.h>
#include <hadron/hadron.h>

#include "Components.h"


class HadronCollisionSystem
        : public secs::TypedEntitySystem<HadronCollisionComponent, TransformComponent>,
          public hadron::ICollisionListener
{
public:

    HadronCollisionSystem()
    {
        setStepConfiguration(true, true);
        m_physicsWorld.registerListener(this);
    }

    ~HadronCollisionSystem()
    {
        m_physicsWorld.unregisterListener(this);
    }

    void postUpdate(double delta) override
    {
        SECS_UNUSED(delta);
        m_physicsWorld.step();
    }

    void process(double delta, const secs::Entity &e, HadronCollisionComponent &hcc, TransformComponent& tc) override
    {
        SECS_UNUSED(delta);
        SECS_UNUSED(e);
        const auto& p = tc.position;
        hcc.body->setPosition(hadron::Vec2(p.x() + hcc.offset.x(), p.y() + hcc.offset.y()));
    }

    void render(const secs::Entity &e) override
    {
        if( enabled )
        {
            auto& hcc = component<HadronCollisionComponent>(e);
            const auto& aabb = hcc.body->aabb();
            aether::graphics::draw_filled_rectangle(
                aether::math::Rectf{ aabb.x, aabb.y, aabb.width, aabb.height },
                aether::graphics::Color(1.0f, 0.0f, 1.0f, 0.5f));
        }
    }

    void onAdded( const secs::Entity& e )
    {
        auto& hcc = component<HadronCollisionComponent>(e);
        assert(hcc.body != nullptr);
        m_physicsWorld.registerBody(hcc.body);
        secs::Entity* eptr = new secs::Entity(e);
        hcc.body->userData(static_cast<void*>(eptr));
    }

    void onRemoved( const secs::Entity& e )
    {
        auto& hcc = component<HadronCollisionComponent>(e);
        m_physicsWorld.unregisterBody(hcc.body);
        auto eptr = static_cast<secs::Entity*>(hcc.body->userData());
        delete eptr;
        delete hcc.body;
        hcc.body = nullptr;
        printf("cleanup\n"); fflush(0);
    }

    void onCollisionEnter(hadron::Body &b1, hadron::Body &b2, hadron::CollisionResult cr) override
    {
        auto e1 = getEntityFromBody(b1);
        auto e2 = getEntityFromBody(b2);
        handleCollision( e1, e2 );
    }

    void onCollisionExit(hadron::Body &b1, hadron::Body &b2) override
    {
        SECS_UNUSED(b1);
        SECS_UNUSED(b2);
        printf("meh\n"); fflush(0);
    }

    void handleCollision( const secs::Entity& e1, const secs::Entity& e2 )
    {
        secs::Entity out1, out2;
        if (entitiesHaveComponents<ShipComponent, BulletComponent>(e1, e2, &out1, &out2))
        {
            auto& ship = component<ShipComponent>(out1);
            auto& bullet = component<BulletComponent>(out2);
            if (ship.faction != bullet.faction && !hasComponent<DieComponent>(out2))
            {
                component<HealthComponent>(out1).currentHealth -= bullet.power;
                component<HealthComponent>(out2).currentHealth = 0;
            }
        }

    }

private:

    template <typename C1, typename C2>
    bool entitiesHaveComponents(secs::Entity e1, secs::Entity e2, secs::Entity* ref1, secs::Entity* ref2)
    {
        bool check = false;
        if( hasComponent<C1>(e1) && hasComponent<C2>(e2) )
        {
            *ref1 = e1; *ref2 = e2;
            check = true;
        }
        else if( hasComponent<C1>(e2) && hasComponent<C2>(e1) )
        {
            *ref1 = e2; *ref2 = e1;
            check = true;
        }
        return check;
    }

    secs::Entity getEntityFromBody( hadron::Body& b )
    {
        return *(static_cast<secs::Entity*>(b.userData()));
    }

    hadron::collision::World m_physicsWorld;

    bool enabled = false;

};
