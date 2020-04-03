#pragma once

#include "Components.h"

class RenderTextureSystem : public secs::EntitySystem
{
public:
	RenderTextureSystem();

	void render(const secs::Entity& e) override;
};

