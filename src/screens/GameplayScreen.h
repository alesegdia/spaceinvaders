#include <aether/aether.h>

#include "../ecs/ECSWorld.h"

class GameplayScreen : public aether::core::IScreen
{
public:

	// Inherited via IScreen
	virtual void show() override;

	virtual void hide() override;
	
	virtual void update(uint64_t delta) override;

	virtual void render() override;

private:
	aether::graphics::Font m_font;
	aether::graphics::TextData m_textData;
	ECSWorld m_ecsWorld;

	uint64_t m_spawnRate = 1e6;
	uint64_t m_nextSpawn = 0;

};