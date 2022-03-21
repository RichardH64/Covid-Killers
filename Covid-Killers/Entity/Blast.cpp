#include "Blast.h"

Blast::Blast(sf::RenderWindow* window, sf::Texture* texture, float x, float y, Level level) : Entity(window, texture, x, y)
{	
	this->level = level;

	this->x = x / 2 - this->width / 2;
	this->y = y - this->height;

	this->sprite.setPosition(this->x, this->y);
	this->hitBox.setPosition(this->x, this->y);

	switch (this->level)
	{
	case Level::ONE:
		this->damage = 6.328125; // 8.4375 - (8.4375/4)
		this->speed = 1.625;
		break;
	case Level::TWO:
		this->damage = 8.4375; // 11.25 - (11.25/4)
		this->speed = 1.70f; // 1.625 + .075
		break;
	case Level::THREE:
		this->damage = 11.25; // 15 - (15/4)
		this->speed = 1.85f; // 1.70 + .30
		break;
	case Level::FOUR:
		this->damage = 15.0;
		this->speed = 2.15f; // 1.85 + .30
		break;
	case Level::FIVE:
		break;
	}
}

Blast::Blast(sf::RenderWindow* window, sf::Texture* textures[], float x, float y, Level level) : Entity(window, textures, x, y)
{
	this->level = level;
	this->hit = true;

	this->x = x / 2 - this->width / 2;
	this->y = y - this->height;

	this->sprite.setPosition(this->x, this->y);
	this->hitBox.setPosition(this->x, this->y);

	switch (this->level)
	{
	case Level::TWO:
		break;
	case Level::THREE:
		break;
	case Level::FOUR:
		this->damage = 15.0;
		this->speed = 2.15f;
		break;
	case Level::FIVE:
		break;
	case Level::ONE:
	default:
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

void Blast::setHit(bool val)
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

	this->hitBox.move(0.f, -this->speed);
	this->sprite.move(0.f, -this->speed);
}

void Blast::render(sf::RenderTarget* target)
{
	target->draw(this->sprite);
	target->draw(this->hitBox);
}