#include "Entity.h"


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

	//===HITBOX===//
	this->hitBox.setFillColor(sf::Color::Transparent);
	this->hitBox.setSize(sf::Vector2f(this->width, this->height));
	this->hitBox.setPosition(this->x, this->y);
	//---HITBOX---//
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

	//===HITBOX===//
	this->hitBox.setFillColor(sf::Color::Transparent);
	this->hitBox.setSize(sf::Vector2f(this->width, this->height));
	this->hitBox.setPosition(this->x, this->y);
	//---HITBOX---//
}

Entity::~Entity()
{

}

const bool& Entity::getDeleted() const
{
	return this->deleted;
}

const sf::RectangleShape& Entity::getHitbox() const
{
	return this->hitBox;
}

void Entity::setDeleted(bool val)
{
	this->deleted = val;
}
