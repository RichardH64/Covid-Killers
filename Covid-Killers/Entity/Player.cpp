#include "Player.h"

Player::Player(sf::RenderWindow* window, sf::Texture* texture, Level level, float x, float y, std::map<std::string, int>* keyBinds, std::map<std::string, bool>* keyBindPressed) : Entity(window, texture, level, x, y)
{
	this->kills = 0;
	this->score = 0;

	this->spawnSingleBlast = false;

	this->keyBinds = keyBinds;
	this->keyBindPressed = keyBindPressed;

	this->cooldownEnergyMax = sf::seconds(0.70f); this->cooldownEnergy = this->cooldownEnergyMax;
	this->cooldownStaminaMax = sf::seconds(0.10f); this->cooldownStamina = this->cooldownStaminaMax;
	
	this->velocity = percentRange(300.f, .10f, static_cast<int>(this->level) - 1);

	switch (this->level)
	{
	case Level::ONE:
		this->cooldownSB = sf::seconds(0.65f);
		this->cooldownSBMax = sf::seconds(0.65f);

		this->hpMax = 147.65625; this->hp = this->hpMax; // 196.875 - (196.875/4)
		this->energyMax = 126.5625; this->energy = this->energyMax;
		this->staminaMax = 116.015625; this->stamina = this->staminaMax;
		break;
	case Level::TWO:
		this->cooldownSB = sf::seconds(0.55f);
		this->cooldownSBMax = sf::seconds(0.55f);

		this->hpMax = 198.875; this->hp = this->hpMax; // 262.5 - (262.5/4)
		this->energyMax = 168.75; this->energy = this->energyMax;
		this->staminaMax = 154.6875; this->stamina = this->staminaMax;
		break;
	case Level::THREE:
		this->cooldownSB = sf::seconds(0.45f);
		this->cooldownSBMax = sf::seconds(0.45f);

		this->hpMax = 262.5; this->hp = this->hpMax; // 350 - (350/4)
		this->energyMax = 225; this->energy = this->energyMax;
		this->staminaMax = 206.25; this->stamina = this->staminaMax;
		break;
	case Level::FOUR:
		this->cooldownSB = sf::seconds(0.35f);
		this->cooldownSBMax = sf::seconds(0.35f);

		this->hpMax = 350; this->hp = this->hpMax;
		this->energyMax = 300; this->energy = this->energyMax;
		this->staminaMax = 275; this->stamina = this->staminaMax;
		break;
	case Level::FIVE:
		break;
	}

	this->bars[0] = new Bar(0.f, 0.f, 300.f, 35.f, &this->hp, &this->hpMax, sf::Color::Red);
	this->bars[1] = new Bar(0.f, 35.f, 250.f, 35.f, &this->energy, &this->energyMax, sf::Color(0, 97, 255));
	this->bars[2] = new Bar(0.f, 70.f, 200.f, 35.f, &this->stamina, &this->staminaMax, sf::Color::Green);
}

Player::~Player()
{
	for (int i = 0; i < 3; i++)
	{
		delete this->bars[i];
		this->bars[i] = nullptr;
	}
}

const bool& Player::getSpawnSingleBlast() const
{
	return this->spawnSingleBlast;
}

const bool& Player::getSpawnMultiBlast() const
{
	return this->spawnMultiBlast;
}

const double& Player::getHealth() const
{
	return this->hp;
}

const int& Player::getKills() const
{
	return this->kills;
}

const int& Player::getScore() const
{
	return this->score;
}

void Player::setHealth(double val)
{
	this->hp = val;
}

void Player::addKill()
{
	this->kills += 1;
}

void Player::addScore(int score)
{
	this->score += score;
}

void Player::resetSpawnSingleBlast()
{
	this->spawnSingleBlast = false;
}

void Player::resetSpawnMultiBlast()
{
	this->spawnMultiBlast = false;
}

void Player::updateLevel()
{
	this->level = static_cast<Level>((static_cast<int>(this->level) + 1));
	this->velocity = percentRange(300.f, .10f, static_cast<int>(this->level) - 1);

	switch (this->level)
	{
	case Level::ONE:
		this->cooldownSB = sf::seconds(0.55f);
		this->cooldownSBMax = sf::seconds(0.55f);

		this->hpMax = 198.875; this->hp = this->hpMax; // 262.5 - (262.5/4)
		this->energyMax = 168.75; this->energy = this->energyMax;
		this->staminaMax = 154.6875; this->stamina = this->staminaMax;
		break;
	case Level::TWO:
		this->cooldownSB = sf::seconds(0.45f);
		this->cooldownSBMax = sf::seconds(0.45f);

		this->hpMax = 262.5; this->hp = this->hpMax; // 350 - (350/4)
		this->energyMax = 225; this->energy = this->energyMax;
		this->staminaMax = 206.25; this->stamina = this->staminaMax;
		break;
	case Level::THREE:
		this->cooldownSB = sf::seconds(0.35f);
		this->cooldownSBMax = sf::seconds(0.35f);

		this->hpMax = 350; this->hp = this->hpMax;
		this->energyMax = 300; this->energy = this->energyMax;
		this->staminaMax = 275; this->stamina = this->staminaMax;
		break;
	case Level::FOUR:
		break;
	case Level::FIVE:
		break;
	}
}

void Player::updateTimers(const float& dt)
{
	this->cooldownSB += sf::seconds(dt);
	this->cooldownEnergy += sf::seconds(dt);
	this->cooldownStamina += sf::seconds(dt);
}

