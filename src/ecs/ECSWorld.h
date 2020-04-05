#pragma once

#include <secs/secs.h>
#include <aether/aether.h>

#include <memory>

#include "Components.h"


class ECSWorld : public secs::Engine
{
public:
	ECSWorld();

	secs::Entity MakePlayerShip(float x, float y);
	secs::Entity MakeEnemyShip(float x, float y, float ySpeed = 2.0f, bool shooter = true, bool sinusoidal = false, bool seeker = false);
	secs::Entity MakeStandAtPointEnemy(float x, float y, bool shooter = true, bool sinusoidal = false);

	secs::Entity MakePlayerBullet(float x, float y);
	secs::Entity MakeEnemyBullet(float x, float y);

	secs::Entity MakeBlueEffect(float x, float y);
	secs::Entity MakeGalaxyEffect(float x, float y, float scale = 1.0f);
	secs::Entity MakeRedEffect(float x, float y);

	secs::Entity MakeAsteroid(float x, float y);

	secs::Entity MakePowerup(float x, float y, PowerupComponent::Type type);
	secs::Entity MakePowerup(float x, float y);

	int numAsteroidsActive()
	{
		return m_numAsteroidsActive;
	}

	int numShipsActive()
	{
		return m_numShipsActive;
	}

	int score()
	{
		return m_score;
	}

	bool gameOver()
	{
		return m_gameOver;
	}

private:

	void AddCollision(const secs::Entity& e, float w, float h, aether::math::Vec2f offset = { 0, 0 });
	void AddShip(const secs::Entity& e, Faction faction, int maxHealth);
	void AddAnimation(const secs::Entity& e, std::shared_ptr<aether::graphics::Animation> anim);
	void AddTransform(const secs::Entity& e, float x, float y, float scale = 1.0f, float rotation = 0.0f);
	void AddBullet(secs::Entity e, Faction faction, int power);
	void AddShoot(secs::Entity e, float rate, std::function<void(secs::Entity)> cb, bool shootRequested = false);
	void AddWaveMovement(secs::Entity e, float amplitude, float offset, float period)
	{
		auto& s = addComponent<SinusoidalEnemyBehaviour>(e);
		s.amplitude = amplitude;
		s.offset = offset;
		s.period = period;
	}

	secs::Entity MakeAnimationEntity(std::shared_ptr<aether::graphics::Animation> anim, float x, float y, float scale, float rotation = 0.0f);

	std::shared_ptr<aether::graphics::Animation> m_enemyAnim;
	std::shared_ptr<aether::graphics::Animation> m_playerAnim;
	std::shared_ptr<aether::graphics::Animation> m_blueFX;
	std::shared_ptr<aether::graphics::Animation> m_galaxyFX;
	std::shared_ptr<aether::graphics::Animation> m_redFX;
	aether::graphics::TextureRegion m_playerBullet;
	aether::graphics::TextureRegion m_enemyBullet;
	aether::graphics::TextureRegion m_healthPowerup;
	aether::graphics::TextureRegion m_shieldPowerup;
	aether::graphics::TextureRegion m_powerPowerup;
	aether::graphics::TextureRegion m_asteroids[4];

	int m_numAsteroidsActive = 0;
	int m_numShipsActive = 0;
	int m_score = 0;
	bool m_gameOver = false;

};