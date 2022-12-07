#pragma once
// Define SFML to be linked as a static library with the exe
//#define SFML_STATIC 
#include <list>
#include <SFML/Graphics.hpp>

#include <Engine/Misc/SimpleCore.h>
#include <Engine/ActorBase/ActorBase.h>
#include <Engine/Delegate/Delegate.h>

class GameBase : public IForbidCopy
{
	friend class GameManager;

protected:
	// Input handler delegates
	MulticastDelegate<sf::Event&> onKeyPressed;
	MulticastDelegate<sf::Event&> onKeyReleased;

public:
	// Game loop functions
	virtual void Draw();
	virtual void Display();
	virtual void InputHandling();
	virtual void Tick(float delta_time);

protected:
	// Game logic functions
	void SpawnActor(Actor* actor);
	void DestroyActor(Actor* actor);
	void PossessToActor(Actor* actor);
	void TickActors(float);

public:
	// Constructor & Destructor
	explicit GameBase(const int VideoWidth, const int VideoHeight);
	explicit GameBase(const sf::VideoMode& in_display);
	virtual ~GameBase();

public:
	// Movement and collision related functions
	// Tries to move, returns blocker if failed
	virtual Actor* TryMove(Actor* Actor, TVector new_pos);

	// Returns the collided actor to the given Actor
	Actor* CollisionExists(Actor* Actor);

	// Clamp a given position bounded to the screen width/height
	TVector GetPositionClamped(const TVector& new_pos);

public:
	// Random functions TODO: Categorize
	TVector GetRandScreenPosition();

public:
	// Called from outside the SimpleEngine, to start a game instance loop
	virtual void InitializeWorld();

	void ToggleVsync(bool);

protected:
	// Handle to main render window, video settings (Order of initialization is important)
	sf::VideoMode    video_mode;
	sf::RenderWindow render_window;

	bool bGameRunning;
	float delta_time;

	// Spawned actors
	std::list<Actor*> Actors;

	// Actor thats controlled by player
	Actor* ControlledActor = nullptr;
};