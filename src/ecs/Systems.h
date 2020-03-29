#include <secs/secs.h>
#include <rztl/rztl.h>

#include "Components.h"

class ECSWorld;

class RenderTextureSystem : public secs::TypedEntitySystem<TransformComponent, SpriteComponent>
{
public:
	virtual void process(double delta, const secs::Entity & e,
		TransformComponent& transform,
		SpriteComponent& sprite) override;
};

class RenderTextSystem : public secs::TypedEntitySystem<TransformComponent, TextComponent>
{
public:
	virtual void process(double delta, const secs::Entity & e,
		TransformComponent& transform,
		TextComponent& text) override;
};
