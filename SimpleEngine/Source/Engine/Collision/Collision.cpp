#include "Collision.h"

bool CircleBody::AgainstRect(const RectBody& rect) const
{
	const CircleBody& circle = *this;
	TVector Distance;
	Distance.x = SEMath::Abs(circle.Center.x - rect.Center.x);
	Distance.y = SEMath::Abs(circle.Center.y - rect.Center.y);

	if (Distance.x > (rect.Width / 2 + circle.Radius)) { return false; }
	if (Distance.y > (rect.Height / 2 + circle.Radius)) { return false; }

	if (Distance.x <= (rect.Width / 2)) { return true; }
	if (Distance.y <= (rect.Height / 2)) { return true; }

	float CornerDistSquared =
		SEMath::square(Distance.x - rect.Width / 2) + SEMath::square(Distance.y - rect.Height / 2);

	return (CornerDistSquared <= SEMath::square(circle.Radius));
}

bool  CircleBody::AgainstSelf(const CircleBody& in_circle) const
{
	return SEMath::circle_collision(this->Center, in_circle.Center, this->Radius, in_circle.Radius);
}