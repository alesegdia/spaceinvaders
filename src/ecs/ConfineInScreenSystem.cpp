#include "ConfineInScreenSystem.h"


void ConfineInScreenSystem::process(double delta, const secs::Entity& e,
    PlayerComponent& pc, TransformComponent& tc, SpriteComponent& sc)
{
    tc.position.x(std::max(std::min(tc.position.x(), 800 - sc.texture.clip().w() * tc.scale), 0.0f));
    tc.position.y(std::max(std::min(tc.position.y(), 600 - sc.texture.clip().h() * tc.scale), 0.0f));
}

