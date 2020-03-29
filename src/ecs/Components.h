#pragma once

#include <aether/aether.h>
#include <secs/secs.h>

struct TransformComponent
{
	float x, y;
};


struct SpriteComponent
{
	aether::graphics::Texture texture;
};

struct TextComponent
{
	std::string text;
};

struct GemComponent
{
	int tier = -1;
};