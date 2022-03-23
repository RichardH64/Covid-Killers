#ifndef BAR_H
#define BAR_H

#include "GUI.h"

class Bar : public GUI
{
private:
	double* val;
	double* valMax;
	double ratio;

	sf::RectangleShape back, front;
public:
	Bar(float x, float y, float w, float l, double* val, double* valMax, sf::Color color = sf::Color::Red);
	virtual ~Bar();

	void update() override;
	void render(sf::RenderTarget* target) override;
};

#endif

