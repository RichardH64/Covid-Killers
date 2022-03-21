#include "GSBorderTileSet.h"

GSBorderTileSet::GSBorderTileSet(sf::RenderWindow* window, sf::Texture* texture, float start)
{
	//===Primary Data===//
	this->window = window;
	this->texture = texture;
	//---Primary Data---//

	//===Create Scales===//
	this->scaleX = this->window->getSize().x / 1280.f;
	this->scaleY = this->window->getSize().y / 720.f;
	//---Create Scales---//

	//===Create Initial Position===//
	this->x = 0.f;
	this->y = 0.f + start;
	//---Create Initial Position---//

	//===Create Sprite===//
	this->sprite = new sf::Sprite(*this->texture);
	this->sprite->setScale(sf::Vector2f(this->scaleX, this->scaleY));
	this->sprite->setPosition(this->x, this->y);
	//---Create Sprite---//
}

GSBorderTileSet::~GSBorderTileSet()
{
	delete this->sprite;
	delete this->texture;
}

void GSBorderTileSet::updateSize(float prevWidth, float prevHeight)
{
	this->scaleY = this->window->getSize().y / 720.f;

	this->y = 90.f * (static_cast<float>(this->window->getSize().y) / 720.f) * 6.f;
	//this->y = this->y * (static_cast<float>(this->window->getSize().y) / prevHeight) + 1.f;

	this->sprite->setScale(sf::Vector2f(this->scaleX, this->scaleY));
	this->sprite->setPosition(this->x, this->y);
}

void GSBorderTileSet::update(const float& dt)
{

}

void GSBorderTileSet::render(sf::RenderTarget* target)
{
	target->draw(*this->sprite);
}