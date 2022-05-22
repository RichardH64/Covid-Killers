#include "Physics.h"


float pythag(const sf::Vector2f& vector)
{
	return std::sqrt((vector.x * vector.x) + (vector.y * vector.y));
}

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

sf::Vector2f multiplyVector(const sf::Vector2f& vectorOne, const sf::Vector2f& vectorTwo)
{
	return sf::Vector2f(vectorOne.x * vectorTwo.x, vectorOne.y * vectorTwo.y);
}

sf::Vector2f divideVector(const sf::Vector2f& vectorOne, const sf::Vector2f& vectorTwo)
{
	return sf::Vector2f(vectorOne.x / vectorTwo.x, vectorOne.y / vectorTwo.y);
}

bool satCollision(const sf::FloatRect& rectSp1, const sf::FloatRect& rectSp2, sf::Vector2f* out_mtv)
{
	float proj_x, proj_y, overlap_x, overlap_y;

	// test overlap in x axis
	proj_x = std::max(rectSp1.left + rectSp1.width, rectSp2.left + rectSp2.width) - std::min(rectSp1.left, rectSp2.left);
	if (proj_x < rectSp1.width + rectSp2.width) {
		if (out_mtv) {
			// calculate mtv in x
			overlap_x = rectSp1.width + rectSp2.width - proj_x;
		}
		// test overlap in y axis
		proj_y = std::max(rectSp1.top + rectSp1.height, rectSp2.top + rectSp2.height) - std::min(rectSp1.top, rectSp2.top);
		if (proj_y < rectSp1.height + rectSp2.height) {
			if (out_mtv) {
				// calculate mtv in y
				overlap_y = rectSp1.height + rectSp2.height - proj_y;
				out_mtv->x = out_mtv->y = 0;

				// choose minimun overlap
				if (overlap_x < overlap_y) {
					out_mtv->x = overlap_x * (rectSp1.left < rectSp2.left ? -1 : 1);
				}
				else {
					out_mtv->y = overlap_y * (rectSp1.top < rectSp2.top ? -1 : 1);
				}
			}
			return true;
		}
	}
	return false;
}
