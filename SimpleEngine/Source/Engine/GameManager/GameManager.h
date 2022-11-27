#pragma once

class GameBase;

#include <Engine/Misc/SimpleCore.h>

/*
*	Implements a GameManager, responsible for
*	managing time and main game loop 
* 
*   Define DEBUG macro, to enable fps display to console
*/

class GameManager : public IForbidCopy
{
private:
	// Game refs and time/debug variables
	class GameBase* game_instance;
	
public:
	// Init constructor and main game loop starter function
	explicit GameManager(class GameBase* game_instance);
	~GameManager();

	// Start a game session
	int StartGame();
};