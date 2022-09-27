#pragma once
// Define SFML to be linked as a static library with the exe
#define SFML_STATIC 
#include <SFML/Graphics.hpp>
#include <list>

// Class responsible for handling game logic
class Game
{
protected:
	sf::RenderWindow render_window; // Handle to main window
	sf::VideoMode    video_mode;    // Handle to main window scale info
	static Game*	 game_instance; // Singleton for the main game instance

	// Test objects
	std::list<sf::Shape*> Actors;

	sf::Shape* ControlledActor = nullptr;

protected:
	void Draw();
	void Show();
	void PollEvent();

public:
	bool Update();
	Game(const sf::VideoMode& in_display);
	~Game();

public:
	sf::Vector2f GetPositionClamped(const sf::Vector2f& new_pos);
	void TryMove(sf::Shape *Actor, sf::Vector2f new_pos);

	sf::Shape* CollisionExists(sf::Shape* Actor);

	bool circle_collision(sf::Vector2f a, sf::Vector2f b, float r1, float r2);
	float vector_distance(sf::Vector2f vec_1, sf::Vector2f vec_2);

public:
	void SpawnShapes();
	sf::Vector2f GetRandomPosition();


public:
	static int Run(const size_t window_height, const size_t window_width);
};
