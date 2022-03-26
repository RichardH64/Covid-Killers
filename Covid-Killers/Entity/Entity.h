#ifndef ENTITY_H
#define ENTITY_H

#include "../Includes.h"

enum class Level { ONE = 1, TWO, THREE, FOUR, FIVE };

class Entity
{
protected:
	Level level;
	float x, y, width, height, scaleX, scaleY;
	float speed;
	bool deleted;

	sf::RenderWindow* window;
	sf::Texture* texture;
	sf::Sprite sprite;
public:
	Entity(sf::RenderWindow* window, sf::Texture* texture, Level level, float x, float y);
	Entity(sf::RenderWindow* window, sf::Texture* texture, float x, float y);
	Entity(sf::RenderWindow* window, sf::Texture* textures[], float x, float y);
	virtual ~Entity();

	const bool& getDeleted() const;
	const sf::Sprite& getSprite() const;

	void setDeleted();

	virtual void updateCollision() = 0;
	virtual void update(const float& dt) = 0;

	virtual void render(sf::RenderTarget* target) = 0;
};

#endif
