#include "Button.h"


Button::Button(sf::RenderWindow* window, std::string pathToFile, bool* condition, bool boolean, float xPos, float yPos)
{
	//===PRIMARY===//
	this->window = window;
	this->texture.loadFromFile(pathToFile);

	this->scaleX = this->window->getSize().x / 1280.f;
	this->scaleY = this->window->getSize().y / 720.f;
	//---PRIMARY---//

	//===BASIC DATA===//
	this->unfilteredXPos = xPos;
	this->unfilteredYPos = yPos;

	this->condition = condition;
	this->boolean = boolean;
	this->buttonState = buttonStates::BTNIDLE;

	this->width = texture.getSize().x * this->scaleX;
	this->height = texture.getSize().y * this->scaleY;
	this->xPos = this->window->getSize().x / 2.f - this->width / 2.f + (xPos * (this->window->getSize().x /1280.f));
	this->yPos = this->window->getSize().y / 2.f - this->height / 2.f + (yPos * (this->window->getSize().y / 720.f));
	//---BASIC DATA===//

	//===GRAPHICS===//
	this->sprite = sf::Sprite(this->texture);
	this->sprite.setScale(sf::Vector2f(this->scaleX, this->scaleY));
	this->sprite.setPosition(this->xPos, this->yPos);
	//---GRAPHICS---//

	//===HITBOX===//
	this->hitBox.setFillColor(sf::Color::Transparent);
	this->hitBox.setSize(sf::Vector2f(this->width, this->height));
	this->hitBox.setPosition(sf::Vector2f(this->xPos, this->yPos));
	//---HITBOX---//
}

Button::~Button()
{

}

void Button::onClick()
{
	*this->condition = this->boolean;
	std::cout << "Hi\n";
}

void Button::update(const sf::Vector2f mosPos)
{
	if (this->hitBox.getGlobalBounds().contains(mosPos))
	{
		this->buttonState = buttonStates::BTNHOVER;
		// Will Check if button is pressed or released
		switch (pressed)
		{
		case false:
		{
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
			{
				this->pressed = true;
				// Trigger button pressed sound
			}
			break;
		}
		case true:
		{
			if (!sf::Mouse::isButtonPressed(sf::Mouse::Left))
			{
				this->pressed = false;
				this->buttonState = buttonStates::BTNPRESSED;
			}
			break;
		}
		}
	}
	else
	{
		this->buttonState = buttonStates::BTNIDLE;
	}

	switch (this->buttonState)
	{
	case buttonStates::BTNIDLE:
		this->hover = false;
		this->pressed = false;
		break;
	case buttonStates::BTNHOVER:
		this->hover = true;
		break;
	case buttonStates::BTNPRESSED:
		this->onClick();
		this->buttonState = buttonStates::BTNHOVER;
		break;
	default:
		break;
	}
}

void Button::render(sf::RenderTarget* target)
{
	target->draw(this->sprite);
	target->draw(this->hitBox);
}