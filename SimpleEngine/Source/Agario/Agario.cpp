#include "Agario.h"
#include <Agario/AgarioActor.h>
#include <Engine/Misc/Math.h>

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
	SpawnActorSafe(character);
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
	// Spawn some random actors
	for (int i = 0; i < 30; ++i)
	{
		AgarioActor* RandActor = new AgarioActor();
		float RandScale = SEMath::RandRange(0.f, 1.f);
		TVector RandPos(GetRandScreenPosition());
		RandActor->setPosition(RandPos);
	 // RandActor->setObeysGravity(true);

		if (!SpawnActorSafe(RandActor))
		{
			delete RandActor;
		}
	}
}

void AgarioGame::onKeyPressed(sf::Event & tickEvent)
{
	const float dAcc = 10.f;
	const float MaxAcc = 15.f;
	if (tickEvent.key.code == sf::Keyboard::A)
	{
		ControlledActor->Acceleration.x += -dAcc;
	}
	if (tickEvent.key.code == sf::Keyboard::D)
	{
		ControlledActor->Acceleration.x += dAcc;
	}

	if (tickEvent.key.code == sf::Keyboard::W)
	{
		ControlledActor->Acceleration.y += -dAcc;

	}
	if (tickEvent.key.code == sf::Keyboard::S)
	{
		ControlledActor->Acceleration.y += dAcc;
	}

	ControlledActor->Acceleration.x = SEMath::clamp(ControlledActor->Acceleration.x, -MaxAcc, MaxAcc);
	ControlledActor->Acceleration.y = SEMath::clamp(ControlledActor->Acceleration.y, -MaxAcc, MaxAcc);
}

void AgarioGame::onKeyReleased(sf::Event& tickEvent)
{
	if (tickEvent.key.code == sf::Keyboard::A)
	{
		ControlledActor->Acceleration.x =0;
	}
	if (tickEvent.key.code == sf::Keyboard::D)
	{
		ControlledActor->Acceleration.x = 0;
	}

	if (tickEvent.key.code == sf::Keyboard::W)
	{
		ControlledActor->Acceleration.y = 0;

	}
	if (tickEvent.key.code == sf::Keyboard::S)
	{
		ControlledActor->Acceleration.y = 0;
	}
}