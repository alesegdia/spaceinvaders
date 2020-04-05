#include <memory>

#include "ECSGUIWorld.h"
#include "Components.h"
#include "Systems.h"


ECSGUIWorld::ECSGUIWorld()
{
	m_normalFont.load("assets/default.ttf", 32);
	m_bigFont.load("assets/default.ttf", 80);
}

secs::Entity ECSGUIWorld::MakeText(const std::string& text, float x, float y)
{
	return MakeText(m_normalFont, text, x, y);
}

secs::Entity ECSGUIWorld::MakeBigText(const std::string& text, float x, float y)
{
	return MakeText(m_bigFont, text, x, y);
}

secs::Entity ECSGUIWorld::MakeText(aether::graphics::Font& font, const std::string& text, float x, float y)
{
	const auto& e = processor().addEntity();
	auto& tc = addComponent<TextComponent>(e);
	tc.color = aether::graphics::Color(1.0f, 1.0f, 1.0f);
	tc.text = text;
	tc.font = font;
	addComponent<TransformComponent>(e).position = { x, y };
	return e;
}