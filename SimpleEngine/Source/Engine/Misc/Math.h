#pragma once

// Include vector class 
#include "SimpleCore.h"
#include <cmath>

#define EARTH_GRAVITY 9.807

// Static function class, for misc math functions
namespace SEMath
{
	template <class T>
	inline T Abs(const T& x)
	{
		return std::abs(x);
	}

	// Returns given float squared
	template <class T>
	inline T square(const T& x)
	{
		return x * x;
	}

	// Returns the distance between the two given vectors
	inline float vector_distance(const TVector& vec_1, const TVector& vec_2)
	{
		return std::sqrt(square(vec_2.x - vec_1.x) + square(vec_2.y - vec_1.y));
	}

	// Returns length of the given vector
	inline float vector_length(const TVector& vec)
	{
		return std::sqrt(vec.x * vec.x + vec.y * vec.y);
	}

	// Clamps a value to a given range
	inline float clamp(float x, float range_a, float range_b)
	{
		return std::clamp(x, range_a, range_b);
	}

	// Random T value from a given range
	template <class T>
	T RandRange(T Min, T Max)
	{
		return Min + (T)rand() / ((T)RAND_MAX / (T)(Max - Min));
	}

	// Returns if there is any collision between the given circles
	bool circle_collision(const TVector& a, const TVector& b, const float& r1, const float& r2);

	TVector NormalizeVector(const TVector& InVec);
};