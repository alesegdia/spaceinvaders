#include "StarsFieldSystem.h"

StarFieldSystem::StarFieldSystem()
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

void StarFieldSystem::renderStep()
{
	for (const auto& layer : m_stars)
	{
		for (const auto& star : layer)
		{
			aether::graphics::draw_filled_rectangle(star, { 1.0f, 1.0f, 1.0f });
		}
	}
}

void StarFieldSystem::step(double delta)
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
