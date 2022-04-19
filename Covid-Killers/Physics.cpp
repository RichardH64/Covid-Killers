#include "Physics.h"

float percentRange(float number, float percent, unsigned loop)
{
	if (loop < 0) { loop = 0; }
	for (unsigned i = 0; i < loop; i++)
	{
		number += number * percent;
	}
	return number;
}

double percentRange(double number, double percent, unsigned loop)
{
	if (loop < 0) { loop = 0; }
	for (unsigned i = 0; i < loop; i++)
	{
		number += number * percent;
	}
	return number;
}

sf::Vector2f normalize(sf::Vector2f vector)
{
	constexpr auto units_in_last_place = 2;
	auto norm = std::sqrt((vector.x * vector.x) + (vector.y * vector.y));

	// Prevent division by zero
	if (norm <= std::numeric_limits<float>::epsilon() * norm * units_in_last_place || norm < std::numeric_limits<float>::min())
	{
		return sf::Vector2f();
	}
	return vector / norm;
}
