#include <memory>

#include "ECSWorld.h"
#include "Components.h"
#include "Systems.h"

namespace
{

	using FrameList = std::vector<aether::graphics::TextureRegion>;
	FrameList GetFrames(std::string base, int from, int to, bool reverse = false)
	{
		std::vector<aether::graphics::TextureRegion> frames;
		for (int i = from; i <= to; i++)
		{
			auto path = base + std::to_string(reverse ? to - i + from : i) + ".png";
			aether::graphics::Texture t;
			t.load(path.c_str());
			frames.push_back({ t });
		}
		return frames;
	}

}

ECSWorld::ECSWorld()
{
	auto shipAnimTime = 0.05e6;
	auto fxAnimTime = 0.05e6;

	m_enemyAnim = std::make_shared<aether::graphics::Animation>(GetFrames("assets/Enemy/Enemy_animation/", 1, 8), shipAnimTime);
	m_playerAnim = std::make_shared<aether::graphics::Animation>(GetFrames("assets/Player/Animation/", 1, 8), shipAnimTime);

	m_blueFX = std::make_shared<aether::graphics::Animation>(GetFrames("assets/Effects/Blue/1_", 0, 16), fxAnimTime);
	m_blueFX->setWrapMode(aether::graphics::Animation::WrapMode::Once);

	m_redFX = std::make_shared<aether::graphics::Animation>(GetFrames("assets/Effects/Galaxy/galaxy_", 0, 16), fxAnimTime);
	m_redFX->setWrapMode(aether::graphics::Animation::WrapMode::Once);

	m_galaxyFX = std::make_shared<aether::graphics::Animation>(GetFrames("assets/Effects/Red/1_", 0, 16), fxAnimTime);
	m_galaxyFX->setWrapMode(aether::graphics::Animation::WrapMode::Once);

	m_playerBullet = aether::graphics::TextureRegion::Create("assets/Player/bullet.png");
	m_enemyBullet = aether::graphics::TextureRegion::Create("assets/Enemy/bullet_enemy.png");

	m_normalFont.load("assets/default.ttf", 32);
}

secs::Entity ECSWorld::MakeEnemyShip(float x, float y)
{
	const auto& e = MakeAnimationEntity(m_enemyAnim, x, y, 0.2f);
	AddShip(e, Faction::Enemy, 10);
	AddCollision(e, 50, 50, { 26, 20 });
	component<TransformComponent>(e).rotation = 180.0f;
	AddShoot(e, 2.0e6, [this](secs::Entity e) {
		auto& tc = component<TransformComponent>(e);
		MakeEnemyBullet(32 + tc.position.x(), 70 + tc.position.y());
	}, true);
	return e;
}

secs::Entity ECSWorld::MakePlayerShip(float x, float y)
{
	const auto& e = MakeAnimationEntity(m_playerAnim, x, y, 0.2f);
	AddShip(e, Faction::Player, 10);
	AddCollision(e, 80, 25, {10, 40});
	component<MovementComponent>(e).speed = { 6.0f, 3.0f };
	addComponent<PlayerComponent>(e);
	AddShoot(e, 0.05e6, [this](secs::Entity e) {
		auto& tc = component<TransformComponent>(e);
		MakePlayerBullet(tc.position.x() + 33, tc.position.y());
	});
	return e;
}

secs::Entity ECSWorld::MakeBlueEffect(float x, float y)
{
	return MakeAnimationEntity(m_blueFX, x, y, 0.5f, rand() % 360);
}

secs::Entity ECSWorld::MakeGalaxyEffect(float x, float y)
{
	return MakeAnimationEntity(m_galaxyFX, x, y, 0.5f, rand() % 360);
}

secs::Entity ECSWorld::MakeRedEffect(float x, float y)
{
	return MakeAnimationEntity(m_redFX, x, y, 0.5f, rand() % 360);
}

