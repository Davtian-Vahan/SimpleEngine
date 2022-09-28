#pragma once

// Include vector class 
#include "SimpleCore.h"

// Static function class, for misc math functions
class SimpleMath
{
public:
	// Returns if there is any collision between the given circles
	static bool circle_collision(const TVector& a, const TVector& b, const float &r1, const float &r2);

	// Returns the distance between the two given vectors
	static float vector_distance(const TVector& vec_1, const TVector&vec_2);

	// Returns given float squared
	static float square(const float &x) { return x * x; }

	// Clamps a value to a given range
	static float clamp(float x, float range_a, float range_b);

	// Return random integer within the given range
	static int rand_range(int min, int max);

	// 
	static sf::Color random_rgb();
};