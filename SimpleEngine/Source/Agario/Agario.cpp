#include "Agario.h"
#include <Engine/Misc/MiscMathLibrary.h>
#include <chrono>
#include <thread>
#include <Agario/AgarioActor.h>

AgarioGame::AgarioGame(size_t screen_height, size_t screen_width)
	: GameBase(sf::VideoMode(screen_height, screen_width))
{}

AgarioGame::AgarioGame()
	: GameBase(sf::VideoMode(1920.f, 1080.f))
{}

void AgarioGame::InitializeWorld()
{
	Super::InitializeWorld();
	SpawnSomething();
}

void AgarioGame::InputHandling()
{
	Super::InputHandling();

	TVector displace{ 0.f, 0.f };
	float speed_mutiplier = 0.1;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		displace.x -= speed_mutiplier;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		displace.x += speed_mutiplier;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		displace.y -= speed_mutiplier;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		displace.y += speed_mutiplier;
	}

	TryMove(ControlledActor, displace);
}

void AgarioGame::Tick(float delta_time)
{
	Super::Tick(delta_time);
}

void AgarioGame::SpawnSomething()
{
	// Spawn a test actor
	AgarioActor* character = new AgarioActor();
	for (int i = 0; i < 100; ++i)
	{
		AgarioActor* temp_actor = new AgarioActor();
		temp_actor->setPosition(GetRandScreenPosition());
		// temp_actor->getDrawable().setColor(SimpleMath::random_rgb());
		SpawnActor(temp_actor);
	}
	SpawnActor(character);
	ControlledActor = character;
}

ActorBase* AgarioGame::TryMove(ActorBase* Actor, TVector offset)
{
	Super::ForceMove(Actor, offset);
	return nullptr;
}