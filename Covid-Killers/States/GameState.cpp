#include "GameState.h"

//===INITIALIZE FUNCTIONS===//
void GameState::initTextures()
{
	//===Init Background Texture===//
	this->textureBackground = new sf::Texture;
	this->textureBackground->loadFromFile("Assets/Tiles/Background.png");
	//---Init Background Texture---//

	//===Init Border Texture===//
	this->textureBorder = new sf::Texture;
	this->textureBorder->loadFromFile("Assets/GameState/Border.png");
	//---Init Border Texture---//

	//===Init Player Texture===//
	this->texturePlayer = new sf::Texture;
	this->texturePlayer->loadFromFile("Assets/Entity/Player/Cell.png");
	//---Init Player Texture---//
	
	//===Init Boss Texture===//
	this->textureBoss = new sf::Texture;
	this->textureBoss->loadFromFile("Assets/Entity/Enemy/Sigma.png");
	//---Init Boss Texture---//
	
	//===Init Blast Texture===//
	this->textureBlast.insert({ BlastType::SINGLE, new sf::Texture });

	this->textureBlast[BlastType::SINGLE]->loadFromFile("Assets/Entity/Blast/Single.png");
	//---Init Blast Texture---//

	//===Init Strain Texture===//
	this->textureEnemy.insert({ EnemyType::SARS, new sf::Texture });
	this->textureEnemy.insert({ EnemyType::DELTA, new sf::Texture });
	this->textureEnemy.insert({ EnemyType::OMI, new sf::Texture });

	this->textureEnemy[EnemyType::SARS]->loadFromFile("Assets/Entity/Enemy/Sars.png");
	this->textureEnemy[EnemyType::DELTA]->loadFromFile("Assets/Entity/Enemy/Delta.png");
	this->textureEnemy[EnemyType::OMI]->loadFromFile("Assets/Entity/Enemy/Omi.png");
	//---Init Strain Texture---//

	//===Init Level Texture===//
	this->textureLevel.insert({Level::ONE, new sf::Texture});
	this->textureLevel.insert({Level::TWO, new sf::Texture});
	this->textureLevel.insert({Level::THREE, new sf::Texture});
	this->textureLevel.insert({Level::FOUR, new sf::Texture});
	this->textureLevel.insert({Level::FIVE, new sf::Texture});

	this->textureLevel[Level::ONE]->loadFromFile("Assets/GameState/LevelOne.png");
	this->textureLevel[Level::TWO]->loadFromFile("Assets/GameState/LevelTwo.png");
	this->textureLevel[Level::THREE]->loadFromFile("Assets/GameState/LevelThree.png");
	this->textureLevel[Level::FOUR]->loadFromFile("Assets/GameState/LevelFour.png");
	this->textureLevel[Level::FIVE]->loadFromFile("Assets/GameState/LevelFive.png");
	//---Init Level Texture---//
}

void GameState::initBackground()
{
	this->backgrounds[0] = new TileMoving(this->window, this->textureBackground, 0.f, -1.f * static_cast<float>(this->window->getSize().y), 150.f, sf::Vector2f(0.f, 1.f));
	this->backgrounds[1] = new TileMoving(this->window, this->textureBackground, 0.f, 0.f, 150.f, sf::Vector2f(0.f, 1.f));

	this->backgrounds[0]->setRelative(this->backgrounds[1]);
	this->backgrounds[1]->setRelative(this->backgrounds[0]);

	this->border = new Tile(this->window, this->textureBorder, 0.f, 90.f * (static_cast<float>(this->window->getSize().y) / 720.f) * 6.f);
}

void GameState::initButtons()
{
}

