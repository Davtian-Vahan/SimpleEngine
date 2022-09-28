#pragma once
// Define SFML to be linked as a static library with the exe
#define SFML_STATIC 
#include <SFML/Graphics.hpp>
#include <list>
#include "SimpleCore.h"

/*
	GameBase declaration
*/

class GameBase
{
public:
	// Game loop functions
	virtual void Draw();
	virtual void Display();
	virtual void InputHandling();
	virtual void FrameLogic() = 0;

protected:
	// Game logic functions
	void SpawnActor(ActorBase* actor);
	void DestroyActor(ActorBase* actor);
	void PossessToActor(ActorBase* actor);

public:
	// Constructor & Destructor
	GameBase(const sf::VideoMode& in_display);
	~GameBase();

public:
	// Movement and collision related functions
	
	// Force a move to given position, even if blocked
	void ForceMove(ActorBase* Actor, TVector new_pos);

	// Tries to move, returns blocker if failed
	virtual ActorBase* TryMove(ActorBase* Actor, TVector new_pos);

	// Returns the collided actor to the given Actor
	ActorBase* CollisionExists(ActorBase* Actor);

	// Clamp a given position bounded to the screen width/height
	TVector GetPositionClamped(const TVector& new_pos);

public:
	// Random functions TODO: Categorize
	TVector GetRandScreenPosition();

private:
	// Singleton for the main game instance
	static GameBase* game_instance; 

	// Game loop updater function
	virtual bool Update() = 0;
public:
	// Called from outside the SimpleEngine, to start a game instance loop
	void Run();
	virtual void InitializeWorld() = 0;

protected:
	// Handle to main render window, video settings
	sf::RenderWindow render_window;
	sf::VideoMode    video_mode;

	// Spawned actors
	std::list<ActorBase*> Actors;

	// Actor thats controlled by player
	ActorBase* ControlledActor = nullptr;
};