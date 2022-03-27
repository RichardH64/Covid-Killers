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

	int calcScore();
public:
	Enemy(sf::RenderWindow* window, sf::Texture* texture, Level level, float x, float y, EnemyType type);
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

class Boss : public Entity
{
private:
	int score;
	double health, damage;
public:
	Boss(sf::RenderWindow* window, sf::Texture* texture, Level level, float x, float y);
	virtual ~Boss();

	const double& getHealth() const;
	const double& getDamage() const;

	void setHealth(double health);

	void spawnMinion();

	void shrink();
	void enlarge();

	void updateBlastCollision(std::vector<Blast*> blasts, Player* player);
	void updateBorderCollision(Player* player);
	void updateCollision() override;
	void update(const float& dt) override;

	void render(sf::RenderTarget* target) override;
};

#endif

