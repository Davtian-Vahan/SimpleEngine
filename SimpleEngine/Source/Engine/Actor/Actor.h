#pragma once

#include "SFML/Graphics.hpp"
#include "SFML/Graphics/Texture.hpp"
#include "SFML/Graphics/Sprite.hpp"
#include <Engine/Collision/Collision.h>
#include <Engine/Misc/SimpleCore.h>

/*
	Base class for all SimpleEngine Actors
*/

class Actor : public sf::Drawable, public IForbidCopy
{
	friend class GameBase;
	typedef Actor* (Actor::*CollisionPredicate)(Actor*);
	friend class AgarioGame;

protected:
	// Texture sprite and collision type callable
	sf::Texture * texture;
	sf::Sprite  * sprite;

	// Rigidy body
	RigidBody* physics_body;

	CollisionPredicate CollisionFunc;
	CollisionResponse CollResponse;

	bool SetTexture(const char * file_path);

protected:
	// Physics and movement members
	Transform tranform;
	Physics   physics;

	float dAcc;
	float MaxVelocity;
	TVector Acceleration;
	TVector Velocity;
	TVector CurrentPosition;
	TVector DesiredPosition;

	bool bObeysGravity;
	float GravityAcceleration;

public:
	// Default Constructor / Destructor
	Actor();
	~Actor();

	// Called every frame for this actor
	virtual void Tick(float delta_time);

	// For SFML to consider this class as sf::Drawable
	virtual void draw(sf::RenderTarget& target, sf:: RenderStates states) const;

	// Handle 2D movement
	virtual void Move_X(float displace);
	virtual void Move_Y(float displace);

	// Setters for velocity and position
	void setPosition(TVector pos);
	void setVelocity(const TVector& InVel);

	void setObeysGravity(const bool);

	// Collision functions TODO: Move these somewhere smarter
	Actor* CheckCircleCollision(Actor* C2);
	Actor* CheckRectCollision(Actor* C2);

	// Getters for velocity and position
	inline TVector     getPosition() const { return sprite->getPosition(); }
	inline TVector     getVelocity() const { return Velocity; }

	// Return sprite global dimensions (considering transform)
	inline TVector getSpriteDimensions() const
	{
		return TVector(sprite->getGlobalBounds().height, sprite->getGlobalBounds().width);
	}
};