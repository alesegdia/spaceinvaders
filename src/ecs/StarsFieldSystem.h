#pragma once

#include <aether/aether.h>

#include <secs/secs.h>


class StarFieldSystem : public secs::System
{
public:
	using Star = aether::math::Rectf;
	using StarsLayer = std::vector<Star>;

	StarFieldSystem();

	void renderStep() override;

	void step(double delta) override;


private:
	StarsLayer m_stars[3];
};