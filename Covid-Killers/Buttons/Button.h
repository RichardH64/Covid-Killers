#ifndef BUTTON_H
#define BUTTON_H

#include "../Includes.h"

enum class buttonStates { BTNIDLE = 0, BTNHOVER, BTNPRESSED };

class Button
{
private:

protected:
	sf::Time lastClicked;
	static const sf::Time lastClickedMax;

	float xPos, yPos, width, height, scaleX, scaleY, unfilteredXPos, unfilteredYPos;

	buttonStates buttonState;

	bool boolean, active;
	bool* condition;

	sf::RenderWindow* window;
	sf::Sprite sprite;
public:
	Button(sf::RenderWindow* window, sf::Texture* texture, bool* condition, bool boolean, float xPos, float yPos);
	virtual ~Button();

	void onClick();
	void setActive();
	void setUnactive();
	void reset();
	void updateTimers(const float& dt);
	void update(const float& dt, const sf::Vector2f mosPos);
	void render(sf::RenderTarget* target);
};

#endif

