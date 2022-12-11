#include "AgarioActor.h"
#include "Engine/Misc/MiscMathLibrary.h"

void AgarioActor::Tick(float delta_time)
{
	Actor::Tick(delta_time);
	// Your own tick logic
}

AgarioActor::AgarioActor()
{
	// Open texture asset for this actor
	bool Ok = 
	SetTexture("C:\\Users\\jedav\\Desktop\\SimpleEngine\\SimpleEngine\\Source\\Agario\\sample_texture.png");
	if (!Ok) SE_LOG("Failed to open asset.");

	GravityAcceleration = 150.f;
	CollResponse = CollisionResponse::RESP_PHYSICS;
	// Set scale and origin for this actors texture
	sprite->setScale(TVector(0.5, 0.5));
	sprite->setOrigin(sprite->getGlobalBounds().height, sprite->getGlobalBounds().width);

	// Set collision callback type for this actor
	CollisionFunc = &Actor::CheckCircleCollision;
}

void AgarioActor::setScale(float new_scale)
{
	sprite->setScale(TVector(new_scale, new_scale));
	sprite->setOrigin(sprite->getGlobalBounds().height / 2, sprite->getGlobalBounds().width / 2);
}
