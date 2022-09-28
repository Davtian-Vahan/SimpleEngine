#include "SimpleGame/Agario/Agario.h"

int main()
{
	srand(time(0));
	GameBase* NewGame = new AgarioGame(1920.f, 1080.f);

	NewGame->InitializeWorld();
	NewGame->Run();
	
	return 0;
}