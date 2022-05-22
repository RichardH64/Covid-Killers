#ifndef PHYSICS_H
#define PHYSICS_H


#include "Includes.h"
#include <limits>
#include <algorithm>


template <typename T>
const T roundTo(T number, int place);

float pythag(const sf::Vector2f& vector);

float percentRange(float number, float percent, unsigned loop = 1);
double percentRange(double number, double percent, unsigned loop = 1);

sf::Vector2f normalize(sf::Vector2f vector);

sf::Vector2f multiplyVector(const sf::Vector2f& vectorOne, const sf::Vector2f& vectorTwo);
sf::Vector2f divideVector(const sf::Vector2f& vectorOne, const sf::Vector2f& vectorTwo);

template<typename T>
inline const T roundTo(T number, int place)
{
	return static_cast<T>(std::round(number * std::pow(10, place)) / std::pow(10, place));
}

// SAT COLLISION TAKEN FROM https://github.com/pabratte/SAT_SFML/blob/master/main.cpp
/**
 * Test if two sprites overlap using Separating Axis Theorem (http://www.dyn4j.org/2010/01/sat/),
 * optionally can receive a pointer to a sf::Vector2f to output the MTV (Minimum Translation Vector)
 * to correct the first sprite position
 * \param sp1 First sprite
 * \param sp2 Second sprite
 * \param out_mtv Pointer to a sf::Vector2f in wich to receive the MTV
 * \return true if overlapping exist, false otherwise
 */
bool satCollision(const sf::FloatRect& rectSp1, const sf::FloatRect& rectSp2, sf::Vector2f* out_mtv = nullptr);


#endif
