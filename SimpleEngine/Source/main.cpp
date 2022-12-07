

#include <Agario/Agario.h>
#include <Engine/GameManager/GameManager.h>

int main()
{
	GameManager manager(new AgarioGame);
	return manager.StartGame();
}