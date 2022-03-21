#ifndef GSTILESET_H
#define GSTILESET_H

#include "../Includes.h"

class GSTileSet
{
private:
	static const float scaleThird;
	float scaleX, scaleY;
	float totScaleX, totScaleY;

	float colPosXOne, colPosXTwo, colPosXThree;
	float rowPosYOne, rowPosYTwo, rowPosYThree;

	float* otherTilePos;

	sf::Texture* texture;
	sf::RenderWindow* window;

	std::vector<std::vector<sf::Sprite*>> backgroundTileSet;
public:
	GSTileSet(sf::RenderWindow* window, sf::Texture* texture, float start);
	virtual ~GSTileSet();

	float* getPosPtr();
	void setOtherTilePos(float* otp);

	void updateSize(float prevWidth, float prevHeight);
	void update(const float& dt) ;
	void render(sf::RenderTarget* target = NULL) ;
};

#endif