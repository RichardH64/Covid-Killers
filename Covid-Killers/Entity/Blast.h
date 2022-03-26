#ifndef BLAST_H
#define BLAST_H

#include "Entity.h"

class Blast : public Entity
{
private:
	double damage;
	bool hit;
public:
	Blast(sf::RenderWindow* window, sf::Texture* texture, Level level, float x, float y);
	virtual ~Blast();

	const double& getDamage() const;
	
	void setHit();

	void updateCollision() override;
	void update(const float& dt);

	void render(sf::RenderTarget* target);
};
#endif

