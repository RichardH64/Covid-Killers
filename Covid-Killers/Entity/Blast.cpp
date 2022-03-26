#include "Blast.h"


Blast::Blast(sf::RenderWindow* window, sf::Texture* texture, Level level, float x, float y) : Entity(window, texture, level, x, y)
{
	this->x = x / 2 - this->width / 2;
	this->y = y - this->height;

	this->sprite.setPosition(this->x, this->y);
	
	this->damage = 15.0;

	switch (this->level)
	{
	case Level::ONE:
		this->speed = 1.625;
		break;
	case Level::TWO:
		this->speed = 1.70f; // 1.625 + .075
		break;
	case Level::THREE:
		this->speed = 1.85f; // 1.70 + .30
		break;
	case Level::FOUR:
		this->speed = 2.15f; // 1.85 + .30
		break;
	case Level::FIVE:
		break;
	}
}

Blast::~Blast()
{
}

const double& Blast::getDamage() const
{
	return this->damage;
}

void Blast::setHit()
{
	this->hit = true;
}

void Blast::updateCollision()
{
	if (this->sprite.getGlobalBounds().top + this->height < 0.f)
	{
		this->deleted = true;
	}
}


void Blast::update(const float& dt)
{
	this->updateCollision();

	this->sprite.move(0.f, -this->speed);
}

void Blast::render(sf::RenderTarget* target)
{
	target->draw(this->sprite);
}