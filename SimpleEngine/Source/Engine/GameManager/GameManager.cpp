#include "GameManager.h"
#include <Engine/Misc/SimpleCore.h>
#include <Engine/GameBase/GameBase.h>

using namespace std::chrono;

#define SHOW_FPS

// Start main loop
int GameManager::StartGame()
{
	srand(time(0));

	// Time/frame related variables
	sf::Clock clock;
	sf::Clock clockFPS;
	double fps_value = 0.f;
	long frame_count = 0;

	// Temporary frame limit to mitigate gpu usage
	const float MaxFps = 400.f;

	// Initialize game world 
	game_instance->InitializeWorld();
	// Enable vsync
	//game_instance->ToggleVsync(true);
	game_instance->SetFrameLimit(MaxFps);

	// Start game loop
	while (game_instance->bGameRunning)
	{
		// Get time elapsed since last call to restart()
		float dt = clock.restart().asSeconds();

		// Main logical functions
		game_instance->InputHandling();
		game_instance->Tick(dt);
		game_instance->Draw();
		game_instance->Display();

		// Calculate and show fps value per 3 secs (to console for now)
		{
			#ifdef SHOW_FPS
			float duration = clockFPS.getElapsedTime().asSeconds();
			if (duration >= 1.0)
			{
				// Calculate FPS and reset frame counter
				fps_value = frame_count / clockFPS.restart().asSeconds();
				frame_count = 0;
			}
			#endif
		}

		// Update fps info on screen
		game_instance->SetFpsText(std::to_string(int(fps_value)) + " :fps");
		++frame_count;
	}

	SE_LOG("Session Ended.");

	// Catch game related errors here
	return 0;
}

GameManager::GameManager(GameBase* in_game_ref)
	: game_instance(in_game_ref)
{}

GameManager::~GameManager()
{
	delete game_instance;
}