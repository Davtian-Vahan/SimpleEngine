#include "Agario.h"
#include <Engine/Misc/MiscMathLibrary.h>
#include <chrono>
#include <thread>

AgarioGame::AgarioGame(size_t screen_height, size_t screen_width)
	: GameBase(sf::VideoMode(screen_height, screen_width))
{}

AgarioGame::AgarioGame()
	: GameBase(sf::VideoMode(1920.f, 1080.f))
{}

void AgarioGame::InitializeWorld()
{
	Super::InitializeWorld();
	SpawnCircles();
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

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
	{
		displace.y += speed_mutiplier;
	}


	TryMove(ControlledActor, displace);
}

void AgarioGame::Tick(float delta_time)
{
	Super::Tick(delta_time);

	if (Actors.size() == 1)
	{
		ControlledActor->setFillColor(sf::Color::Red);
	}
}

void AgarioGame::SpawnCircles()
{
	int circle_count = 20; 
	for (int it = 0; it < circle_count; ++it)
	{
		CircleActor* circle = new CircleActor(15.f);
		do
		{
			TVector position = GetRandScreenPosition();
			circle->setPosition(GetPositionClamped(position));

			float radius = 2 + rand() % 50;
			circle->setRadius(radius);

			// set origin to be center
			circle->setOrigin(circle->getRadius(), circle->getRadius());

		} while (CollisionExists(circle));

		circle->setFillColor(SimpleMath::random_rgb());
		SpawnActor(circle);
	}

	// Spawn my player character
	float character_radius = 15;
	CircleActor* character = new CircleActor(character_radius);

	TVector position = GetRandScreenPosition();
	character->setOrigin(character_radius, character_radius);
	character->setPosition(GetPositionClamped(position));

	SpawnActor(character);
	PossessToActor(character);
}

ActorBase* AgarioGame::TryMove(ActorBase* Actor, TVector offset)
{
	CircleActor* HitActor = SimpleCast(CircleActor*, Super::TryMove(Actor, offset));
	CircleActor* MyActor = SimpleCast(CircleActor*, Actor);

	if (HitActor)
	{
		float HitActorRadius = HitActor->getRadius();
		float MyActorRadius = MyActor->getRadius();
		float NewRadius = HitActorRadius + MyActorRadius;
		float AnimRadiusIter = MyActorRadius;

		if (MyActorRadius <= HitActorRadius)
		{
			return HitActor;
		}

		// Eat collided actor
		Actors.remove(HitActor);

		// Play getting bigger animation
		while (AnimRadiusIter < NewRadius)
		{
			MyActor->setRadius(AnimRadiusIter);
			MyActor->setOrigin(AnimRadiusIter, AnimRadiusIter);
			Draw();
			Display();
			AnimRadiusIter += 1.f;
			std::this_thread::sleep_for(std::chrono::milliseconds(10));
		}
	}
	return HitActor;
}