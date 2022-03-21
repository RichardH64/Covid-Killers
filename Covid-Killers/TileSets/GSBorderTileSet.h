#ifndef GSBORDERTILESET_H
#define GSBORDERTILESET_H

#include "../Includes.h"

class GSBorderTileSet
{
private:
	float scaleX, scaleY;
	float x, y;

	sf::Sprite* sprite;
	sf::Texture* texture;
	sf::RenderWindow* window;
public:
	GSBorderTileSet(sf::RenderWindow* window, sf::Texture* texture, float start);
	virtual ~GSBorderTileSet();

	void updateSize(float prevWidth, float prevHeight);
	void update(const float& dt);
	void render(sf::RenderTarget* target = NULL);
};

#endif

