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

	std::map<std::string, int>* keyBinds;
	std::map<std::string, bool>* keyBindPressed;

	bool isSprinting, isBlasting, spacePressed;
	Bar* bars[3];

public:
	Player(sf::RenderWindow* window, sf::Texture* texture, Level level, float x, float y, std::map<std::string, int>* keyBinds, std::map<std::string, bool>* keyBindPressed);
	virtual ~Player();

	const bool& getSpacePressed() const;
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
	void updateMovement(const float& dt);
	void updateBlast();
	void updateInput(const float& dt);
	void updateCollision() override;
	void updateBars();
	void updateStats();
	void update(const float& dt) override;

	void render(sf::RenderTarget* target) override;
};

#endif
