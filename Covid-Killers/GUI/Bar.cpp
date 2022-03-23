#include "Bar.h"

Bar::Bar(float x, float y, float w, float l, double* val, double* valMax, sf::Color color) : GUI(x, y, w, l)
{
	this->val = val;
	this->valMax = valMax;
	this->ratio = *this->val / *this->valMax;

	this->back.setSize(sf::Vector2f(w, l));
	this->back.setPosition(sf::Vector2f(x, y));
	this->back.setFillColor(sf::Color(25, 25, 25, 200));

	this->front.setSize(sf::Vector2f(w * static_cast<float>(this->ratio), l));
	this->front.setPosition(sf::Vector2f(x, y));
	this->front.setFillColor(color);
}

Bar::~Bar()
{
}

void Bar::update()
{
	this->ratio = *this->val / *this->valMax;
	this->front.setSize(sf::Vector2f(this->w * static_cast<float>(this->ratio), this->front.getSize().y));
}

void Bar::render(sf::RenderTarget* target)
{
	target->draw(this->back);
	target->draw(this->front);
}
