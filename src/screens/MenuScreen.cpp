#include "MenuScreen.h"

#include "../ecs/Systems.h"

#include "../Game.h"


MenuScreen::MenuScreen(Game& g)
	: m_game(g)
{

}

void MenuScreen::show()
{
	m_ecsGUI.pushSystem(std::make_shared<RenderTextSystem>());
	m_ecsGUI.MakeBigText("Space", 240, 100);
	m_ecsGUI.MakeBigText("Invaders", 190, 170);

	m_ecsGUI.MakeText("press space to start", 200, 400);

	m_ecsGUI.MakeText("hiscore: " + std::to_string(get_hiscore()), 270, 700);
}

void MenuScreen::hide()
{

}

void MenuScreen::update(uint64_t delta)
{
	m_ecsGUI.step(delta);
	if (aether::core::is_key_down(aether::core::KeyCode::Space))
	{
		m_game.setScreen(std::make_shared<GameplayScreen>(m_game));
	}
}

void MenuScreen::render()
{
	aether::graphics::clear(0, 0, 0);
	m_ecsGUI.render();
}
