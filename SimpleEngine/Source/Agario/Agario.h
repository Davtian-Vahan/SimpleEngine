#pragma once

#include <Engine/GameBase/GameBase.h>

class AgarioGame : public GameBase
{
public:
	AgarioGame();

	virtual void InitializeWorld() override;
	virtual void InputHandling() override;
	virtual void Tick(float delta_time) override;

	void SpawnSomething();

	void onKeyPressed(sf::Event& );
	void onKeyReleased(sf::Event& );

	typedef GameBase Super;
};