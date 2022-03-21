#ifndef BLAST_H
#define BLAST_H

#include "Entity.h"

class Blast : public Entity
{
private:
	double damage;
	bool hit;
public:
	Blast(sf::RenderWindow* window, sf::Texture* texture, float x, float y, Level level = Level::ONE);
	Blast(sf::RenderWindow* window, sf::Texture* textures[], float x, float y, Level level = Level::ONE);
	virtual ~Blast();

	const double& getDamage() const;
	
	void setHit(bool val);

	void updateCollision() override;
	void update(const float& dt);

	void render(sf::RenderTarget* target);
};
#endif

