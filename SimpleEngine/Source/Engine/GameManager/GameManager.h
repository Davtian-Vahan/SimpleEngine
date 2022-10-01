#pragma once

class GameBase;

/*
*	Implements a GameManager, responsible for
*	managing time and main game loop 
* 
*   Define DEBUG macro, to enable fps display to console
*/

class GameManager
{
private:
	// Game refs and time/debug variables
	class GameBase* game_instance;
	float total_elapsed_time_s;
	bool  debug_show_fps;
	
public:
	// Init constructor and main game loop starter function
	explicit GameManager(class GameBase* game_instance);
	~GameManager();
	int StartGame();

public:
	// Deleted functions
	GameManager(const GameManager&) = delete;
	void operator=(const GameManager&) = delete;

	// Some getters
	inline float TotalElapsedTime() const { return total_elapsed_time_s; }
};