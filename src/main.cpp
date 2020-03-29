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
		m_font.load("assets/default.ttf", 64);
		auto enemyFrames = GetFrames("assets/Enemy/Enemy_animation/", 1, 8);
		m_anim.addFrames(enemyFrames);
		m_anim.reset(m_animData);
		m_textData = m_font.createTextTexture("Space Invaders", aether::graphics::Color(1.0f, 1.0f, 1.0f));
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
		m_animData.currentFrame->texture.draw(0, 0, 0.5f, 0.5f);
		m_textData.draw(10, 10);
	}

private:
	aether::graphics::Animation m_anim;
	aether::graphics::AnimationData m_animData;
	aether::graphics::Font m_font;
	aether::graphics::TextData m_textData;

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
