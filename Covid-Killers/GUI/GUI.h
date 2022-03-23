#ifndef GUI_H
#define GUI_H

#include "../Includes.h"

class GUI
{
protected:
	float x, y, w, l;
public:
	GUI(float x, float y, float w, float l);
	virtual ~GUI();

	virtual void update() = 0;
	virtual void render(sf::RenderTarget* target) = 0;
};

#endif

