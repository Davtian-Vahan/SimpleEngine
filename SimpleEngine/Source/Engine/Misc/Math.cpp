#include "Math.h"
#include <algorithm>

TVector SEMath::NormalizeVector(const TVector& InVec)
{
	TVector newVec = InVec;
	newVec.x /= vector_length(InVec);
	newVec.y /= vector_length(InVec);
	return newVec;
}

bool SEMath::circle_collision(const TVector& a, const TVector& b, const float& r1, const float& r2)
{
	// (x2-x1)^2 + (y2-y1)^2 <= (r1+r2)^2
	float part1 = square(b.x - a.x) + square(b.y - a.y);
	float part2 = square(r1 + r2);
	return part1 <= part2;
}