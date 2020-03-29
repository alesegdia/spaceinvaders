#include <aether/aether.h>
#include <memory>

std::vector<aether::graphics::TextureRegion> GetFrames(std::string base, int from, int to)
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

class SampleScreen : public aether::core::IScreen
{
public:

	// Inherited via IScreen
	virtual void show() override
	{
		m_tex.load("assets/Enemy/spaceship_enemy_red.png");
		m_enemyFrames = GetFrames("assets/Enemy/Enemy_animation/", 1, 8);

		std::vector<const aether::graphics::TextureRegion*> v;
		for (auto& tr : m_enemyFrames)
		{
			v.push_back(&tr);
		}

		m_anim.addFrames(v);
		m_animData.reset();
		m_anim.reset(m_animData);
		m_anim.updateData(m_animData);
	}
	virtual void hide() override
	{
	}
	virtual void update(uint64_t delta) override
	{
		m_animData.timer += delta;
		m_anim.updateData(m_animData);
	}
	virtual void render() override
	{
		aether::graphics::clear(0, 0, 0);
		//m_tex.draw(0, 0);
		m_animData.currentFrame->texture->draw(0, 0);
	}

private:
	aether::graphics::Texture m_tex;
	aether::graphics::Animation m_anim;
	aether::graphics::AnimationData m_animData;
	std::vector<aether::graphics::TextureRegion> m_enemyFrames;

};

class Game : public aether::core::Application
{
public:
	Game(int w, int h)
		: aether::core::Application(w, h)
	{

	}

	virtual int ready(int argc, char** argv)
	{
		setScreen(std::make_shared<SampleScreen>());
		return 0;
	}

};

int main(int argc, char** argv)
{
	return Game(800, 600).exec(argc, argv);
}
