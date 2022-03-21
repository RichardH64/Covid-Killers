#ifndef ENEMY_H
#define ENEMY_H

#include "Player.h"

enum class EnemyType { DEFAULT = 0, SARS, DELTA, OMI };

class Enemy : public Entity
{
private:
	int score;
	EnemyType type;
	double health, damage;
public:
	Enemy(sf::RenderWindow* window, sf::Texture* textures[], float x, float y, EnemyType type = EnemyType::DEFAULT, Level level = Level::ONE);
	virtual ~Enemy();

	const EnemyType& getType() const;
	const double& getHealth() const;
	const double& getDamage() const;

	void setHealth(double health);

	void updateBlastCollision(std::vector<Blast*> blasts, Player* player);
	void updateBorderCollision(Player* player);
	void updateCollision() override;
	void update(const float& dt) override;

	void render(sf::RenderTarget* target) override;
};

#endif

