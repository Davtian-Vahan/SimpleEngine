#include "Actor.h"
#include "SFML/Graphics/Sprite.hpp"
#include "SFML/Graphics/Drawable.hpp"
#include <Engine/Misc/Math.h>
#include <Engine/Misc/SimpleCore.h>

// Set null collision by default
Actor::Actor()
	: CollisionFunc(nullptr), Acceleration(0.f, 0.f), bObeysGravity(false),
	GravityAcceleration(100.f), CollResponse(CollisionResponse::RESP_NONE),
	MaxVelocity(5.f), physics_body(nullptr)
{
	try
	{
		texture = new sf::Texture();
		sprite = new sf::Sprite();
	}
	catch (std::bad_alloc&)
	{
		SE_LOG("Class Actor: failed to allocate sprite or texture.");
		exit(EXIT_FAILURE);
	}
}

// Deallocate any further dynamic memory that will be coded
Actor::~Actor()
{
	delete texture;
	delete sprite;
	delete physics_body;
}

// Called every frame
void Actor::Tick(float delta_time)
{
	// Update velocity based on acceleration
	Velocity += Acceleration;

	// Dampen velocity
	Velocity /= 1.01f;

	// Update position based on velocity and time
	DesiredPosition = CurrentPosition + Velocity * delta_time;

	// Handle gravity
	if (bObeysGravity)
	{
		DesiredPosition.y += delta_time * GravityAcceleration;
	}
}

// Overriden from sf::Drawable
void Actor::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(*sprite, states);
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


// Circle collision callback
Actor* Actor::CheckCircleCollision(Actor* C2)
{
	const Actor* C1 = this;
	const float radius_a = C1->getSpriteDimensions().y / 2;
	const float radius_b = C2->getSpriteDimensions().y / 2;
	const TVector center_a = C1->getPosition();
	const TVector center_b = C2->getPosition();
	if (SEMath::circle_collision(center_a, center_b, radius_a, radius_b))
	{
		return C2;
	}
	return nullptr;
}

// Circle collision callback
Actor* Actor::CheckRectCollision(Actor* C2)
{
	if (this->sprite->getGlobalBounds().intersects(C2->sprite->getGlobalBounds()))
	{
		return C2;
	}
	return nullptr;
}

// Setters
void Actor::setPosition(TVector InPos)
{
	sprite->setPosition(CurrentPosition = InPos);
}

//
void Actor::setVelocity(const TVector& InVel)
{
	Velocity = InVel;
}

//
void Actor::setObeysGravity(const bool inGravity)
{
	bObeysGravity = inGravity;
}

// 
void Actor::Move_X(float displace)
{
	Velocity.x += displace;
}

// 
void Actor::Move_Y(float displace)
{
	Velocity.y += displace;
}