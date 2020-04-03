#include "AnimationSystem.h"

void AnimationSystem::onAdded(const secs::Entity& e)
{
	auto& anim = component<AnimationComponent>(e);
	anim.animation->reset(anim.animationData);
}

void AnimationSystem::process(double delta, const secs::Entity& e, AnimationComponent& ac, SpriteComponent& sc)
{
	SECS_UNUSED(delta);
	SECS_UNUSED(e);
	ac.animationData.timer += delta;
	ac.animation->updateData(ac.animationData);
	sc.texture = ac.animationData.currentFrame->texture;
}

