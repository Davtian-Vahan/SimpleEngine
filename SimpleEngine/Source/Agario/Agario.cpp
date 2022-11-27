#include "Agario.h"
#include <Engine/Misc/MiscMathLibrary.h>
#include <chrono>
#include <thread>
#include <Agario/AgarioActor.h>


AgarioGame::AgarioGame()
	: GameBase(sf::VideoMode(1920.f, 1080.f))
{}

void AgarioGame::InitializeWorld()
{
	Super::InitializeWorld();

	// Bind event functions
	Super::onKeyPressed.AddRaw(this, &AgarioGame::onKeyPressed);
	Super::onKeyReleased.AddRaw(this, &AgarioGame::onKeyReleased);

	SpawnSomething();
}

void AgarioGame::InputHandling()
{
	Super::InputHandling();
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

void AgarioGame::onKeyPressed(sf::Event & tickEvent)
{
	TVector UpdateVelocity;

	if (tickEvent.key.code == sf::Keyboard::A)
	{
		ControlledActor->Move_X(-ControlledActor->Acceleration);
	}
	if (tickEvent.key.code == sf::Keyboard::D)
	{
		ControlledActor->Move_X(ControlledActor->Acceleration);
	}

	if (tickEvent.key.code == sf::Keyboard::W)
	{
		ControlledActor->Move_Y(-ControlledActor->Acceleration);
	}
	if (tickEvent.key.code == sf::Keyboard::S)
	{
		ControlledActor->Move_Y(ControlledActor->Acceleration);
	}
}

void AgarioGame::onKeyReleased(sf::Event& tickEvent)
{
	TVector UpdateVelocity;

	if (tickEvent.key.code == sf::Keyboard::A)
	{
		ControlledActor->Move_X(0);
	}
	if (tickEvent.key.code == sf::Keyboard::D)
	{
		ControlledActor->Move_X(0);
	}

	if (tickEvent.key.code == sf::Keyboard::W)
	{
		ControlledActor->Move_Y(0);

	}
	if (tickEvent.key.code == sf::Keyboard::S)
	{
		ControlledActor->Move_Y(0);
	}
}
