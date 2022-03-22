#ifndef BUTTON_H
#define BUTTON_H

#include "../Includes.h"

enum class buttonStates { BTNIDLE = 0, BTNHOVER, BTNPRESSED };

class Button
{
private:

protected:
	float xPos, yPos, width, height, scaleX, scaleY, unfilteredXPos, unfilteredYPos;

	buttonStates buttonState;

	bool pressed, hover, boolean;
	bool* condition;

	sf::RenderWindow* window;
	sf::RectangleShape hitBox;
	sf::Sprite sprite;
public:
	Button(sf::RenderWindow* window, sf::Texture* texture, bool* condition, bool boolean, float xPos, float yPos);
	virtual ~Button();

	void onClick();
	void update(const sf::Vector2f mosPos);
	void render(sf::RenderTarget* target);
};

#endif

