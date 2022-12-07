#include "Agario.h"
#include <Agario/AgarioActor.h>
#include <Engine/Misc/MiscMathLibrary.h>

AgarioGame::AgarioGame()
	: Super(1920.f, 1080.f)
{}

void AgarioGame::InitializeWorld()
{
	Super::InitializeWorld();

	// Bind event functions
	Super::onKeyPressed.AddRaw(this, &AgarioGame::onKeyPressed);
	Super::onKeyReleased.AddRaw(this, &AgarioGame::onKeyReleased);

	// Spawn a main character
	AgarioActor* character = new AgarioActor();
	SpawnActor(character);
	ControlledActor = character;

	// Spawn some other random actors
	SpawnRandomActors();
}

void AgarioGame::InputHandling()
{
	Super::InputHandling();
}

void AgarioGame::Tick(float delta_time)
{
	Super::Tick(delta_time);
}

void AgarioGame::SpawnRandomActors()
{
	TVector PrevPos;
	// Spawn 5 random actors
	for (int i = 0; i < 5; ++i)
	{
		AgarioActor* RandActor = new AgarioActor();
		TVector NewPosition(PrevPos.x + 400.f, PrevPos.y);
		RandActor->setPosition(NewPosition);
		SpawnActor(RandActor);
		PrevPos = NewPosition;
	}
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