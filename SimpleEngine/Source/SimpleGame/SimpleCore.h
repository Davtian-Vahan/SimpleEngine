#pragma once

#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/Shape.hpp>
#include <SFML/Graphics/CircleShape.hpp>

#define SimpleCast(Type, Value) dynamic_cast<Type>(Value)

typedef sf::Vector2f	   TVector;
typedef sf::Shape		   ActorBase;
typedef sf::CircleShape    CircleActor;