secs::Entity ECSWorld::MakeText(const std::string& text, float x, float y)
{
	const auto& e = processor().addEntity();
	auto& tc = addComponent<TextComponent>(e);
	tc.color = aether::graphics::Color(1.0f, 1.0f, 1.0f);
	tc.text = text;
	tc.font = m_normalFont;
	AddTransform(e, x, y);
	return e;
}

void ECSWorld::AddCollision(const secs::Entity& e, float w, float h, aether::math::Vec2f offset)
{
	//assert(hasComponent<TransformComponent>(e));
	auto& tc = component<TransformComponent>(e);
	auto& hcc = addComponent<HadronCollisionComponent>(e);
	hcc.body = new hadron::Body(tc.position.x(), tc.position.y(), w, h);
	hcc.offset = offset;
}

void ECSWorld::AddShip(const secs::Entity& e, Faction faction, int maxHealth)
{
	addComponent<ShipComponent>(e).faction = faction;
	addComponent<HealthComponent>(e).maxHealth = maxHealth;
	addComponent<MovementComponent>(e);
}

void ECSWorld::AddAnimation(const secs::Entity& e, std::shared_ptr<aether::graphics::Animation> anim)
{
	auto& ac = addComponent<AnimationComponent>(e);
	ac.animation = anim;
}

void ECSWorld::AddTransform(const secs::Entity& e, float x, float y, float scale, float rotation)
{
	auto& tc = addComponent<TransformComponent>(e);
	tc.position = { x, y };
	tc.scale = scale;
	tc.rotation = rotation;
	//processor().forceApplyChanges();
}

secs::Entity ECSWorld::MakeAnimationEntity(std::shared_ptr<aether::graphics::Animation> anim, float x, float y, float scale, float rotation)
{
	const auto& e = processor().addEntity();
	addComponent<SpriteComponent>(e);
	AddAnimation(e, anim);
	AddTransform(e, x, y, scale, rotation);
	return e;
}

secs::Entity ECSWorld::MakePlayerBullet(float x, float y)
{
	auto e = processor().addEntity();
	addComponent<SpriteComponent>(e).texture = m_playerBullet;
	AddTransform(e, x, y, 0.25f);
	AddCollision(e, 6, 10, { 13.0f, 10.0f });
	AddBullet(e, Faction::Player, 1);
	addComponent<MovementComponent>(e).axis = { 0.0f, -5.0f };
	addComponent<OnDeathActionComponent>(e).action = [this] (secs::Entity e) {
		auto& tc = component<TransformComponent>(e);
		MakeBlueEffect(tc.position.x() - 50, tc.position.y() - 50);
	};
	return e;
}

secs::Entity ECSWorld::MakeEnemyBullet(float x, float y)
{
	auto e = processor().addEntity();
	addComponent<SpriteComponent>(e).texture = m_enemyBullet;
	AddTransform(e, x, y, 0.25f, 180.0f);
	AddCollision(e, 6, 10, { 13.0f, 10.0f });
	AddBullet(e, Faction::Enemy, 1);
	addComponent<MovementComponent>(e).axis = { 0.0f, 5.0f };
	addComponent<OnDeathActionComponent>(e).action = [this](secs::Entity e) {
		auto& tc = component<TransformComponent>(e);
		MakeRedEffect(tc.position.x() - 50, tc.position.y() - 50);
	};
	return e;
}

void ECSWorld::AddBullet(secs::Entity e, Faction faction, int power)
{
	auto& bullet = addComponent<BulletComponent>(e);
	bullet.faction = faction;
	bullet.power = power;
	addComponent<HealthComponent>(e).maxHealth = 1;
}

void ECSWorld::AddShoot(secs::Entity e, float rate, std::function<void(secs::Entity)> cb, bool shootRequested)
{
	auto& sc = addComponent<ShootComponent>(e);
	sc.shootingRate = rate;
	sc.nextShootAvailable = 0.0f;
	sc.shootCallback = cb;
	sc.shootRequested = shootRequested;
}
