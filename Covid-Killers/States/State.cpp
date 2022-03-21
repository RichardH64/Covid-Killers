#include "State.h"

//===ABSTRACT STATE===//


State::State(sf::RenderWindow* window, sf::Vector2i* mosPosWindow, sf::Vector2f* mosPosView)
{
	this->window = window;
	this->quit = false;
	this->mosPosWindow = mosPosWindow;
	this->mosPosView = mosPosView;

	this->prevWidth = static_cast<float>(this->window->getSize().x);
	this->prevHeight = static_cast<float>(this->window->getSize().y);
	this->fontConnectionII.loadFromFile("Assets/Fonts/ConnectionIi-2wj8.otf");
}

State::State(sf::RenderWindow* window, sf::Vector2i* mosPosWindow, sf::Vector2f* mosPosView, std::map<std::string, bool*> booleans)
{
	this->window = window;
	this->quit = false;
	this->mosPosWindow = mosPosWindow;
	this->mosPosView = mosPosView;

	this->prevWidth = static_cast<float>(this->window->getSize().x);
	this->prevHeight = static_cast<float>(this->window->getSize().y);
	this->fontConnectionII.loadFromFile("Assets/Fonts/ConnectionIi-2wj8.otf");

	this->booleans = booleans;
}

State::~State()
{
}

const bool& State::getQuit() const
{
	return this->quit;
}

/*
void State::checkForQuit()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
	{
		this->quit = true;
	}
}
*/

