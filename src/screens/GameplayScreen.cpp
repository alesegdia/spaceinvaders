#include "GameplayScreen.h"


void GameplayScreen::show()
{
	m_font.load("assets/default.ttf", 64);
	auto enemyFrames = GetFrames("assets/Enemy/Enemy_animation/", 1, 8);
	m_anim.addFrames(enemyFrames);
	m_anim.reset(m_animData);
	m_textData = m_font.createTextTexture("Space Invaders", aether::graphics::Color(1.0f, 1.0f, 1.0f));
}

void GameplayScreen::hide()
{

}

void GameplayScreen::update(uint64_t delta)
{
	m_animData.timer += delta;
	m_anim.updateData(m_animData);
	m_stars.step(delta);
}

void GameplayScreen::render()
{
	aether::graphics::clear(0, 0, 0);
	m_stars.renderStep();
	m_animData.currentFrame->texture.draw(0, 0, 0.5f, 0.5f);
	m_textData.draw(10, 10);
}
