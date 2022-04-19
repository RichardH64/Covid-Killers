#ifndef TILEMOVING_H
#define TILEMOVING_H

#include "Tile.h"
#include "../Physics.h"

class TileMoving : public Tile
{
private:
	Tile* relative;

	float velocity;
	sf::Vector2f direction;
public:
	TileMoving(sf::RenderWindow* window, sf::Texture* texture, float x, float y, float velocity, sf::Vector2f direction);
	virtual ~TileMoving();

	void setRelative(Tile* relative);

	void update(const float& dt);
};

#endif

