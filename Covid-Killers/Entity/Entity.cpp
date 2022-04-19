#include "Entity.h"

sf::Vector2f normalize(sf::Vector2f vector)
{
	constexpr auto units_in_last_place = 2;
	auto norm = std::sqrt((vector.x * vector.x) + (vector.y * vector.y));

	// Prevent division by zero
	if (norm <= std::numeric_limits<float>::epsilon() * norm * units_in_last_place || norm < std::numeric_limits<float>::min())
	{
		return sf::Vector2f();
	}
	return vector / norm;
}

float percentRange(float number, float percent, unsigned loop)
{
	if (loop < 0) { loop = 0; }
	for (int i = 0; i < loop; i++)
	{
		number += number * percent;
	}
	return number;
}

double percentRange(double number, double percent, unsigned loop)
{
	if (loop < 0) { loop = 0; }
	for (int i = 0; i < loop; i++)
	{
		number += number * percent;
	}
	return number;
}

Entity::Entity(sf::RenderWindow* window, sf::Texture* texture, Level level, float x, float y)
{
	//===PRIMARY===//
	this->window = window;
	this->level = level;

	this->scaleX = 1.5f * (this->window->getSize().x / 1280.f);
	this->scaleY = 1.5f * (this->window->getSize().y / 720.f);
	//---PRIMARY---//

	//===BASIC DATA===//
	this->deleted = false;

	this->x = x;
	this->y = y;

	this->width = texture->getSize().x * this->scaleX;
	this->height = texture->getSize().y * this->scaleY;

	if (this->x + this->width > this->window->getSize().x) { this->x = this->window->getSize().x - this->width; }
	//---BASIC DATA===//

	//===GRAPHICS===//
	this->sprite = sf::Sprite(*texture);
	this->sprite.setScale(sf::Vector2f(this->scaleX, this->scaleY));
	this->sprite.setPosition(this->x, this->y);
	//---GRAPHICS---//

	//===Movement===//
	this->velocity = 100.f;
	this->direction = { 0.f, 0.f };
	//---Movement---//
}

Entity::Entity(sf::RenderWindow* window, sf::Texture* texture, float x, float y)
{
	//===PRIMARY===//
	this->window = window;
	this->texture = texture;

	this->scaleX = 1.5f * (this->window->getSize().x / 1280.f);
	this->scaleY = 1.5f * (this->window->getSize().y / 720.f);
	//---PRIMARY---//

	//===BASIC DATA===//
	this->deleted = false;

	this->x = x;
	this->y = y;

	this->width = this->texture->getSize().x * this->scaleX;
	this->height = this->texture->getSize().y * this->scaleY;

	if (this->x + this->width > this->window->getSize().x) { this->x = this->window->getSize().x - this->width; }
	//---BASIC DATA===//

	//===GRAPHICS===//
	this->sprite = sf::Sprite(*this->texture);
	this->sprite.setScale(sf::Vector2f(this->scaleX, this->scaleY));
	this->sprite.setPosition(this->x, this->y);
	//---GRAPHICS---//

	//===Movement===//
	this->velocity = 100.f;
	this->direction = { 0.f, 0.f };
	//---Movement---//
}

Entity::Entity(sf::RenderWindow* window, sf::Texture* textures[], float x, float y)
{
	//===PRIMARY===//
	this->window = window;
	this->texture = textures[0];

	this->scaleX = 1.5f * (this->window->getSize().x / 1280.f);
	this->scaleY = 1.5f * (this->window->getSize().y / 720.f);
	//---PRIMARY---//

	//===BASIC DATA===//
	this->deleted = false;

	this->x = x;
	this->y = y;

	this->width = this->texture->getSize().x * this->scaleX;
	this->height = this->texture->getSize().y * this->scaleY;

	if (this->x + this->width > this->window->getSize().x) { this->x = this->window->getSize().x - this->width; }
	//---BASIC DATA===//

	//===GRAPHICS===//
	this->sprite = sf::Sprite(*this->texture);
	this->sprite.setScale(sf::Vector2f(this->scaleX, this->scaleY));
	this->sprite.setPosition(this->x, this->y);
	//---GRAPHICS---//
}

Entity::~Entity()
{

}

const bool& Entity::getDeleted() const
{
	return this->deleted;
}

const sf::Sprite& Entity::getSprite() const
{
	return this->sprite;
}

void Entity::setDeleted()
{
	this->deleted = true;
}
