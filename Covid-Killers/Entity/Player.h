#ifndef PLAYER_H
#define PLAYER_H

#include "Blast.h"
#include "../GUI/Bar.h"

class Player : public Entity
{
private:
	int kills, score;
	double hp, hpMax;
	double energy, energyMax;
	double stamina, staminaMax;
	double blastDrain, staminaDrain;

	sf::Time cooldownSB, cooldownSBMax; // Cooldown Single Blast
	sf::Time cooldownEnergy, cooldownEnergyMax; // Cooldown Energy
	sf::Time cooldownStamina, cooldownStaminaMax; // Cooldown Stamina

	bool isSprinting, isBlasting, spacePressed;
	Bar* bars[3];

public:
	Player(sf::RenderWindow* window, sf::Texture* texture, float x, float y, Level level = Level::ONE);
	virtual ~Player();

	const bool& getSpacePressed() const;
	const sf::RectangleShape& getHitBox() const;
	const double& getHealth() const;
	const int& getKills() const;
	const int& getScore() const;

	void setHealth(double val);
	void addKill();
	void addScore(int score);

	void resetSpacePressed();

	void spawnSingleBlast();
	void spawnExoplosion();

	void updateLevel();
	void updateTimers(const float& dt);
	void updateMovement();
	void updateBlast();
	void updateInput();
	void updateCollision() override;
	void updateBars();
	void updateStats();
	void update(const float& dt) override;

	void render(sf::RenderTarget* target) override;
};

#endif
