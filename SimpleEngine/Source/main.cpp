#include "Agario/Agario.h"
#include <Engine/GameManager/GameManager.h>

int main()
{
	GameManager Manager(new AgarioGame());
	return Manager.StartGame();
}