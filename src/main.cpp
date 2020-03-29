#include <aether/aether.h>

class Game : public aether::core::Application
{
public:
	Game(int w, int h)
		: aether::core::Application(w, h)
	{

	}
};

int main(int argc, char** argv)
{
	return Game(100, 100).exec(argc, argv);
}
