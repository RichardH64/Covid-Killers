#include "Blast.h"


Blast::Blast(sf::RenderWindow* window, sf::Texture* texture, Level level, float x, float y) : Entity(window, texture, level, x, y)
{
	this->x = x / 2 - this->width / 2;
	this->y = y - this->height;

	this->sprite.setPosition(this->x, this->y);
	
	this->damage = 15.0;

	this->direction.y = -1.f;
	this->velocity = percentRange(200.f, .20f, static_cast<int>(this->level) - 1);
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

	this->sprite.move(normalize(this->direction) * this->velocity * dt);
}

void Blast::render(sf::RenderTarget* target)
{
	target->draw(this->sprite);
}