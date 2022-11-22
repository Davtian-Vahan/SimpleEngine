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

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		ControlledActor->Move_X(-1.f * ControlledActor->Acceleration);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		ControlledActor->Move_X(ControlledActor->Acceleration);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		ControlledActor->Move_Y(ControlledActor->Acceleration);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		ControlledActor->Move_Y(-1.f * ControlledActor->Acceleration);
	}
}

void AgarioGame::Tick(float delta_time)
{
	Super::Tick(delta_time);
}

void AgarioGame::SpawnSomething()
{
	// Spawn a test actor
	AgarioActor* character = new AgarioActor();
	for (int i = 0; i < 3; ++i)
	{
		AgarioActor* temp_actor = new AgarioActor();
		temp_actor->setPosition(GetRandScreenPosition());
		SpawnActor(temp_actor);
	}
	SpawnActor(character);
	ControlledActor = character;
}