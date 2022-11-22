#pragma once

#include <Engine/ActorBase/ActorBase.h>

class AgarioActor : public Actor
{
public:
	virtual void Tick(float delta_time) override;
	AgarioActor();
};