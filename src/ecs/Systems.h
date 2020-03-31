#include <secs/secs.h>
#include <rztl/rztl.h>

#include <aether/aether.h>

#include "Components.h"

class ECSWorld;

class RenderTextureSystem : public secs::TypedEntitySystem<TransformComponent, SpriteComponent>
{
public:
	virtual void process(double delta, const secs::Entity & e,
		TransformComponent& transform,
		SpriteComponent& sprite) override;
};

class RenderTextSystem : public secs::TypedEntitySystem<TransformComponent, TextComponent>
{
public:
	virtual void process(double delta, const secs::Entity & e,
		TransformComponent& transform,
		TextComponent& text) override;
};

class StarFieldSystem : public secs::System
{
public:
	using Star = aether::math::Rectf;
	using StarsLayer = std::vector<Star>;
	StarFieldSystem()
	{
		setStepConfiguration(true, true);
		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < 10; j++)
			{
				m_stars[i].push_back(Star(rand() % 800, rand() % 600, i + 1, i + 1));
			}
		}
	}

	void renderStep() override
	{
		for (const auto& layer : m_stars)
		{
			for (const auto& star : layer)
			{
				aether::graphics::draw_filled_rectangle(star, { 1.0f, 1.0f, 1.0f });
			}
		}
	}

	void step(double delta) override
	{
		for (int i = 0; i < 3; i++)
		{
			for (auto& star : m_stars[i])
			{
				star.y(star.y() + i + 1);
				if (star.y() > 600)
				{
					star.y(0);
					star.x(rand() % 800);
				}
			}
		}
	}


private:
	StarsLayer m_stars[3];
};