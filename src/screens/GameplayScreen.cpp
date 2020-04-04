#include "GameplayScreen.h"

#include "../ecs/Systems.h"

void GameplayScreen::show()
{
	m_font.load("assets/default.ttf", 64);
	m_textData = m_font.createTextTexture("Space Invaders", aether::graphics::Color(1.0f, 1.0f, 1.0f));

	m_ecsWorld.pushSystem(std::make_shared<RenderTextSystem>());
	m_ecsWorld.pushSystem(std::make_shared<AnimationSystem>());
	m_ecsWorld.pushSystem(std::make_shared<StarFieldSystem>());
	m_ecsWorld.pushSystem(std::make_shared<RenderTextureSystem>());
	m_ecsWorld.pushSystem(std::make_shared<PlayerInputSystem>());
	m_ecsWorld.pushSystem(std::make_shared<ShootingSystem>());
	m_ecsWorld.pushSystem(std::make_shared<MovementSystem>());
	m_ecsWorld.pushSystem(std::make_shared<ConfineInScreenSystem>());
	m_ecsWorld.pushSystem(std::make_shared<HadronCollisionSystem>());
	m_ecsWorld.pushSystem(std::make_shared<DestroyOnExitScreen>());
	m_ecsWorld.pushSystem(std::make_shared<HealthSystem>());
	m_ecsWorld.pushSystem(std::make_shared<DieSystem>());
	m_ecsWorld.pushSystem(std::make_shared<AsteroidSystem>());

	m_ecsWorld.MakePlayerShip(350, 600);

	m_ecsWorld.MakeText("Space Invaders", 0, 0);
	
	for (int i = 0; i < 4; i++)
	{
		m_ecsWorld.MakeAsteroid(i * 200 - 150, 100);
	}
}

void GameplayScreen::hide()
{

}

void GameplayScreen::update(uint64_t delta)
{
	m_ecsWorld.step(delta);
	m_nextSpawn += delta;
	if (m_nextSpawn >= m_spawnRate)
	{
		m_nextSpawn = 0;
		m_ecsWorld.MakeEnemyShip(rand() % 700, -100, 2 + rand() % 3);
	}
}

void GameplayScreen::render()
{
	aether::graphics::clear(0, 0, 0);
	m_ecsWorld.render();
	aether::graphics::draw_filled_rectangle(0, 600, 800, 800, aether::graphics::Color(0.1f, 0.1f, 0.1f));
}
