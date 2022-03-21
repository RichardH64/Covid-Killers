#ifndef BAR_H
#define BAR_H

#include "../Includes.h"

class Bar
{
private:
	double* val;
	double* valMax;
	double ratio;
	float x, y, w, l;

	sf::RectangleShape back, front;
public:
	Bar(double* val, double* valMax, float x, float y, float w, float l, sf::Color color = sf::Color::Red);
	virtual ~Bar();

	void update();
	void render(sf::RenderTarget* target);
};

#endif

