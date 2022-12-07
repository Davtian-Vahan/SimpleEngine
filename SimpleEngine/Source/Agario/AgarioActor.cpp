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

	//
	Acceleration = 1000.f;
	bObeyGravity = true;
	GravityAcceleration = 150.f;
	// Set scale and origin for this actors texture
	sprite->setScale(TVector(0.5, 0.5));
	sprite->setOrigin(sprite->getGlobalBounds().height, sprite->getGlobalBounds().width);

	// Set collision callback type for this actor
	CollisionFunc = &Actor::CheckCircleCollision;
}
