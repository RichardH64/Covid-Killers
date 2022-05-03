#include "Tile.h"

Tile::Tile(sf::RenderWindow* window, sf::Texture* texture, float x, float y)
{
	//===PRIMARY===//
	this->window = window;

	this->scaleX = this->window->getView().getSize().x / 1280.f;
	this->scaleY = this->window->getView().getSize().y / 720.f;
	//---PRIMARY---//

	//===GRAPHICS===//
	this->sprite = sf::Sprite(*texture);
	this->sprite.setScale(sf::Vector2f(this->scaleX, this->scaleY));
	this->sprite.setPosition(sf::Vector2f(x, y));
	//---GRAPHICS---//
}

Tile::~Tile()
{
}

const sf::Sprite& Tile::getSprite() const
{
	return this->sprite;
}

void Tile::update(const float& dt)
{
}

void Tile::render(sf::RenderTarget* target)
{
	target->draw(sprite);
}