//---INITIALIZE FUNCTIONS---//
GameState::GameState(sf::RenderWindow* window, sf::Vector2i* mosPosWindow, sf::Vector2f* mosPosView, std::map<std::string, int>* keyBinds, std::map<std::string, bool>* keyBindPressed, std::map<std::string, bool*> booleans) : State(window, mosPosWindow, mosPosView, keyBinds, keyBindPressed, booleans)
{
	this->initTextures();
	this->initBackground();
	this->initButtons();

	this->prevWidth = static_cast<float>(this->window->getSize().x);
	this->prevHeight = static_cast<float>(this->window->getSize().y);

	//===Init Boolean (Maps)===//
	this->pause = false;
	this->restart = false;
	this->gameOver = false;
	this->renderBanner = true;

	this->booleansPause.insert({ "PauseGameState", &this->pause });
	this->booleansPause.insert({ "QuitGameState", &this->quit });

	this->booleansGameOver.insert({ "RetryGameState", this->booleans["RetryGameState"] });
	this->booleansGameOver.insert({ "QuitGameState", &this->quit });
	//---Init Boolean (Maps)---//

	this->level = Level::ONE;

	this->player = new Player(this->window, this->texturePlayer, this->level, 0.f, 540.f, this->keyBinds, this->keyBindPressed);
	this->enemies.push_back(new Enemy(this->window, this->textureEnemy[EnemyType::SARS], this->level, static_cast<float>(rand() % (this->window->getSize().x + 1)), 0.f, EnemyType::SARS));

	//===Init Timers===//
	this->cooldownPauseCreationMax = sf::seconds(0.5f);
	this->cooldownPauseCreation = this->cooldownPauseCreationMax;

	this->cooldownGameOver = sf::seconds(0.0f);
	this->cooldownGameOverMax = sf::seconds(120.f);

	switch (this->level)
	{
	case Level::ONE:
		this->cooldownEnemySpawnMax = sf::seconds(2.75f);
		break;
	case Level::TWO:
		this->cooldownEnemySpawnMax = sf::seconds(2.5f);
		break;
	case Level::THREE:
		this->cooldownEnemySpawnMax = sf::seconds(2.25f);
		break;
	case Level::FOUR:
		this->cooldownEnemySpawnMax = sf::seconds(2.0f);
		break;
	case Level::FIVE:
		this->cooldownGameOver = sf::seconds(0.0f);
		this->cooldownGameOverMax = sf::seconds(300.f);
		break;
	}

	this->cooldownEnemySpawn = this->cooldownEnemySpawnMax;

	this->cooldownLevelHideMax = sf::seconds(0.3f);
	this->cooldownLevelStayMax = sf::seconds(0.3f);
	this->cooldownLevelFullMax = this->cooldownLevelHideMax + this->cooldownLevelStayMax;
	//---Init Timers---//

	//===Init Level Banner===//
	this->levelBanner.setTexture(*this->textureLevel[this->level]);
	this->levelBanner.setPosition(this->window->getSize().x / 2.f - this->levelBanner.getGlobalBounds().width / 2.f, 12.5f * (static_cast<float>(this->window->getSize().y) / 720.f));
	//---Init Level Banner---//
}

GameState::~GameState()
{
	//===Delete GUI===//
	for (int i = 0; i < 2; i++)
	{
		delete this->backgrounds[i];
	}
	delete this->border;
	//---Delete GUI---//

	//===Delete Entities===//
	for (auto& i : this->enemies)
	{
		delete i;
	}
	this->enemies.clear();

	delete this->player;
	//---Delete Entities---//

	//===Delete Textures===//
	delete this->textureBackground;
	delete this->textureBorder;
	delete this->texturePlayer;
	delete this->textureBoss;

	delete this->textureBlast[BlastType::SINGLE];
	this->textureBlast.clear();

	delete this->textureEnemy[EnemyType::SARS];
	delete this->textureEnemy[EnemyType::DELTA];
	delete this->textureEnemy[EnemyType::OMI];
	this->textureEnemy.clear();

	delete this->textureLevel[Level::ONE];
	delete this->textureLevel[Level::TWO];
	delete this->textureLevel[Level::THREE];
	delete this->textureLevel[Level::FOUR];
	delete this->textureLevel[Level::FIVE];
	this->textureLevel.clear();
	//---Delete Textures===//
}

void GameState::endState()
{
}

void GameState::confirmQuit()
{
}

void GameState::resetButton()
{
}

EnemyType GameState::randomEnemy()
{
	switch (rand() % 3)
	{
	case 0:
		return EnemyType::SARS;	
	case 1:
		return EnemyType::DELTA;
	case 2:
		return EnemyType::OMI;
	default:
		return EnemyType::SARS;
	}
}

