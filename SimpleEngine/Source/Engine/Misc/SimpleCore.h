#pragma once

#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/Shape.hpp>
#include <SFML/Graphics/CircleShape.hpp>
#include <thread>
#include <chrono>
#include <exception>

#define DEBUG

// Utility macros
#define SE_CAST(Type, Value) dynamic_cast<Type>(Value)
#define SE_SLEEP_THIS(ms) std::this_thread::sleep_for(std::chrono::milliseconds(ms))

#ifdef DEBUG
#define SE_LOG(fmt, ...) printf(fmt, ##__VA_ARGS__) 
#else 
#define SE_LOG(fmt, ...) do { } while(0)
#endif

#define SE_LOG_VEC(vec)  printf("%f, %f\n", vec.x, vec.y)

typedef sf::Vector2f	   TVector;
typedef sf::CircleShape    CircleActor;

// Classes can inherit from this interface to forbid copy
struct IForbidCopy
{
	IForbidCopy() = default;
	IForbidCopy(const IForbidCopy&) = delete;
	void operator=(const IForbidCopy&) = delete;
	//virtual ~IForbidCopy() = 0;
};