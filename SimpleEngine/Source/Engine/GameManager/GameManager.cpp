#include "GameManager.h"

#include <Engine/Misc/SimpleCore.h>
#include <Engine/GameBase/GameBase.h>

#define DEBUG
using namespace std::chrono;

GameManager::GameManager(GameBase* in_game_ref)
	: game_instance(in_game_ref), total_elapsed_time_s(0.f), debug_show_fps(true)
{}

GameManager::~GameManager()
{
	delete game_instance;
}

// Start main loop
int GameManager::StartGame()
{
	srand(time(0));

	// Time/frame related variables
	time_point frame_start_time = system_clock::now();
	time_point fps_start_time = system_clock::now();
	float  delta_time  = 0.f; 
	double fps_value   = 0.f;
	int    frame_count = 0;

	// Initialize game world 
	game_instance->InitializeWorld();

	// Start game loop
	while (game_instance->bGameRunning)
	{
		// Get current time
		frame_start_time = system_clock::now();

		// Main logical functions
		game_instance->InputHandling();
		game_instance->Tick(delta_time);
		game_instance->Draw();
		game_instance->Display();
		// Get time passed since start of the frame
		delta_time = duration_cast<seconds>(system_clock::now() - frame_start_time).count();

		#ifdef DEBUG
		// Calculate and show fps value per 3 secs (to console for now)
		time_point fps_end_time = system_clock::now();
		duration<double> dur = duration_cast<seconds>(fps_end_time - fps_start_time);
		if (dur.count() >= 1.0)
		{
			// calculate fps
			fps_value = frame_count / dur.count();

			// reset timer and frame count
			frame_count = 0;
			fps_start_time = system_clock::now();
		}

		printf("FPS %f\n", fps_value);
		#endif

		++frame_count;
	}

	#ifdef DEBUG
	printf("Session ended");
	#endif

	// Catch game related errors here
	// ...returns 0 for now
	return 0;
}