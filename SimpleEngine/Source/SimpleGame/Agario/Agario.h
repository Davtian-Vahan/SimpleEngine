#pragma once

#include "../GameBase.h"

class AgarioGame : public GameBase
{
public:
	AgarioGame(size_t screen_height, size_t screen_width);

	virtual void InitializeWorld() override;
	virtual void InputHandling() override;
	virtual bool Update() override;
	virtual void FrameLogic() override;

	virtual ActorBase* TryMove(ActorBase* Actor, TVector offset) override;
	void SpawnCircles();
};