void GameState::updateLevel()
{
	switch (this->level)
	{
	case Level::ONE:
		if (this->player->getScore() >= 2500)
		{
			this->level = Level::TWO;
			this->levelBanner.setTexture(*this->textureLevel[this->level]);
			
			this->player->updateLevel();
			this->enemies.push_back(new Enemy(this->window, this->textureEnemy[EnemyType::DELTA], this->level, static_cast<float>(rand() % (this->window->getSize().x + 1)), 0.f, EnemyType::DELTA));

			this->cooldownEnemySpawnMax = sf::seconds(2.5f);
			this->cooldownEnemySpawn = this->cooldownEnemySpawnMax;
			this->cooldownGameOver = sf::seconds(0.f);

			this->cooldownLevelStay = sf::seconds(0.f);
			this->cooldownLevelHide = sf::seconds(0.f);
			this->cooldownLevelFull = sf::seconds(0.f);
			this->levelFlashCount = 0;
		}
		break;
	case Level::TWO:
		if (this->player->getScore() >= 7500)
		{
			this->level = Level::THREE;
			this->levelBanner.setTexture(*this->textureLevel[this->level]);
			
			this->player->updateLevel();
			this->enemies.push_back(new Enemy(this->window, this->textureEnemy[EnemyType::OMI], this->level, static_cast<float>(rand() % (this->window->getSize().x + 1)), 0.f, EnemyType::OMI));	

			this->cooldownEnemySpawnMax = sf::seconds(2.25f);
			this->cooldownEnemySpawn = this->cooldownEnemySpawnMax;
			this->cooldownGameOver = sf::seconds(0.f);

			this->cooldownLevelStay = sf::seconds(0.f);
			this->cooldownLevelHide = sf::seconds(0.f);
			this->cooldownLevelFull = sf::seconds(0.f);
			this->levelFlashCount = 0;
		}
		break;
	case Level::THREE:
		if (this->player->getScore() >= 17500)
		{
			this->level = Level::FOUR;
			this->levelBanner.setTexture(*this->textureLevel[this->level]);
			
			this->player->updateLevel();
			EnemyType ran;
			ran = this->randomEnemy();
			this->enemies.push_back(new Enemy(this->window, this->textureEnemy[ran], this->level, static_cast<float>(rand() % (this->window->getSize().x + 1)), 0.f, ran));
			
			this->cooldownEnemySpawnMax = sf::seconds(2.0f);
			this->cooldownEnemySpawn = this->cooldownEnemySpawnMax;
			this->cooldownGameOver = sf::seconds(0.f);

			this->cooldownLevelStay = sf::seconds(0.f);
			this->cooldownLevelHide = sf::seconds(0.f);
			this->cooldownLevelFull = sf::seconds(0.f);
			this->levelFlashCount = 0;
		}
		break;
	case Level::FOUR:
		if (this->player->getScore() >= 40000)
		{
			this->level = Level::FIVE;
			this->levelBanner.setTexture(*this->textureLevel[this->level]);

			this->player->updateLevel();
			//Spawn Boss

			this->cooldownEnemySpawn = this->cooldownEnemySpawnMax;
			this->cooldownGameOver = sf::seconds(0.f);

			this->cooldownLevelStay = sf::seconds(0.f);
			this->cooldownLevelHide = sf::seconds(0.f);
			this->cooldownLevelFull = sf::seconds(0.f);
			this->levelFlashCount = 0;
		}
		break;
	case Level::FIVE:
		break;
	}
}

void GameState::updateTimers(const float& dt)
{
	this->cooldownEnemySpawn += sf::seconds(dt);
	this->cooldownPauseCreation += sf::seconds(dt);
	this->cooldownGameOver += sf::seconds(dt);

	if (this->renderBanner)
	{ 
		this->cooldownLevelStay += sf::seconds(dt);
	}
	else 
	{
		this->cooldownLevelHide += sf::seconds(dt);
	}

	this->cooldownLevelFull += sf::seconds(dt);
}

