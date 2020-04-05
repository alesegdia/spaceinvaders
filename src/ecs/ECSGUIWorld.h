#pragma once

#include <secs/secs.h>
#include <aether/aether.h>

#include <memory>

#include "Components.h"


class ECSGUIWorld : public secs::Engine
{
public:
	ECSGUIWorld();

	secs::Entity MakeText(const std::string& text, float x, float y);
	secs::Entity MakeBigText(const std::string& text, float x, float y);

private:
	secs::Entity MakeText(aether::graphics::Font& font, const std::string& text, float x, float y);

	aether::graphics::Font m_normalFont;
	aether::graphics::Font m_bigFont;

};