#include <aether/aether.h>


class GameplayScreen : public aether::core::IScreen
{
public:

	// Inherited via IScreen
	virtual void show() override;

	virtual void hide() override;
	
	virtual void update(uint64_t delta) override;

	virtual void render() override;

private:
	aether::graphics::Animation m_anim;
	aether::graphics::AnimationData m_animData;
	aether::graphics::Font m_font;
	aether::graphics::TextData m_textData;
	StarFieldSystem m_stars;

};