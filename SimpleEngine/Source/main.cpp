#include "SimpleGame/Game.h"

int main()
{
	srand(time(0));
	return Game::Run(1280.f, 720.f);
}