#include "Game.h"


namespace
{
	int s_hiscore = 0;
}

void set_hiscore(int hiscore)
{
	s_hiscore = hiscore;
}

int get_hiscore()
{
	return s_hiscore;
}
