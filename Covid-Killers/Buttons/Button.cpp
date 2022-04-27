#include "Button.h"

const sf::Time Button::lastClickedMax = sf::seconds(0.25f);

Button::Button(sf::RenderWindow* window, sf::Texture* texture, bool* condition, bool boolean, float xPos, float yPos)
{
	//===PRIMARY===//
	this->window = window;

	this->scaleX = this->window->getView().getSize().x / 1280.f;
	this->scaleY = this->window->getView().getSize().y / 720.f;

	this->lastClicked = this->lastClickedMax;
	//---PRIMARY---//

	//===BASIC DATA===//

	this->condition = condition;
	this->boolean = boolean;
	this->buttonState = buttonStates::BTNIDLE;

	this->width = texture->getSize().x * this->scaleX;
	this->height = texture->getSize().y * this->scaleY;
	this->xPos = this->window->getView().getSize().x / 2.f - this->width / 2.f + xPos * this->scaleX;
	this->yPos = this->window->getView().getSize().y / 2.f - this->height / 2.f + yPos * this->scaleY;
	//---BASIC DATA===//

	//===GRAPHICS===//
	this->sprite = sf::Sprite(*texture);
	this->sprite.setScale(sf::Vector2f(this->scaleX, this->scaleY));
	this->sprite.setPosition(this->xPos, this->yPos);
	//---GRAPHICS---//
}

Button::~Button()
{

}

void Button::onClick()
{
	*this->condition = this->boolean;
}

void Button::setActive()
{
	this->sprite.setScale(sf::Vector2f(this->scaleX + .05f * this->scaleX, this->scaleY + .05f * this->scaleY));
	this->sprite.setPosition(this->xPos - 7.5f * this->scaleX, this->yPos - 7.5f * this->scaleY);

	this->active = true;
}

void Button::setUnactive()
{
	this->sprite.setScale(sf::Vector2f(this->scaleX, this->scaleY));
	this->sprite.setPosition(this->xPos, this->yPos);

	this->active = false;
}

void Button::reset()
{
	this->lastClicked = sf::seconds(0.f);
}

void Button::updateTimers(const float& dt)
{
	this->lastClicked += sf::seconds(dt);

	if (this->lastClicked >= (this->lastClickedMax * 3.f)) { this->lastClicked = this->lastClickedMax; } // Just so it doesn't hold up too much space
}

void Button::update(const float& dt, const sf::Vector2f mosPos)
{
	this->updateTimers(dt);

	if (this->sprite.getGlobalBounds().contains(mosPos))
	{
		this->buttonState = buttonStates::BTNHOVER;
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			if (this->lastClicked >= this->lastClickedMax)
			{
				this->buttonState = buttonStates::BTNPRESSED;
				this->lastClicked = sf::seconds(0.f);
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
		if (this->active) { this->setUnactive(); }
		break;
	case buttonStates::BTNHOVER:
		if (!this->active) { this->setActive(); }
		break;
	case buttonStates::BTNPRESSED:
		this->onClick();
		if (this->active) { this->setUnactive(); }
		this->buttonState = buttonStates::BTNIDLE;
		break;
	}
}

void Button::render(sf::RenderTarget* target)
{
	target->draw(this->sprite);
}