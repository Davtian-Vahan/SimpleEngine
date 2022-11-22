#pragma once

#include <Engine/GameBase/GameBase.h>

class AgarioGame : public GameBase
{
public:
	AgarioGame(size_t screen_height, size_t screen_width);
	AgarioGame();

	virtual void InitializeWorld() override;
	virtual void InputHandling() override;
	virtual void Tick(float delta_time) override;

	void SpawnSomething();

	typedef GameBase Super;
};