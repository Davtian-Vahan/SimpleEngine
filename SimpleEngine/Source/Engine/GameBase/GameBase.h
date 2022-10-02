#pragma once
// Define SFML to be linked as a static library with the exe
#define SFML_STATIC 
#include <list>
#include <SFML/Graphics.hpp>

#include <Engine/Misc/SimpleCore.h>
#include <Engine/ActorBase/ActorBase.h>

class GameBase
{
	friend class GameManager;
public:
	// Game loop functions
	virtual void Draw();
	virtual void Display();
	virtual void InputHandling();
	virtual void Tick(float delta_time);

protected:
	// Game logic functions
	void SpawnActor(ActorBase* actor);
	void DestroyActor(ActorBase* actor);
	void PossessToActor(ActorBase* actor);

public:
	// Constructor & Destructor
	explicit GameBase(const sf::VideoMode& in_display);
	~GameBase();

public:
	// Delete copy functions
	GameBase(const GameBase&) = delete;
	void operator=(const GameBase&) = delete;

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

public:
	// Called from outside the SimpleEngine, to start a game instance loop
	virtual void InitializeWorld();

protected:
	// Handle to main render window, video settings
	sf::RenderWindow render_window;
	sf::VideoMode    video_mode;

	bool bGameRunning;
	float delta_time;

	// Spawned actors
	std::list<ActorBase*> Actors;

	// Actor thats controlled by player
	ActorBase* ControlledActor = nullptr;
};