#include "ActorBase.h"
#include <Engine/Misc/SimpleCore.h>

bool ActorBase::SetTexture(const char* file_path)
{
	// try to load the given texture
	if (!texture.loadFromFile(file_path))
		return false;
	// Set texture to sprite if loaded
	sprite.setTexture(texture);
	return true;
}

void ActorBase::Move_X(float displace)
{
	TVector new_pos = sprite.getPosition();
	new_pos.x += displace;
	sprite.setPosition(new_pos);
}

void ActorBase::Move_Y(float displace)
{
	TVector new_pos = sprite.getPosition();
	new_pos.y += displace;
	sprite.setPosition(new_pos);
}

void ActorBase::setPosition(TVector pos)
{
	sprite.setPosition(pos);
}
