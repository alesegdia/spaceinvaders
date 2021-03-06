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
	float rotation = 0.0f;
};

struct SpriteComponent
{
	aether::graphics::TextureRegion texture;
	bool drawScaledCentered = false;
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
	bool destroyOnAnimationFinished = true;
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
	float currentShield;
	float maxShield = 0;
	float shieldRecoverPerSecond = 0.0000005f;
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

struct DieComponent
{

};

struct OnDeathActionComponent
{
	std::function<void(const secs::Entity& e)> action;
};

struct MovementComponent
{
	aether::math::Vec2f axis = { 0.0f, 0.0f };
	aether::math::Vec2f speed = { 1.0f, 1.0f };
};

struct TriggerComponent
{

};

struct ShootComponent
{
	std::function<void(secs::Entity)> shootCallback;
	bool shootRequested;
	float nextShootAvailable;
	float shootingRate;
};

struct PlayerComponent
{

};

struct AsteroidComponent
{
	float startScale = 0.0f;
	float endScale = 0.25f;
	uint64_t scalingTime = 500000;
	float rotationSpeed = 0.0001f;
};

struct PlayerSeekerEnemyBehaviour
{

};

struct SinusoidalEnemyBehaviour
{
	float amplitude;
	float period;
	float time = 0.0f;
	float offset;
};

struct StandAtPointEnemyBehaviour
{
	aether::math::Vec2f fromPosition;
	aether::math::Vec2f pointToStand;
	uint64_t timeTraveling = 1000000;
	uint64_t timer ;
};

struct PowerupComponent
{
	enum class Type
	{
		Health,
		Shield,
		Power
	};

	Type type;
};