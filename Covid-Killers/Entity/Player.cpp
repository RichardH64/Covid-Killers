#include "Player.h"

Player::Player(sf::RenderWindow* window, sf::Texture* texture, Level level, float x, float y, std::map<std::string, int>* keyBinds, std::map<std::string, bool>* keyBindPressed) : Entity(window, texture, level, x, y)
{
	this->kills = 0;
	this->score = 0;
	this->isSprinting = false;
	this->spacePressed = false;
	this->blastDrain = 2.475;
	this->staminaDrain = .1;

	this->keyBinds = keyBinds;
	this->keyBindPressed = keyBindPressed;

	this->cooldownEnergyMax = sf::seconds(0.70f); this->cooldownEnergy = this->cooldownEnergyMax;
	this->cooldownStaminaMax = sf::seconds(0.10f); this->cooldownStamina = this->cooldownStaminaMax;

	switch (this->level)
	{
	case Level::ONE:
		this->speed = 2.35f; // START
		this->cooldownSB = sf::seconds(0.65f);
		this->cooldownSBMax = sf::seconds(0.65f);

		this->hpMax = 147.65625; this->hp = this->hpMax; // 196.875 - (196.875/4)
		this->energyMax = 126.5625; this->energy = this->energyMax;
		this->staminaMax = 116.015625; this->stamina = this->staminaMax;
		break;
	case Level::TWO:
		this->speed = 2.65f; // 2.35 + .30
		this->cooldownSB = sf::seconds(0.55f);
		this->cooldownSBMax = sf::seconds(0.55f);

		this->hpMax = 198.875; this->hp = this->hpMax; // 262.5 - (262.5/4)
		this->energyMax = 168.75; this->energy = this->energyMax;
		this->staminaMax = 154.6875; this->stamina = this->staminaMax;
		break;
	case Level::THREE:
		this->speed = 2.95f; // 2.65 + .30
		this->cooldownSB = sf::seconds(0.45f);
		this->cooldownSBMax = sf::seconds(0.45f);

		this->hpMax = 262.5; this->hp = this->hpMax; // 350 - (350/4)
		this->energyMax = 225; this->energy = this->energyMax;
		this->staminaMax = 206.25; this->stamina = this->staminaMax;
		break;
	case Level::FOUR:
		this->speed = 3.25f; // 2.95 + .30
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
	this->bars[1] = new Bar(0.f, 35.f, 250.f, 35.f, &this->energy, &this->energyMax, sf::Color::Blue);
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

const bool& Player::getSpacePressed() const
{
	return this->spacePressed;
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

void Player::resetSpacePressed()
{
	this->spacePressed = false;
}

void Player::spawnSingleBlast()
{
}

void Player::spawnExoplosion()
{
}

void Player::updateLevel()
{
	switch (this->level)
	{
	case Level::ONE:
		this->level = Level::TWO;
		this->speed = 2.65f;
		this->cooldownSB = sf::seconds(0.55f);
		this->cooldownSBMax = sf::seconds(0.55f);

		this->hpMax = 198.875; this->hp = this->hpMax; // 262.5 - (262.5/4)
		this->energyMax = 168.75; this->energy = this->energyMax;
		this->staminaMax = 154.6875; this->stamina = this->staminaMax;
		break;
	case Level::TWO:
		this->level = Level::THREE;
		this->speed = 2.95f; // 2.65 + .30
		this->cooldownSB = sf::seconds(0.45f);
		this->cooldownSBMax = sf::seconds(0.45f);

		this->hpMax = 262.5; this->hp = this->hpMax; // 350 - (350/4)
		this->energyMax = 225; this->energy = this->energyMax;
		this->staminaMax = 206.25; this->stamina = this->staminaMax;
		break;
	case Level::THREE:
		this->level = Level::FOUR;
		this->speed = 3.25f;
		this->cooldownSB = sf::seconds(0.35f);
		this->cooldownSBMax = sf::seconds(0.35f);

		this->hpMax = 350; this->hp = this->hpMax;
		this->energyMax = 300; this->energy = this->energyMax;
		this->staminaMax = 275; this->stamina = this->staminaMax;
		break;
	case Level::FOUR:
		this->level = Level::FIVE;
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

void Player::updateMovement()
{
	//Keyboard Input
	if (this->keyBindPressed->at("MOVE_UP"))
	{
		if ((sf::Keyboard::isKeyPressed(sf::Keyboard::RShift) || sf::Keyboard::isKeyPressed(sf::Keyboard::LShift)) && this->stamina > 0.0 && (this->stamina > this->staminaDrain * 2.0 || this->isSprinting)) 
		{ 	
			this->sprite.move(0.f, -(this->speed * 2.5f));
			this->stamina -= this->staminaDrain; 
			this->isSprinting = true; 
		}
		else 
		{ 
			this->sprite.move(0.f, -this->speed);
			this->isSprinting = false; 
		}
	}
	else if (this->keyBindPressed->at("MOVE_DOWN"))
	{
		if ((sf::Keyboard::isKeyPressed(sf::Keyboard::RShift) || sf::Keyboard::isKeyPressed(sf::Keyboard::LShift)) && this->stamina > 0.0 && (this->stamina > this->staminaDrain * 2.0 || this->isSprinting))
		{
			this->sprite.move(0.f, (this->speed * 2.5f));
			this->stamina -= this->staminaDrain;
			this->isSprinting = true;
		}
		else
		{
			this->sprite.move(0.f, this->speed);
			this->isSprinting = false;
		}
	}

	if (this->keyBindPressed->at("MOVE_LEFT"))
	{
		if ((sf::Keyboard::isKeyPressed(sf::Keyboard::RShift) || sf::Keyboard::isKeyPressed(sf::Keyboard::LShift)) && this->stamina > 0.0 && (this->stamina > this->staminaDrain * 2.0 || this->isSprinting))
		{
			this->sprite.move(-(this->speed * 2.5f), 0.f);
			this->stamina -= this->staminaDrain;
			this->isSprinting = true;
		}
		else
		{
			this->sprite.move(-this->speed, 0.f);
			this->isSprinting = false;
		}
	}
	else if (this->keyBindPressed->at("MOVE_RIGHT"))
	{
		if ((sf::Keyboard::isKeyPressed(sf::Keyboard::RShift) || sf::Keyboard::isKeyPressed(sf::Keyboard::LShift)) && this->stamina > 0.0 && (this->stamina > this->staminaDrain * 2.0 || this->isSprinting))
		{
			this->sprite.move((this->speed * 2.5f), 0.f);
			this->stamina -= this->staminaDrain;
			this->isSprinting = true;
		}
		else
		{
			this->sprite.move(this->speed, 0.f);
			this->isSprinting = false;
		}
	}
}

void Player::updateBlast()
{
	if (this->keyBindPressed->at("SINGLE_BLAST") && this->energy > 0)
	{
		if (this->cooldownSB >= this->cooldownSBMax)
		{
			this->spacePressed = true;
			this->energy -= this->blastDrain;
			this->cooldownSB = sf::seconds(0.f);
		}
	}
}

void Player::updateInput()
{
	this->updateMovement();
	this->updateBlast();
}

void Player::updateCollision()
{
	// Left Coll
	if (this->sprite.getGlobalBounds().left < 0.f)
	{
		this->sprite.setPosition(0.f, this->sprite.getGlobalBounds().top);
	}
	// Right Coll
	else if (this->sprite.getGlobalBounds().left + this->sprite.getGlobalBounds().width > this->window->getSize().x)
	{
		this->sprite.setPosition(this->window->getSize().x - this->sprite.getGlobalBounds().width, this->sprite.getGlobalBounds().top);
	}

	// Top Coll
	if (this->sprite.getGlobalBounds().top < 540.f * (static_cast<float>(this->window->getSize().y) / 720.f))
	{
		this->sprite.setPosition(this->sprite.getGlobalBounds().left, 540.f * (static_cast<float>(this->window->getSize().y) / 720.f));
	}
	// Bottom Coll
	else if (this->sprite.getGlobalBounds().top + this->sprite.getGlobalBounds().height >= this->window->getSize().y)
	{
		this->sprite.setPosition(this->sprite.getGlobalBounds().left, this->window->getSize().y - this->sprite.getGlobalBounds().height);
	}
}

void Player::updateBars()
{
	for (int i = 0; i < 3; i++)
	{
		this->bars[i]->update();
	}
}

void Player::updateStats()
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
	if (this->cooldownEnergy >= this->cooldownEnergyMax && !this->spacePressed)
	{
		this->energy += this->blastDrain * 1.0 / 3.0;
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
	if (this->cooldownStamina >= this->cooldownStaminaMax && !this->isSprinting)
	{
		this->stamina += 0.3;
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
	this->updateInput();
	this->updateCollision();
	this->updateBars();
	this->updateStats();
}

void Player::render(sf::RenderTarget* target)
{
	target->draw(this->sprite);

	for (int i = 0; i < 3; i++)
	{
		this->bars[i]->render(target);
	}
}
