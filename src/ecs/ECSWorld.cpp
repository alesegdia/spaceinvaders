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
	auto fxAnimTime = 0.025e6;

	m_enemyAnim = std::make_shared<aether::graphics::Animation>(GetFrames("assets/Enemy/Enemy_animation/", 1, 8), shipAnimTime);
	m_playerAnim = std::make_shared<aether::graphics::Animation>(GetFrames("assets/Player/Animation/", 1, 8), shipAnimTime);

	m_blueFX = std::make_shared<aether::graphics::Animation>(GetFrames("assets/Effects/Blue/1_", 0, 16), fxAnimTime);
	m_blueFX->setWrapMode(aether::graphics::Animation::WrapMode::Once);

	m_redFX = std::make_shared<aether::graphics::Animation>(GetFrames("assets/Effects/Red/1_", 0, 16), fxAnimTime);
	m_redFX->setWrapMode(aether::graphics::Animation::WrapMode::Once);

	m_galaxyFX = std::make_shared<aether::graphics::Animation>(GetFrames("assets/Effects/Galaxy/galaxy_", 0, 16), fxAnimTime);
	m_galaxyFX->setWrapMode(aether::graphics::Animation::WrapMode::Once);

	m_playerBullet = aether::graphics::TextureRegion::Create("assets/Player/bullet.png");
	m_enemyBullet = aether::graphics::TextureRegion::Create("assets/Enemy/bullet_enemy.png");

	for (int i = 0; i < 4; i++)
	{
		m_asteroids[i] = aether::graphics::TextureRegion::Create("assets/Asteroids/asteroid" + std::to_string(i) + ".png");
	}

	m_healthPowerup = aether::graphics::TextureRegion::Create("assets/Powerups/health0.png");
	m_shieldPowerup = aether::graphics::TextureRegion::Create("assets/Powerups/shield0.png");
	m_powerPowerup = aether::graphics::TextureRegion::Create("assets/Powerups/power0.png");
}


secs::Entity ECSWorld::MakeEnemyShip(float x, float y, float ySpeed, bool shooter, bool sinusoidal, bool seeker)
{
	const auto& e = MakeAnimationEntity(m_enemyAnim, x, y, 0.2f);
	AddShip(e, Faction::Enemy, 3);
	AddCollision(e, 50, 50, { 26, 20 });
	component<TransformComponent>(e).rotation = 180.0f;
	if (shooter)
	{
		AddShoot(e, 2.0e6 + (rand() % 100) * 10000, [this](secs::Entity e) {
			auto& tc = component<TransformComponent>(e);
			MakeEnemyBullet(32 + tc.position.x(), 70 + tc.position.y());
		}, true);
	}
	auto& bullet = addComponent<BulletComponent>(e);
	bullet.faction = Faction::Enemy;
	bullet.power = 2;
	addComponent<OnDeathActionComponent>(e).action = [this](secs::Entity e) {
		auto& tc = component<TransformComponent>(e);
		MakeGalaxyEffect(tc.position.x() - 70, tc.position.y() - 70);
		m_score += 50;
		if (rand() % 2 == 0) MakePowerup(tc.position.x() + 10, tc.position.y() + 10);
	};
	addComponent<MovementComponent>(e).axis = { 0.0f, ySpeed };
	if (sinusoidal)
	{
		AddWaveMovement(e, 100, x, 5);
	}
	if (seeker)
	{
		addComponent<PlayerSeekerEnemyBehaviour>(e);
	}
	return e;
}

secs::Entity ECSWorld::MakeStandAtPointEnemy(float x, float y, bool shooter, bool sinusoidal)
{
	m_numShipsActive++;
	auto ox = float(rand() % 800);
	auto oy = -100.0f;
	auto e = MakeEnemyShip(ox, oy, 0, shooter, sinusoidal);
	auto& sap = addComponent<StandAtPointEnemyBehaviour>(e);
	sap.fromPosition = { ox, oy };
	sap.pointToStand = { x, y };
	sap.timer = 0;
	sap.timeTraveling = 1000000;
	auto& aic = component<MovementComponent>(e);
	aic.axis = { 0, 0 };
	aic.speed = { 0, 0 };
	component<OnDeathActionComponent>(e).action = [this](secs::Entity e) {
		auto& tc = component<TransformComponent>(e);
		MakeGalaxyEffect(tc.position.x() - 70, tc.position.y() - 70);
		m_score += 50;
		m_numShipsActive--;
		if (rand() % 2 == 0) MakePowerup(tc.position.x() + 10, tc.position.y() + 10);
	};
	if (sinusoidal)
	{
		component<SinusoidalEnemyBehaviour>(e).offset = x;
		component<SinusoidalEnemyBehaviour>(e).amplitude = 50;
	}
	return e;
}

