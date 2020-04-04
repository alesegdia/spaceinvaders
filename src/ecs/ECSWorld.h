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
	secs::Entity MakeEnemyShip(float x, float y);

	secs::Entity MakePlayerBullet(float x, float y);
	secs::Entity MakeEnemyBullet(float x, float y);

	secs::Entity MakeBlueEffect(float x, float y);
	secs::Entity MakeGalaxyEffect(float x, float y);
	secs::Entity MakeRedEffect(float x, float y);

	secs::Entity MakeText(const std::string& text, float x, float y);

private:

	void AddCollision(const secs::Entity& e, float w, float h, aether::math::Vec2f offset = { 0, 0 });
	void AddShip(const secs::Entity& e, Faction faction, int maxHealth);
	void AddAnimation(const secs::Entity& e, std::shared_ptr<aether::graphics::Animation> anim);
	void AddTransform(const secs::Entity& e, float x, float y, float scale = 1.0f, float rotation = 1.0f);
	void AddBullet(secs::Entity e, Faction faction, int power);
	void AddShoot(secs::Entity e, float rate, std::function<void(secs::Entity)> cb);

	secs::Entity MakeAnimationEntity(std::shared_ptr<aether::graphics::Animation> anim, float x, float y, float scale);

	aether::graphics::Font m_normalFont;
	std::shared_ptr<aether::graphics::Animation> m_enemyAnim;
	std::shared_ptr<aether::graphics::Animation> m_playerAnim;
	std::shared_ptr<aether::graphics::Animation> m_blueFX;
	std::shared_ptr<aether::graphics::Animation> m_galaxyFX;
	std::shared_ptr<aether::graphics::Animation> m_redFX;
	aether::graphics::TextureRegion m_playerBullet;
	aether::graphics::TextureRegion m_enemyBullet;

};