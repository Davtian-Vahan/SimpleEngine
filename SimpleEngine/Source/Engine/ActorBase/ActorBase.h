#pragma once
#include <SFML/Graphics/Shape.hpp>
#include <SFML/Graphics/CircleShape.hpp>
#include "SFML/Graphics/Texture.hpp"
#include "SFML/Graphics/Sprite.hpp"
#include "../Misc/SimpleCore.h"

class ActorBase 
{
protected:
	sf::Texture texture;
	sf::Sprite sprite;

	bool SetTexture(const char * file_path);
public:
	virtual void Move_X(float displace);
	virtual void Move_Y(float displace);

	sf::Sprite& getDrawable() { return sprite; }
	TVector getPosition() { return sprite.getPosition(); }

	void setPosition(TVector pos);
};