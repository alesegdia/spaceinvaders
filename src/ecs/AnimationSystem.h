#pragma once

#include "Components.h"


class AnimationSystem : public secs::TypedEntitySystem<AnimationComponent, SpriteComponent>
{
public:
	void onAdded(const secs::Entity& e) override;
	void process(double delta, const secs::Entity & e, AnimationComponent& ac, SpriteComponent& sc) override;
};
