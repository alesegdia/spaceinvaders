#include "RenderTextSystem.h"


RenderTextSystem::RenderTextSystem()
{
	setStepConfiguration(true, true);
}

void RenderTextSystem::process(double delta, const secs::Entity & e, TransformComponent & transform, TextComponent & text)
{
	if (text.text != text.prevText)
	{
		text.prevText = text.text;
		text.textData = text.font.createTextTexture(text.text.c_str(), text.color);
	}
}

void RenderTextSystem::render(const secs::Entity& e)
{
	auto& text = component<TextComponent>(e);
	const auto& transform = component<TransformComponent>(e);
	text.textData.draw(transform.position.x(), transform.position.y());
}

