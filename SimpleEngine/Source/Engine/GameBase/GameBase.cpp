#include "GameBase.h"
#include <Engine/Misc/MiscMathLibrary.h>
#include <chrono>
#include <thread>
#include <ctime>

// Draw each frame, called from game loop
void GameBase::Draw()
{
	render_window.clear(sf::Color(128, 128, 128));
	for (Actor* Actor : Actors)
	{
		render_window.draw(*Actor);
	}
}

// Display each frame, called from game loop
void GameBase::Display()
{
	render_window.display();
}

// Handle input each frame, called from game loop
void GameBase::InputHandling()
{
	sf::Event poll_event;
	while (render_window.pollEvent(poll_event))
	{
		if (poll_event.type == sf::Event::Closed)
		{
			render_window.close();
			bGameRunning = false;
			break;
		}

		// Broadcast key pressed and released delegates
		if (poll_event.type == sf::Event::KeyPressed)
		{
			onKeyPressed.Broadcast(poll_event);
		}

		if (poll_event.type == sf::Event::KeyReleased)
		{
			onKeyReleased.Broadcast(poll_event);
		}
	}
}

void GameBase::Tick(float dt)
{
	// Time related member updates go here
	// ...........
	this->delta_time = dt;
	TickActors(dt);
}

void GameBase::SpawnActor(Actor* actor)
{
	Actors.push_back(actor);
}

void GameBase::DestroyActor(Actor* actor)
{
	Actors.remove(actor);
	delete actor;
}

void GameBase::PossessToActor(Actor* actor)
{
	ControlledActor = actor;
}

void GameBase::TickActors(float dt)
{
	for (Actor* IterActor : Actors)
	{
		IterActor->Tick(dt);
		TryMove(IterActor, IterActor->DesiredPosition);
	}
}

// Tries to move if no collision, else return collided actor
Actor* GameBase::TryMove(Actor* InActor, TVector PossiblePos)
{
	TVector CachedPos = InActor->getPosition();
	// Set new clamped position
	InActor->setPosition(GetPositionClamped(PossiblePos));

	// Check for collision 
	Actor* CollidedActor = CollisionExists(InActor);

	//If moving causes collision, reset movement
	if (CollidedActor)
	{
		InActor->setPosition(CachedPos);
		return CollidedActor;
	}
	return nullptr;
}

// Return if given actor collides with any other known actor
Actor* GameBase::CollisionExists(Actor* InActor)
{
	// Checks for circle collision only for now
	for (Actor* IterActor : Actors)
	{
		Actor* C1 = InActor;  
		Actor* C2 = IterActor;
		// No collision with itself
		if (C1 == C2) { continue; }
		// Check for collision with the appropriate collision predicate 
		if (C1->CollisionFunc)
		{
			Actor* CollidedActor = (C1->*(C1->CollisionFunc))(C2);
			if (CollidedActor)
			{
				return CollidedActor;
			}
		}
	}
	return nullptr;
}

// Generic clamped position, collision not checked yet
TVector GameBase::GetPositionClamped(const TVector& new_pos)
{
	TVector res_pos = new_pos;
	res_pos.x = SimpleMath::clamp(res_pos.x, 0, video_mode.width);
	res_pos.y = SimpleMath::clamp(res_pos.y, 0, video_mode.height);

	return res_pos;
}

// Returns a random non clamped position on the screen
TVector GameBase::GetRandScreenPosition()
{
	return TVector(rand() % video_mode.width, rand() % video_mode.height);
}

void GameBase::InitializeWorld()
{
	bGameRunning = true;
}

void GameBase::ToggleVsync(bool new_vsync)
{
	render_window.setVerticalSyncEnabled(new_vsync);
}

// Only init constructor for now, feed it video dimensions
GameBase::GameBase(const int VideoWidth, const int VideoHeight)
	: render_window(video_mode, ""), video_mode(VideoWidth, VideoHeight),
	  bGameRunning(false),			 delta_time(0.f)
{}

// Destructor, release memory of actors
GameBase::~GameBase()
{
	for (const Actor* Actor : Actors)
	{
		delete Actor;
	}
}