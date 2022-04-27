#include "TileMoving.h"

TileMoving::TileMoving(sf::RenderWindow* window, sf::Texture* texture, float x, float y, float velocity, sf::Vector2f direction) : Tile(window, texture, x, y)
{
	this->velocity = velocity;
	this->direction = direction;
	this->relative = nullptr;
}

TileMoving::~TileMoving()
{
}

void TileMoving::setRelative(Tile* relative)
{
	this->relative = relative;
}

void TileMoving::update(const float& dt)
{
	this->sprite.move(normalize(this->direction) * this->velocity * dt);

	float x = this->sprite.getPosition().x;
	float y = this->sprite.getPosition().y;

	if (this->sprite.getPosition().x > this->window->getView().getSize().x)
	{
		if (relative)
		{
			x = this->relative->getSprite().getPosition().x - this->sprite.getGlobalBounds().width + (this->sprite.getGlobalBounds().width * 0.01f * this->scaleX);
		}
		else
		{
			x = 0.f;
		}
	}	
	if (this->sprite.getPosition().y > this->window->getView().getSize().y)
	{
		if (relative)
		{
			y = this->relative->getSprite().getPosition().y - this->sprite.getGlobalBounds().height + (this->sprite.getGlobalBounds().height * 0.01f * this->scaleY);
		}
		else
		{
			y = 0.f;
		}
	}

	this->sprite.setPosition(sf::Vector2f(x, y));
}
