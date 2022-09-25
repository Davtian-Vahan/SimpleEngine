#pragma once
// Define SFML to be linked as a static library with the exe
#define SFML_STATIC 
#include <SFML/Graphics.hpp>

// Class responsible for handling game logic
class Game
{
protected:
	sf::RenderWindow render_window; // Handle to main window
	sf::VideoMode    video_mode;    // Handle to main window scale info
	static Game*	 game_instance; // Singleton for the main game instance

	// Test objects
	sf::RectangleShape RectActor;

protected:
	void Draw();
	void Show();
	void PollEvent();

public:
	bool Update();
	Game(const sf::VideoMode& in_display);

public:
	static int Run(const size_t window_height, const size_t window_width);
};
