#ifndef TILE_H
#define TILE_H

#include "../Includes.h"

class Tile
{
protected:
	float scaleX, scaleY;

	sf::RenderWindow* window;
	sf::Sprite sprite;
public:
	Tile(sf::RenderWindow* window, sf::Texture* texture, float x, float y);
	virtual ~Tile();

	const sf::Sprite& getSprite() const;

	void update(const float& dt);
	void render(sf::RenderTarget* target);
};

#endif
