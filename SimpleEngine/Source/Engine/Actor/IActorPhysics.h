#pragma once

#include <Engine/Misc/SimpleCore.h>

class IActorPhysics
{
	friend class Actor;
protected:

	float   Speed;
	float   Weight;
	TVector Velocity;
	

};