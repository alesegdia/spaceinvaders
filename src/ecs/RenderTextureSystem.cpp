#include "RenderTextureSystem.h"


RenderTextureSystem::RenderTextureSystem()
{
	setStepConfiguration(false, true);
}

void RenderTextureSystem::render(const secs::Entity & e)
{
	auto& sprite = processor()->component<SpriteComponent>(e);
	auto& transform = processor()->component<TransformComponent>(e);
	if (sprite.texture.valid())
	{
		sprite.texture.drawRotatedScaled(transform.position.x(), transform.position.y(), transform.scale, transform.scale, transform.rotation);
	}
}


