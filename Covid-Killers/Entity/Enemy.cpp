#include "Enemy.h"

Enemy::Enemy(sf::RenderWindow* window, sf::Texture* textures[], float x, float y, EnemyType type, Level level) : Entity(window, textures, x, y)
{
	this->level = level;

	if (type == EnemyType::DEFAULT)
	{
		switch (rand() % 3 + 1)
		{
		case 1:
			this->type = EnemyType::SARS;
			break;
		case 2:
			this->type = EnemyType::DELTA;
			break;
		case 3:
			this->type = EnemyType::OMI;
			break;
		default:
			this->type = EnemyType::SARS;
			break;
		}
	}
	else
	{
		this->type = type;
	}

	switch (this->type)
	{
	case EnemyType::SARS:
		this->texture = textures[0];

		this->sprite = sf::Sprite(*this->texture);
		this->sprite.setScale(sf::Vector2f(this->scaleX, this->scaleY));
		this->sprite.setPosition(this->x, this->y);

		switch (this->level)
		{
		case Level::ONE:
			this->health = 13.333; // 20 - (20/3)
			this->damage = 6.328125; // 8.4375 - (8.4375/4)
			this->speed = 0.275f; // START
			this->score = rand() % 249 + 170; // Min 170 Max 418
			break;
		case Level::TWO:
			this->health = 20; // 30 - (30/3)
			this->damage = 8.4375; // 11.25 - (11.25/4)
			this->speed = 0.30f; // .275 + .075
			this->score = rand() % 209 + 350; // Min 350 Max 558
			break;
		case Level::THREE:
			this->health = 30; // 45 - (45/3)
			this->damage = 11.25; // 15 - (15/4)
			this->speed = 0.45f; // .30 +  .15
			this->score = rand() % 339 + 420; // Min 420 Max 758
			break;
		case Level::FOUR:
			this->health = 45.0; // START
			this->damage = 15.0; // START
			this->speed = 0.75f; // .45 + .30
			this->score = rand() % 319 + 630; // Min 630 Max 948
			break;
		case Level::FIVE:
			break;
		}
		break;
	case EnemyType::DELTA:
		this->texture = textures[1];

		this->sprite = sf::Sprite(*this->texture);
		this->sprite.setScale(sf::Vector2f(this->scaleX, this->scaleY));
		this->sprite.setPosition(this->x, this->y);

		switch (this->level)
		{
		case Level::TWO:
			this->health = 13.333; // 20 - (20/3)
			this->damage = 4.921875; // 6.5625 - (6.5625/4)
			this->speed = 0.70f;
			this->score = rand() % 237 + 387; // Min 387 Max 623
			break;
		case Level::THREE:
			this->health = 20.0; // 30 - (30/3)
			this->damage = 6.5625; // 8.75 - (8.75/4)
			this->speed = 0.85f; // .70 + .15
			this->score = rand() % 497 + 537; // Min 537 Max 1033
			break;
		case Level::FOUR:
			this->health = 30.0; // START
			this->damage = 8.75; // START
			this->speed = 1.15f; // .85 + .30
			this->score = rand() % 557 + 897; // Min 897 Max 1453
			break;
		case Level::FIVE:
			break;
		default:
			break;
		}
		break;
	case EnemyType::OMI:
		this->texture = textures[2];

		this->sprite = sf::Sprite(*this->texture);
		this->sprite.setScale(sf::Vector2f(this->scaleX, this->scaleY));
		this->sprite.setPosition(this->x, this->y);

		switch (this->level)
		{
		case Level::THREE:
			this->health = 10; // 15 - (15/3)
			this->damage = 5.625; // 7.5 - (7.5/4)
			this->speed = 1.25f; // 1.25
			this->score = rand() % 613 + 1532; // Min 1532 Max 2144
			break;
		case Level::FOUR:
			this->health = 15.0;
			this->damage = 7.5; // START
			this->speed = 1.55f; // 1.25 + .30
			this->score = rand() % 753 + 1812; // Min 1812 Max 2564
			break;
		case Level::FIVE:
			break;
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
		if (this->hitBox.getGlobalBounds().intersects(blasts[i]->getHitbox().getGlobalBounds()))
		{
			if (this->deleted) { break; }
			this->health -= blasts[i]->getDamage();
			blasts[i]->setHit(true);
			blasts[i]->setDeleted(true);
			if (this->health <= 0)
			{
				player->addKill();
				player->addScore(this->score);
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
	this->hitBox.move(0.f, this->speed);
	this->sprite.move(0.f, this->speed);
}

void Enemy::render(sf::RenderTarget* target)
{
	target->draw(this->sprite);
	target->draw(this->hitBox);
}

