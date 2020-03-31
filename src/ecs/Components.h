#pragma once

#include <aether/aether.h>
#include <secs/secs.h>


struct TransformComponent
{
	float x, y;
};

struct SpriteComponent
{
	aether::graphics::TextureRegion texture;
};

struct TextComponent
{
	std::string text;
	aether::graphics::Color color;
};

