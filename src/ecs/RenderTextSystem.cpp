#include "RenderTextSystem.h"


RenderTextSystem::RenderTextSystem()
{
	setStepConfiguration(true, true);
}

void RenderTextSystem::process(double delta, const secs::Entity & e, TransformComponent & transform, TextComponent & text)
{
#ifndef AETHER_USE_ALLEGRO
	if (text.text != text.prevText)
	{
		text.prevText = text.text;
		text.textData.texture.destroy();
		text.textData = text.font.createTextTexture(text.text.c_str(), text.color);
	}
#endif
}

void RenderTextSystem::render(const secs::Entity& e)
{
#ifndef AETHER_USE_ALLEGRO
	auto& text = component<TextComponent>(e);
	const auto& transform = component<TransformComponent>(e);
	text.textData.draw(transform.position.x(), transform.position.y());
#endif
}

