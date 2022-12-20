#pragma once

#include <Engine/Misc/SimpleCore.h>
#include <Engine/Delegate/Delegate.h>
#include <Engine/Misc/Math.h>

enum class CollisionResponse { RESP_NONE, RESP_BLOCK, RESP_PHYSICS};

class ICollisionFuncs
{
	// Circle collision callback
	
};

class RigidBody
{

};

class RectBody;

class CircleBody : public RigidBody
{

protected:
	float Radius;
	TVector Center;

public:

	bool AgainstRect(const RectBody& rect) const;
	bool AgainstSelf(const CircleBody& rect) const;

};

class RectBody : public RigidBody
{
public:
	TVector Center;
	float Width;
	float Height;
};

class TriangleBody : public RigidBody
{

};