#pragma once

#include <aether/aether.h>

#include "../ecs/ECSWorld.h"
#include "../ecs/ECSGUIWorld.h"
#include "../ecs/Systems.h"

class Game;

class GameplayScreen : public aether::core::IScreen
{
public:

	GameplayScreen(Game& g);

	virtual void show() override;

	virtual void hide() override;
	
	virtual void update(uint64_t delta) override;

	virtual void render() override;

private:

	void spawnAsteroids();

	ECSWorld m_ecs;
	ECSGUIWorld m_ecsGUI;

	secs::Entity m_scoreText;

	uint64_t m_spawnEnemyShipRate = 10e6;
	uint64_t m_nextSpawnEnemyShip = 0;

	uint64_t m_spawnAsteroidsRate = 10e6;
	uint64_t m_nextSpawnAsteroids = 0;

	bool m_standShipsActive = false;
	bool m_randomShipsActive = true;

	secs::Entity m_playerShip;

	int m_staleShipsWave = 0;

	std::shared_ptr<PlayerSeekerBehaviourSystem> m_playerSeekerSystem;

	Game& m_game;

};