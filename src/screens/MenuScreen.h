#pragma once

#include <aether/aether.h>

#include "../ecs/ECSWorld.h"
#include "../ecs/ECSGUIWorld.h"
#include "../ecs/Systems.h"

class Game;

class MenuScreen : public aether::core::IScreen
{
public:

	MenuScreen(Game& g);

	virtual void show() override;

	virtual void hide() override;
	
	virtual void update(uint64_t delta) override;

	virtual void render() override;


private:
	ECSGUIWorld m_ecsGUI;
	Game& m_game;

};