#include "AgarioActor.h"
#include <Engine/Misc/Math.h>
#include <Engine/Misc/Paths.h>

void AgarioActor::Tick(float delta_time)
{
	Actor::Tick(delta_time);
	// Your own tick logic
}

AgarioActor::AgarioActor()
{
	// Open texture asset for this actor
	std::string TexturePath = Paths::source_dir() + "\\Agario\\sample_texture.png";
	bool Ok = 
	SetTexture(TexturePath.c_str());
	if (!Ok) SE_LOG("Failed to open asset.");

	GravityAcceleration = 150.f;
	CollResponse = CollisionResponse::RESP_PHYSICS;
	// Set scale and origin for this actors texture
	sprite->setScale(TVector(0.5, 0.5));
	sprite->setOrigin(sprite->getGlobalBounds().height, sprite->getGlobalBounds().width);

	// Set collision callback type for this actor
	CollisionFunc = &Actor::CheckCircleCollision;

	// Allocate a type of physics body
	physics_body = new CircleBody();
}

void AgarioActor::setScale(float new_scale)
{
	sprite->setScale(TVector(new_scale, new_scale));
	sprite->setOrigin(sprite->getGlobalBounds().height / 2, sprite->getGlobalBounds().width / 2);
}
