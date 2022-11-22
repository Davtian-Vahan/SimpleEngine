#include "ActorBase.h"
#include "SFML/Graphics/Sprite.hpp"
#include "SFML/Graphics/Drawable.hpp"
#include <Engine/Misc/MiscMathLibrary.h>
#include <Engine/Misc/SimpleCore.h>

// Set null collision by default
Actor::Actor()
	: CollisionFunc(nullptr), Acceleration(0.f),
	  Weight(0.f), MaxSpeed(0.f)
{
	try
	{
		texture = new sf::Texture();
		sprite = new sf::Sprite();
	}
	catch (std::bad_alloc&)
	{
		SimpleLogError("Class Actor: failed to allocate sprite or texture.");
		exit(EXIT_FAILURE);
	}
}

// Deallocate any further dynamic memory that will be coded
Actor::~Actor()
{
	delete texture;
	delete sprite;
}

// Called every frame
void Actor::Tick(float delta_time)
{
	setPosition(CurrentPosition);
	// Cache a desired position for main game class to grant
	DesiredPosition = CurrentPosition + Velocity * delta_time;
}

// Overriden from sf::Drawable
void Actor::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(*sprite, states);
}

// Self expl
void Actor::Move_X(float displace)
{
	float& x = Velocity.x;
	float& y = Velocity.y;

	if (std::abs(x) < MaxSpeed)
	{
		x += displace;
		printf("Displace x : %f\n", x);
		return;
	}
	
	x = 0;
	y = 0;
}

// Self expl
void Actor::Move_Y(float displace)
{
	float& x = Velocity.x;
	float& y = Velocity.y;

	if (std::abs(y) < MaxSpeed)
	{

		y += displace;
		printf("Displace y : %f\n", y);
		return;
	}

	x = 0;
	y = 0;
}

// Set texture for the sprite from a given file path
bool Actor::SetTexture(const char* file_path)
{
	// try to load the given texture
	if (!texture->loadFromFile(file_path))
		return false;
	// Set texture to sprite if loaded
	sprite->setTexture(*texture);
	return true;
}

// Self expl
void Actor::setPosition(TVector InPos)
{
	sprite->setPosition(CurrentPosition = InPos);
}

//
void Actor::setVelocity(const TVector& InVel)
{
	Velocity = InVel;
}

// Circle collision callback
Actor* Actor::CheckCircleCollision(Actor * C2)
{
	const Actor* C1 = this;
	const float radius_a = C1->getSpriteDimensions().y / 2.f;
	const float radius_b = C2->getSpriteDimensions().y / 2.f;
	const TVector  center_a = C1->getPosition() ;
	const TVector  center_b = C2->getPosition() ;
	if (SimpleMath::circle_collision(center_a, center_b, radius_a, radius_b))
	{
		return C2;
	}
	return nullptr;
}