#include "Enemy.h"

int Enemy::calcScore()
{
	if (static_cast<float>(this->sprite.getGlobalBounds().top) <= 100.f * (static_cast<float>(this->window->getSize().y) / 720.f))
	{
		return this->score * 3;
	}
	return this->score * (1 + this->sprite.getGlobalBounds().top / (540.f * (static_cast<float>(this->window->getSize().y) / 720.f)));
}

Enemy::Enemy(sf::RenderWindow* window, sf::Texture* texture, Level level, float x, float y, EnemyType type) : Entity(window, texture, level, x, y)
{
	this->type = type;

	switch (this->type)
	{
	case EnemyType::SARS:
		this->health = 45.0;
		this->damage = 15.0;
		switch (this->level)
		{
		case Level::ONE:
			this->speed = 0.25f; this->score = 300; break;
		case Level::TWO:
			this->speed = 0.35f; this->score = 450; break;
		case Level::THREE:
			this->speed = 0.45f; this->score = 600; break;
		case Level::FOUR:
		case Level::FIVE:
			this->speed = 0.55f; this->score = 750; break;
		}
		break;
	case EnemyType::DELTA:
		this->health = 30.0;
		this->damage = 8.75;
		switch (this->level)
		{
		case Level::TWO:
			this->speed = 0.75f; this->score = 600; break;
		case Level::THREE:
			this->speed = 0.85f; this->score = 800; break;
		case Level::FOUR:
		case Level::FIVE:
			this->speed = 0.95f; this->score = 1000; break;
		default:
			break;
		}
		break;
	case EnemyType::OMI:
		this->health = 15.0;
		this->damage = 7.5;
		switch (this->level)
		{
		case Level::THREE:
			this->speed = 1.15f; this->score = 1250; break;
		case Level::FOUR:
		case Level::FIVE:
			this->speed = 1.25f; this->score = 1500; break;
		default:
			break;
		}
		break;
	}
}

Enemy::~Enemy()
{

}

const EnemyType& Enemy::getType() const
{
	return this->type;
}

const double& Enemy::getHealth() const
{
	return this->health;
}

const double& Enemy::getDamage() const
{
	return this->damage;
}

void Enemy::setHealth(double health)
{
	this->health = health;
}

void Enemy::updateBlastCollision(std::vector<Blast*> blasts, Player* player)
{
	for (int i = 0; i < blasts.size(); i++)
	{
		if (this->sprite.getGlobalBounds().intersects(blasts[i]->getSprite().getGlobalBounds()))
		{
			if (this->deleted) { break; }
			this->health -= blasts[i]->getDamage();
			blasts[i]->setHit();
			blasts[i]->setDeleted();
			if (this->health <= 0)
			{
				player->addKill();
				player->addScore(this->calcScore());
				this->deleted = true;
				break;
			}
		}
	}
}

void Enemy::updateBorderCollision(Player* player)
{
	if (this->sprite.getGlobalBounds().top + this->height >= 540.f * (static_cast<float>(this->window->getSize().y) / 720.f))
	{
		player->setHealth(player->getHealth() - this->damage);
		this->deleted = true;
	}
}


void Enemy::updateCollision()
{

}

void Enemy::update(const float& dt)
{
	//this->updateCollision();
	this->sprite.move(0.f, this->speed);
}

void Enemy::render(sf::RenderTarget* target)
{
	target->draw(this->sprite);
}

