#pragma once

#include <aether/aether.h>
#include <secs/secs.h>
#include <hadron/hadron.h>
#include <functional>

enum class Faction
{
	Enemy,
	Player
};

struct TransformComponent
{
	aether::math::Vec2f position;
	float scale = 1.0f;
};

struct SpriteComponent
{
	aether::graphics::TextureRegion texture;
};

struct TextComponent
{
	aether::graphics::Font font;
	std::string text;
	std::string prevText;
	aether::graphics::TextData textData;
	aether::graphics::Color color;
};

struct AnimationComponent
{
	std::shared_ptr<aether::graphics::Animation> animation;
	aether::graphics::AnimationData animationData;
};

struct HadronCollisionComponent
{
	hadron::Body* body = nullptr;
	aether::math::Vec2f offset = aether::math::Vec2f(0, 0);
};

struct HealthComponent
{
	int currentHealth;
	int maxHealth;
};

struct ShipComponent
{
	Faction faction;
};

struct BulletComponent
{
	Faction faction;
	int power;
};

struct AsteroidComponent
{

};

struct DieComponent
{

};

struct OnDeathActionComponent
{
	std::function<void(const secs::Entity& e)> action;
};
