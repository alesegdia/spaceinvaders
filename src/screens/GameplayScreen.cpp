#include "GameplayScreen.h"

#include "../ecs/Systems.h"

#include "../Game.h"

GameplayScreen::GameplayScreen(Game& g)
	: m_game(g)
{

}

void GameplayScreen::show()
{
	m_ecsGUI.pushSystem(std::make_shared<RenderTextSystem>());

	m_ecs.pushSystem(std::make_shared<AnimationSystem>());
	m_ecs.pushSystem(std::make_shared<StarFieldSystem>());
	m_ecs.pushSystem(std::make_shared<RenderTextureSystem>());
	m_ecs.pushSystem(std::make_shared<PlayerInputSystem>());
	m_ecs.pushSystem(std::make_shared<ShootingSystem>());
	m_ecs.pushSystem(std::make_shared<MovementSystem>());
	m_ecs.pushSystem(std::make_shared<ConfineInScreenSystem>());
	m_ecs.pushSystem(std::make_shared<HadronCollisionSystem>());
	m_ecs.pushSystem(std::make_shared<DestroyOnExitScreen>());
	m_ecs.pushSystem(std::make_shared<HealthSystem>());
	m_ecs.pushSystem(std::make_shared<DieSystem>());
	m_ecs.pushSystem(std::make_shared<AsteroidSystem>());
	m_playerSeekerSystem = std::make_shared<PlayerSeekerBehaviourSystem>();
	m_ecs.pushSystem(m_playerSeekerSystem);
	m_ecs.pushSystem(std::make_shared<SinusoidalEnemyBehaviourSystem>());
	m_ecs.pushSystem(std::make_shared<StandAtPointBehaviourSystem>());

	m_playerShip = m_ecs.MakePlayerShip(350, 600);
	m_playerSeekerSystem->setPlayerEntity(m_playerShip);

	m_ecsGUI.MakeText("Space Invaders: SAVE THE EARTH! ", 0, 0);
	m_scoreText = m_ecsGUI.MakeText("SCORE: 0", 0, 600);

	spawnAsteroids();
}

void GameplayScreen::hide()
{

}

void GameplayScreen::update(uint64_t delta)
{
	m_ecs.step(delta);
	m_ecsGUI.step(delta);

	m_nextSpawnEnemyShip += delta;
	if (m_nextSpawnEnemyShip >= m_spawnEnemyShipRate / std::min(m_staleShipsWave + 1, 5))
	{
		m_nextSpawnEnemyShip = 0;
		auto shooter = rand() % 2;
		auto sinusoidal = rand() % 2;
		auto seeker = !sinusoidal;
		m_ecs.MakeEnemyShip(rand() % 700, -100, 2 + rand() % 3, shooter, sinusoidal, seeker);
	}

	if (m_ecs.numShipsActive() == 0)
	{
		auto waveType = m_staleShipsWave % 6;
		int yLimit = 2;
		bool alternate = false;
		bool sine = false;
		switch (waveType)
		{
		case 0:
			yLimit = 1; alternate = true; sine = false;
			break;
		case 1:
			yLimit = 1; alternate = true; sine = true;
			break;

		case 2:
			yLimit = 1; alternate = false; sine = false;
			break;
		case 3:
			yLimit = 1; alternate = false; sine = true;
			break;

		case 4:
			yLimit = 2; alternate = true; sine = false;
			break;
		case 5:
			yLimit = 2; alternate = false; sine = true;
			break;
		}

		for (int i = 0; i < 7; i++)
		{
			for (int j = 0; j < yLimit; j++)
			{
				if (i % 2 == 0 || !alternate)
				{
					m_ecs.MakeStandAtPointEnemy(55 + i * 100, 50 + j * 100, rand() % 2 == 0, sine);
				}
			}
		}

		m_staleShipsWave++;
	}

	if (m_ecs.numAsteroidsActive() == 0)
	{
		spawnAsteroids();
	}

	m_ecsGUI.component<TextComponent>(m_scoreText).text =
		"SCORE: " + std::to_string(m_ecs.score()) + "    HISCORE: " + std::to_string(get_hiscore());
	if (m_ecs.gameOver())
	{
		set_hiscore(m_ecs.score());
		m_game.setScreen(std::make_shared<MenuScreen>(m_game));
	}
}

void GameplayScreen::render()
{
	aether::graphics::clear(0, 0, 0);
	m_ecs.render();
	aether::graphics::draw_filled_rectangle(0, 0, 800, 30, aether::graphics::Color(1.0f, 0.0f, 0.0f));
	aether::graphics::draw_filled_rectangle(0, 600, 800, 800, aether::graphics::Color(0.0f, 0.0f, 0.0f));
	m_ecsGUI.render();

	auto drawBar = [](int amount, const aether::graphics::Color& c, const aether::math::Vec2f& offset)
	{
		int spacing = 5;
		int widthBar = 10;
		int heightBar = 30;
		for (int i = 0; i < amount; i++)
		{
			int x1 = offset.x() + (spacing + widthBar) * i;
			int y1 = offset.y();
			int x2 = x1 + widthBar;
			int y2 = y1 + heightBar;
			aether::graphics::draw_filled_rectangle(x1, y1, x2, y2, c);
		}
	};

	auto& hc = m_ecs.component<HealthComponent>(m_playerShip);
	drawBar(hc.currentHealth * 5, aether::graphics::Color(0.0f, 1.0f, 0.0f), { 10,  650 });
	drawBar(hc.currentShield * 5, aether::graphics::Color(0.0f, 1.0f, 1.0f), { 10,  700 });
	
	auto& sc = m_ecs.component<ShootComponent>(m_playerShip);
	auto shootPower = 6 - sc.shootingRate / 0.1e6;
	drawBar(shootPower * 10, aether::graphics::Color(1.0f, 0.5f, 0.0f), { 10,  750 });
}

void GameplayScreen::spawnAsteroids()
{
	for (int i = 0; i < 4; i++)
	{
		m_ecs.MakeAsteroid(i * 200 - 150, 150);
	}
}