void GameState::updateBlast(const float& dt)
{
	if(this->player->getSpacePressed())
	{
		this->blasts.push_back(new Blast(this->window, this->textureBlast[BlastType::SINGLE], this->level, this->player->getSprite().getPosition().x * 2.f + this->player->getSprite().getGlobalBounds().width, this->player->getSprite().getPosition().y));
		this->player->resetSpacePressed();
	}

	for (int i = 0; i < this->blasts.size(); i++)
	{
		if (this->blasts[i]->getDeleted())
		{
			this->blasts.erase(this->blasts.begin() + i);
		}
	}

	for (int i = 0; i < this->blasts.size(); i++)
	{
		this->blasts[i]->update(dt);
	}
}

void GameState::updateEnemies(const float& dt)
{
	//Enemy Spawner
	if (this->enemies.size() < 3)
	{
		switch (this->level)
		{
		case Level::ONE:
			if (this->enemies.size() < 1)
			{
				this->enemies.push_back(new Enemy(this->window, this->textureEnemy[EnemyType::SARS], this->level, static_cast<float>(rand() % (this->window->getSize().x + 1)), 0.f, EnemyType::SARS));
			}
			break;
		case Level::TWO: 
		{
			if (this->enemies.size() < 2)
			{
				switch (this->enemies.back()->getType())
				{
				case EnemyType::SARS:
					this->enemies.push_back(new Enemy(this->window, this->textureEnemy[EnemyType::DELTA], this->level, static_cast<float>(rand() % (this->window->getSize().x + 1)), 0.f, EnemyType::DELTA));
					break;
				case EnemyType::DELTA:
				default:
					this->enemies.push_back(new Enemy(this->window, this->textureEnemy[EnemyType::SARS], this->level, static_cast<float>(rand() % (this->window->getSize().x + 1)), 0.f, EnemyType::SARS));
					break;
				}
			}
			break;
		}
		case Level::THREE: 
		{
			switch (this->enemies.back()->getType())
			{
			case EnemyType::SARS:
				this->enemies.push_back(new Enemy(this->window, this->textureEnemy[EnemyType::DELTA], this->level, static_cast<float>(rand() % (this->window->getSize().x + 1)), 0.f, EnemyType::DELTA));
				break;
			case EnemyType::DELTA:
				this->enemies.push_back(new Enemy(this->window, this->textureEnemy[EnemyType::OMI], this->level, static_cast<float>(rand() % (this->window->getSize().x + 1)), 0.f, EnemyType::OMI));
				break;
			case EnemyType::OMI:
			default:
				this->enemies.push_back(new Enemy(this->window, this->textureEnemy[EnemyType::SARS], this->level, static_cast<float>(rand() % (this->window->getSize().x + 1)), 0.f, EnemyType::SARS));
				break;
			}
			break;
		}
		case Level::FOUR:
			EnemyType ran;
			ran = this->randomEnemy();
			this->enemies.push_back(new Enemy(this->window, this->textureEnemy[ran], this->level, static_cast<float>(rand() % (this->window->getSize().x + 1)), 0.f, ran));			break;
		case Level::FIVE:
			break;
		}
	}

	for (int i = 0; i < this->enemies.size(); i++)
	{
		this->enemies[i]->update(dt);
	}

	for (int i = 0; i < this->enemies.size(); i++)
	{
		this->enemies[i]->updateBlastCollision(this->blasts, this->player);
	}

	for (int i = 0; i < this->enemies.size(); i++)
	{
		this->enemies[i]->updateBorderCollision(this->player);
	}

	for (int i = 0; i < this->enemies.size(); i++)
	{
		if (this->enemies[i]->getDeleted()) 
		{
			this->enemies.erase(this->enemies.begin() + i);
		}
	}
}

void GameState::updateInput()
{
	if (this->keyBindPressed->at("PAUSE"))
	{
		if(this->cooldownPauseCreation >= this->cooldownPauseCreationMax)
		{
			switch (this->pause)
			{
			case false:
				this->pause = true;
				break;
			default:
				break;
			}
			this->cooldownPauseCreation = sf::seconds(0.f);
		}
	}
}

