#include <memory>

#include "ECSWorld.h"
#include "Components.h"
#include "Systems.h"

namespace
{

	using FrameList = std::vector<aether::graphics::TextureRegion>;
	FrameList GetFrames(std::string base, int from, int to)
	{
		std::vector<aether::graphics::TextureRegion> frames;
		for (int i = from; i <= to; i++)
		{
			auto path = base + std::to_string(i) + ".png";
			aether::graphics::Texture t;
			t.load(path.c_str());
			frames.push_back({ t });
		}
		return frames;
	}

}

ECSWorld::ECSWorld()
{
	m_playerAnim = std::make_shared<aether::graphics::Animation>(GetFrames("assets/Enemy/Enemy_animation/", 1, 8), 1000);
	m_enemyAnim = std::make_shared<aether::graphics::Animation>(GetFrames("assets/Player/Animation/", 1, 8), 1000);
	m_blueFX = std::make_shared<aether::graphics::Animation>(GetFrames("assets/Effects/Blue/1_", 0, 16), 2000);
	m_redFX = std::make_shared<aether::graphics::Animation>(GetFrames("assets/Effects/Galaxy/galaxy_", 0, 16), 2000);
	m_galaxyFX = std::make_shared<aether::graphics::Animation>(GetFrames("assets/Effects/Red/1_", 0, 16), 2000);
	m_normalFont.load("assets/default.ttf", 32);
}

secs::Entity ECSWorld::MakeEnemyShip(float x, float y)
{
	const auto& e = MakeAnimationEntity(m_enemyAnim, x, y, 0.2f);
	AddShip(e, Faction::Enemy, 10);
	AddCollision(e, 10, 10);
	return e;
}

secs::Entity ECSWorld::MakePlayerShip(float x, float y)
{
	const auto& e = MakeAnimationEntity(m_playerAnim, x, y, 0.2f);
	AddShip(e, Faction::Enemy, 10);
	AddCollision(e, 10, 10);
	return e;
}

secs::Entity ECSWorld::MakeBlueEffect(float x, float y)
{
	return MakeAnimationEntity(m_blueFX, x, y, 0.5f);
}

secs::Entity ECSWorld::MakeGalaxyEffect(float x, float y)
{
	return MakeAnimationEntity(m_galaxyFX, x, y, 0.5f);
}

secs::Entity ECSWorld::MakeRedEffect(float x, float y)
{
	return MakeAnimationEntity(m_redFX, x, y, 0.5f);
}

secs::Entity ECSWorld::MakeText(const std::string& text, float x, float y)
{
	const auto& e = processor().addEntity();
	auto& tc = processor().addComponent<TextComponent>(e);
	tc.color = aether::graphics::Color(1.0f, 1.0f, 1.0f);
	tc.text = text;
	tc.font = m_normalFont;
	AddTransform(e, x, y);
	return e;
}

void ECSWorld::AddCollision(const secs::Entity& e, float w, float h, aether::math::Vec2f offset)
{
	assert(hasComponent<TransformComponent>(e));
	auto& tc = component<TransformComponent>(e);
	auto& hcc = addComponent<HadronCollisionComponent>(e);
	hcc.body = new hadron::Body(tc.position.x(), tc.position.y(), w, h);
	hcc.offset = offset;
}

void ECSWorld::AddShip(const secs::Entity& e, Faction faction, int maxHealth)
{
	processor().addComponent<ShipComponent>(e).faction = faction;
	processor().addComponent<HealthComponent>(e).maxHealth = maxHealth;
}

void ECSWorld::AddAnimation(const secs::Entity& e, std::shared_ptr<aether::graphics::Animation> anim)
{
	auto& ac = processor().addComponent<AnimationComponent>(e);
	ac.animation = anim;
}

void ECSWorld::AddTransform(const secs::Entity& e, float x, float y, float scale)
{
	auto& tc = processor().addComponent<TransformComponent>(e);
	tc.position = { x, y };
	tc.scale = scale;
	processor().forceApplyChanges();
}

secs::Entity ECSWorld::MakeAnimationEntity(std::shared_ptr<aether::graphics::Animation> anim, float x, float y, float scale)
{
	const auto& e = processor().addEntity();
	processor().addComponent<SpriteComponent>(e);
	AddAnimation(e, anim);
	AddTransform(e, x, y, scale);
	return e;
}
