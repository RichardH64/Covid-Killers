#include "Enemy.h"

int Enemy::calcScore()
{
	if (static_cast<float>(this->sprite.getGlobalBounds().top) <= 100.f * (static_cast<float>(this->window->getSize().y) / 720.f))
	{
		return this->score * 3;
	}
	return static_cast<int>(this->score * (1 + this->sprite.getGlobalBounds().top / (540.f * (static_cast<float>(this->window->getSize().y) / 720.f))));
}

Enemy::Enemy(sf::RenderWindow* window, sf::Texture* texture, Level level, float x, float y, EnemyType type) : Entity(window, texture, level, x, y)
{
	this->type = type;
	this->direction.y = 1.f;

	switch (this->type)
	{
	case EnemyType::SARS:
		this->health = 45.0;
		this->damage = 15.0;
		this->velocity = percentRange(50.f, .15f, static_cast<int>(this->level) - 1);
		switch (this->level)
		{
		case Level::ONE:
			this->score = 300; break;
		case Level::TWO:
			this->score = 450; break;
		case Level::THREE:
			this->score = 600; break;
		case Level::FOUR:
		case Level::FIVE:
			this->score = 750; break;
		}
		break;
	case EnemyType::DELTA:
		this->health = 30.0;
		this->damage = 8.75;
		this->velocity = percentRange(90.f, .10f, static_cast<int>(this->level) - 2);
		switch (this->level)
		{
		case Level::TWO:
			this->score = 600; break;
		case Level::THREE:
			this->score = 800; break;
		case Level::FOUR:
		case Level::FIVE:
			this->score = 1000; break;
		default:
			break;
		}
		break;
	case EnemyType::OMI:
		this->health = 15.0;
		this->damage = 7.5;
		this->velocity = percentRange(150.f, .05f, static_cast<int>(this->level) - 3);
		switch (this->level)
		{
		case Level::THREE:
			this->score = 1250; break;
		case Level::FOUR:
		case Level::FIVE:
			this->score = 1500; break;
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
	this->sprite.move(normalize(this->direction) * this->velocity * dt);
}

void Enemy::render(sf::RenderTarget* target)
{
	target->draw(this->sprite);
}

