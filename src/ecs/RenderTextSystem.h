#pragma once

#include "Components.h"

class RenderTextSystem : public secs::TypedEntitySystem<TransformComponent, TextComponent>
{
public:

	RenderTextSystem();

	void process(double delta, const secs::Entity & e,
		TransformComponent& transform,
		TextComponent& text) override;

	void render(const secs::Entity& e) override;
};