secs::Entity ECSWorld::MakePlayerShip(float x, float y)
{
	const auto& e = MakeAnimationEntity(m_playerAnim, x, y, 0.2f);
	AddShip(e, Faction::Player, 10);
	addComponent<MovementComponent>(e).speed = { 5.0f, 3.0f };
	AddCollision(e, 80, 25, {10, 40});
	addComponent<PlayerComponent>(e);
	AddShoot(e, 0.5e6, [this](secs::Entity e) {
		auto& tc = component<TransformComponent>(e);
		MakePlayerBullet(tc.position.x() + 33, tc.position.y());
	});
	component<HealthComponent>(e).maxShield = 10;
	addComponent<OnDeathActionComponent>(e).action = [this](const secs::Entity& e)
	{
		m_gameOver = true;
	};
	return e;
}

secs::Entity ECSWorld::MakeBlueEffect(float x, float y)
{
	return MakeAnimationEntity(m_blueFX, x, y, 0.5f, rand() % 360);
}

secs::Entity ECSWorld::MakeGalaxyEffect(float x, float y, float scale)
{
	return MakeAnimationEntity(m_galaxyFX, x, y, scale, rand() % 360);
}

secs::Entity ECSWorld::MakeRedEffect(float x, float y)
{
	return MakeAnimationEntity(m_redFX, x, y, 0.5f, rand() % 360);
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


secs::Entity ECSWorld::MakeAsteroid(float x, float y)
{
	m_numAsteroidsActive++;
	auto e = MakeAnimationEntity(m_galaxyFX, x, y, 2.0f, rand() % 360);
	addComponent<OnDeathActionComponent>(e).action = [this] (const secs::Entity& e) {
		auto asteroid = processor().addEntity();
		auto& tc = component<TransformComponent>(e);
		auto& sc = addComponent<SpriteComponent>(asteroid);
		sc.texture = m_asteroids[rand() % 4];
		sc.drawScaledCentered = true;
		AddTransform(asteroid, tc.position.x() + 250, tc.position.y() + 250, 0.2f, 0.0f);
		auto& ac = addComponent<AsteroidComponent>(asteroid);
		ac.endScale = 0.25f + (rand() % 10) / 100.0f;
		ac.rotationSpeed = (5 - rand() % 10) / 50000.0f;
		AddCollision(asteroid, 90, 90, { -45, -45 });
		addComponent<ShipComponent>(asteroid).faction = Faction::Enemy;
		addComponent<BulletComponent>(asteroid).faction = Faction::Enemy;
		component<BulletComponent>(asteroid).power = 2;
		addComponent<HealthComponent>(asteroid).maxHealth = 10;
		addComponent<OnDeathActionComponent>(asteroid).action = [this](const secs::Entity& a) {
			m_numAsteroidsActive--;
			auto& tc = component<TransformComponent>(a);
			m_score += 200;
			MakePowerup(tc.position.x()-30, tc.position.y());
			for (int i = 0; i < 10; i++)
			{
				int drandom = 50;
				float dx, dy;
				dx = 55.0f - drandom + rand() % drandom * 2;
				dy = 50.0f - drandom + rand() % drandom * 2;
				MakeGalaxyEffect(
					tc.position.x() - dx,
					tc.position.y() - dy, 0.5f);
			}
		};
	};
	return e;
}

secs::Entity ECSWorld::MakePowerup(float x, float y, PowerupComponent::Type type)
{
	auto e = processor().addEntity();
	auto& sc = addComponent<SpriteComponent>(e);
	addComponent<PowerupComponent>(e).type = type;
	switch (type)
	{
	case PowerupComponent::Type::Health:
		sc.texture = m_healthPowerup; break;
	case PowerupComponent::Type::Power:
		sc.texture = m_powerPowerup; break;
	case PowerupComponent::Type::Shield:
		sc.texture = m_shieldPowerup; break;
	}
	AddTransform(e, x, y, 0.25f);
	addComponent<MovementComponent>(e).axis = { 0.0f, 0.1f };
	AddCollision(e, 40, 40, { 11, 14 });
	AddWaveMovement(e, 10, x, 10);
	return e;
}

secs::Entity ECSWorld::MakePowerup(float x, float y)
{
	auto rng = rand() % 3;
	switch (rng)
	{
	case 0: return MakePowerup(x, y, PowerupComponent::Type::Power);
	case 1: return MakePowerup(x, y, PowerupComponent::Type::Health);
	case 2: return MakePowerup(x, y, PowerupComponent::Type::Shield);
	}
	return secs::Entity();
}