void GameState::updateSize()
{
	// Fixes the background sprites, if resolution changed
	if (this->prevWidth != static_cast<float>(this->window->getSize().x) || this->prevHeight != static_cast<float>(this->window->getSize().y))
	{
		for (int i = 0; i < 2; i++)
		{
			this->backgrounds[i]->updateSize(this->prevWidth, this->prevHeight);
		}

		this->border->updateSize(this->prevWidth, this->prevHeight);

		this->prevWidth = static_cast<float>(this->window->getSize().x);
		this->prevHeight = static_cast<float>(this->window->getSize().y);
	}
}

void GameState::update(const float& dt)
{
	/*
	--Check if screen width/height has changed has changed
	*/
	this->updateSize();

	if ( (this->cooldownGameOver >= this->cooldownGameOverMax) || (this->player->getHealth() < 0.0) && (!this->gameOver))
	{
		this->stateStack.push(new GameOverState(this->window, this->mosPosWindow, this->mosPosView, this->keyBinds, this->keyBindPressed, this->booleansGameOver));
		this->player->updateBars();
		this->player->updateBars();
		this->player->updateBars();
		this->gameOver = true;
	}

	if ((this->pause && !this->gameOver) && (this->stateStack.empty())) // Checks if the player has initiated pause AND the stack is already empty
	{
		this->stateStack.push(new PauseState(this->window, this->mosPosWindow, this->mosPosView, this->keyBinds, this->keyBindPressed, this->booleansPause));
	}

	if (!this->stateStack.empty()) // If the stack isn't empty, that state will be updated
	{
		this->stateStack.top()->update(dt);
		if (this->stateStack.top()->getQuit())
		{
			this->stateStack.top()->confirmQuit();
			if (this->stateStack.top()->getQuit()) // Done Twice because the it will first confirm that user still chooses to quit, saving etc
			{
				this->stateStack.top()->endState();
				delete this->stateStack.top();
				this->stateStack.pop();
			}
		}
		return;
	}

	this->updateTimers(dt);

	this->updateInput();

	this->updateLevel();

	//===Update Entities===//
	this->player->update(dt);

	this->updateBlast(dt);

	this->updateEnemies(dt);
	//---Update Entities---//

	//===Update GUI===//
	for (int i = 0; i < 2; i++)
	{
		this->backgrounds[i]->update(dt);
	}
	this->border->update(dt);
	//---Update GUI---//
}

void GameState::renderLevelBanner(sf::RenderTarget* target)
{
	if (this->levelFlashCount < 3)
	{
		if (this->cooldownLevelStay >= this->cooldownLevelStayMax) // If the banner has stayed long enough
		{
			this->renderBanner = false;
			this->cooldownLevelStay = sf::seconds(0.f);
		}
		else if (this->cooldownLevelHide >= this->cooldownLevelHideMax) // If the banner has hid long enough
		{
			this->renderBanner = true;
			this->cooldownLevelHide = sf::seconds(0.f);
		}

		if (this->renderBanner == true)
		{
			target->draw(this->levelBanner); 
		}

		if (this->cooldownLevelFull >= this->cooldownLevelFullMax)
		{
			this->levelFlashCount++;
			this->cooldownLevelFull = sf::seconds(0.f);
		}
	}
	else
	{
		target->draw(this->levelBanner);
	}
}

void GameState::render(sf::RenderTarget* target)
{
	/*
	* Render Hierarchy
		Background
		Player
		Blast
		Enemy
		Shield
		State
	*/
	for (int i = 0; i < 2; i++)
	{
		this->backgrounds[i]->render(target);
	}

	//===Render Entities===//
	this->player->render(target);

	for (int i = 0; i < this->blasts.size(); i++)
	{
		this->blasts[i]->render(target);
	}

	for (int i = 0; i < this->enemies.size(); i++)
	{
		this->enemies[i]->render(target);
	}
	//===Render Entities===//

	this->renderLevelBanner(target);
	this->border->render(target);

	if (!this->stateStack.empty()) // As long as the stack is not empty, it will render the top
	{
		this->stateStack.top()->render(target);
	}
}
