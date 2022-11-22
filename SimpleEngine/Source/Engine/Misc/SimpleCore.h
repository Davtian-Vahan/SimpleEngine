#pragma once

#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/Shape.hpp>
#include <SFML/Graphics/CircleShape.hpp>
#include <thread>
#include <chrono>
#include <exception>

#define SimpleCast(Type, Value) dynamic_cast<Type>(Value)
#define SleepThis(ms) std::this_thread::sleep_for(std::chrono::milliseconds(ms))
#define SimpleLogError(msg) printf(msg)

typedef sf::Vector2f	   TVector;
typedef sf::CircleShape    CircleActor;