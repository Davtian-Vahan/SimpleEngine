#pragma once

#include <Engine/ActorBase/ActorBase.h>
#include <array>

class AgarioActor : public Actor
{
public:
	virtual void Tick(float delta_time) override;
	AgarioActor();

	void setScale(float new_scale);
};

