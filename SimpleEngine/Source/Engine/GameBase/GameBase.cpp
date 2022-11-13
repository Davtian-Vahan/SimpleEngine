#include "GameBase.h"
#include <Engine/Misc/MiscMathLibrary.h>
#include <chrono>
#include <thread>
#include <ctime>

// Draw each frame, called from game loop
void GameBase::Draw()
{
	render_window.clear(sf::Color(128, 128, 128));
	for (ActorBase* Actor : Actors)
	{
		render_window.draw(**Actor);
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
		}
	}
}

void GameBase::Tick(float delta_time)
{
	// Time related member updates go here
	// ...........
	this->delta_time = delta_time;
}

void GameBase::SpawnActor(ActorBase* actor)
{
	Actors.push_back(actor);
}

void GameBase::DestroyActor(ActorBase* actor)
{
	Actors.remove(actor);
	delete actor;
}

void GameBase::PossessToActor(ActorBase* actor)
{
	ControlledActor = actor;
}

void GameBase::ForceMove(ActorBase* Actor, TVector offset)
{
	// Add the offset to current position and clamp it to screen 
	const TVector ResultPos = GetPositionClamped(Actor->getPosition() + offset);

	// Set new clamped position
	Actor->setPosition(ResultPos);
}

// Tries to move if no collision, else return collided actor
ActorBase* GameBase::TryMove(ActorBase* Actor, TVector offset)
{
	TVector CachedPos = Actor->getPosition();
	TVector ResultPos = GetPositionClamped(Actor->getPosition() + offset);
	// Set new clamped position
	Actor->setPosition(ResultPos);

	// Check for collision 
	ActorBase* CollidedActor = CollisionExists(Actor);

	//If moving causes collision, reset movement
	if (CollidedActor)
	{
		Actor->setPosition(CachedPos);
		return CollidedActor;
	}
	return nullptr;
}

// Return if given actor collides with any other known actor
ActorBase* GameBase::CollisionExists(ActorBase* Actor)
{
	// Checks for circle collision only for now
	for (ActorBase* IterActor : Actors)
	{
		// 
		ActorBase* C1 = Actor;  
		ActorBase* C2 = IterActor;

		// no collision with itself
		if (C1 == C2) { continue; }

		const TVector  center_a = C1->getPosition();
		const TVector  center_b = C2->getPosition();

		const float radius_a = C1->getCollisionRadius();
		const float radius_b = C2->getCollisionRadius();

		if (SimpleMath::circle_collision(center_a, center_b, radius_a, radius_b))
		{
			return C2;
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

// Constructor
GameBase::GameBase(const sf::VideoMode& in_videomode)
	: render_window(in_videomode, ""), video_mode(in_videomode),
	  bGameRunning(false), delta_time(0.f)
{}

// Destructor, release memory of actors
GameBase::~GameBase()
{
	for (const ActorBase* Actor : Actors)
	{
		delete Actor;
	}
}