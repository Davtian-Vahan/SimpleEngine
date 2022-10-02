#include "MiscMathLibrary.h"
#include <cmath>
#include <algorithm>

bool SimpleMath::circle_collision(const TVector& a, const TVector& b, const float& r1, const float& r2)
{
	// (x2-x1)^2 + (y2-y1)^2 <= (r1+r2)^2
	float part1 = square(b.x - a.x) + square(b.y - a.y);
	float part2 = square(r1 + r2);
	return part1 <= part2;
}

float SimpleMath::vector_distance(const TVector& vec_1, const TVector& vec_2)
{
	return std::sqrt(square(vec_2.x - vec_1.x) + square(vec_2.y - vec_1.y));
}

float SimpleMath::clamp(float x, float range_a, float range_b)
{
	return std::clamp(x, range_a, range_b);
}

int SimpleMath::rand_range(int min, int max)
{
	return min + rand() % max;
}

sf::Color SimpleMath::random_rgb()
{
	int r = rand_range(0, 128);
	int g = rand_range(0, 128);
	int b = rand_range(0, 128);
	return sf::Color(r, g, b);
}