void Player::updateMovement(const float& dt)
{
	//Keyboard Input
	if ((this->keyBindPressed->at("MOVE_LEFT") && this->keyBindPressed->at("MOVE_RIGHT")) || (!this->keyBindPressed->at("MOVE_LEFT") && !this->keyBindPressed->at("MOVE_RIGHT")))
	{
		this->direction.x = 0.f;
	}
	else if (this->keyBindPressed->at("MOVE_LEFT"))
	{
		this->direction.x = -1.f;
	}
	else if (this->keyBindPressed->at("MOVE_RIGHT"))
	{
		this->direction.x = 1.f;
	}

	if ((this->keyBindPressed->at("MOVE_UP") && this->keyBindPressed->at("MOVE_DOWN")) || (!this->keyBindPressed->at("MOVE_UP") && !this->keyBindPressed->at("MOVE_DOWN")))
	{
		this->direction.y = 0.f;
	}
	else if (this->keyBindPressed->at("MOVE_UP"))
	{
		this->direction.y = -1.f;
	}
	else if (this->keyBindPressed->at("MOVE_DOWN"))
	{
		this->direction.y = 1.f;
	}

	if (this->keyBindPressed->at("SPRINT"))
	{
		// Stamina Drain = (11 - Level) percent of Max Stamina multiplied by the change in time
		this->stamina -= this->staminaMax * (.11 - static_cast<double>(this->level)/100.0) * static_cast<double>(dt);
		this->sprite.move(normalize(this->direction) * percentRange(this->velocity, .75f, 1) * dt);
	}
	else
	{
		this->sprite.move(normalize(this->direction) * this->velocity * dt);
	}

}

void Player::updateBlast(const float& dt)
{
	if (this->keyBindPressed->at("SINGLE_BLAST") && this->energy > 0)
	{
		if (this->cooldownSB >= this->cooldownSBMax)
		{
			// Energy Drain = (110 - Level) percent of Max Energy multiplied by the change in time
			this->energy -= this->energyMax * (1.1 - static_cast<double>(this->level) / 10.0) * static_cast<double>(dt);
			this->cooldownSB = sf::seconds(0.f);
			this->spawnSingleBlast = true;
		}
	}	
	
	if (this->keyBindPressed->at("MULTI_BLAST") && this->energy > 0)
	{
		if (this->cooldownSB >= this->cooldownSBMax)
		{
			// Energy Drain = (110 - Level) percent of Max Energy multiplied by the change in time
			this->energy -= this->energyMax * (1.1 - static_cast<double>(this->level) / 10.0) * static_cast<double>(dt) * 3.0;
			this->cooldownSB = sf::seconds(0.f);
			this->spawnMultiBlast = true;
		}
	}
}

void Player::updateInput(const float& dt)
{
	this->updateMovement(dt);
	this->updateBlast(dt);
}

void Player::updateCollision()
{
	// Left Collision
	if (this->sprite.getGlobalBounds().left < 0.f)
	{
		this->sprite.setPosition(0.f, this->sprite.getGlobalBounds().top);
	}
	// Right Collision
	else if (this->sprite.getGlobalBounds().left + this->sprite.getGlobalBounds().width > this->window->getView().getSize().x)
	{
		this->sprite.setPosition(this->window->getView().getSize().x - this->sprite.getGlobalBounds().width, this->sprite.getGlobalBounds().top);
	}

	// Top Collision
	if (this->sprite.getGlobalBounds().top <  540.f * this->window->getView().getSize().y / 720.f)
	{
		this->sprite.setPosition(this->sprite.getGlobalBounds().left, 540.f * this->window->getView().getSize().y / 720.f);
	}
	// Bottom Collision
	else if (this->sprite.getGlobalBounds().top + this->sprite.getGlobalBounds().height >= this->window->getView().getSize().y)
	{
		this->sprite.setPosition(this->sprite.getGlobalBounds().left, this->window->getView().getSize().y - this->sprite.getGlobalBounds().height);
	}
}

void Player::updateBars()
{
	for (int i = 0; i < 3; i++)
	{
		this->bars[i]->update();
	}
}

void Player::updateStats(const float& dt)
{
	//===HEALTH===//
	if (this->hp < 0.0)
	{
		this->hp = 0.0;
	}
	if (this->hp > this->hpMax)
	{
		this->hp = this->hpMax;
	}
	//===HEALTH===//

	//===ENERGY===//
	if (this->energy < 0.0)
	{
		this->energy = 0.0;
	}
	if (this->cooldownEnergy >= this->cooldownEnergyMax && !this->keyBindPressed->at("SINGLE_BLAST"))
	{
		this->energy += this->energyMax * (1.1 + static_cast<double>(this->level) / 10.0) * static_cast<double>(dt);
		this->cooldownEnergy = sf::seconds(0.f);
	}
	if (this->energy > this->energyMax)
	{
		this->energy = this->energyMax;
	}
	//===ENERGY===//

	//===STAMINA===//
	if (this->stamina < 0.0)
	{
		this->stamina = 0.0;
	}
	if (this->cooldownStamina >= this->cooldownStaminaMax && !this->keyBindPressed->at("SPRINT"))
	{
		this->stamina += this->staminaMax * (.50 + static_cast<double>(this->level) / 100.0) * static_cast<double>(dt);
		this->cooldownStamina = sf::seconds(0.f);

	}
	if (this->stamina > this->staminaMax)
	{
		this->stamina = this->staminaMax;
	}
	//===STAMINA===//
}

void Player::update(const float& dt)
{
	// Movement / Windows Collision
	this->updateTimers(dt);
	this->updateInput(dt);
	this->updateCollision();
	this->updateBars();
	this->updateStats(dt);
}

void Player::render(sf::RenderTarget* target)
{
	target->draw(this->sprite);

	for (int i = 0; i < 3; i++)
	{
		this->bars[i]->render(target);
	}
}
