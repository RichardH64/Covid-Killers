#include "Entity.h"

Entity::Entity(sf::RenderWindow* window, sf::Texture* texture, Level level, float x, float y)
{
	//===PRIMARY===//
	this->window = window;
	this->level = level;
	//---PRIMARY---//

	//===BASIC DATA===//
	this->deleted = false;
	this->width = texture->getSize().x * 1.5f;
	this->height = texture->getSize().y * 1.5f;
	if (x + this->width > this->window->getSize().x) { x = this->window->getSize().x - this->width; }
	//---BASIC DATA===//

	//===GRAPHICS===//
	this->sprite = sf::Sprite(*texture);
	this->sprite.setScale(sf::Vector2f(1.5f, 1.5f));
	this->sprite.setPosition(sf::Vector2f(x, y));
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
	//---PRIMARY---//

	//===BASIC DATA===//
	this->deleted = false;
	this->width = this->texture->getSize().x * 1.5f;
	this->height = this->texture->getSize().y * 1.5f;
	if (x + this->width > this->window->getSize().x) { x = this->window->getSize().x - this->width; }
	//---BASIC DATA===//

	//===GRAPHICS===//
	this->sprite = sf::Sprite(*this->texture);
	this->sprite.setScale(sf::Vector2f(1.5f, 1.5f));
	this->sprite.setPosition(sf::Vector2f(x, y));
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
	//---PRIMARY---//

	//===BASIC DATA===//
	this->deleted = false;
	this->width = texture->getSize().x * 1.5f;
	this->height = texture->getSize().y * 1.5f;
	if (x + this->width > this->window->getSize().x) { x = this->window->getSize().x - this->width; }
	//---BASIC DATA===//

	//===GRAPHICS===//
	this->sprite = sf::Sprite(*this->texture);
	this->sprite.setScale(sf::Vector2f(1.5f, 1.5f));
	this->sprite.setPosition(sf::Vector2f(x, y));
	//---GRAPHICS---//

	//===Movement===//
	this->velocity = 100.f;
	this->direction = { 0.f, 0.f };
	//---Movement---//
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
