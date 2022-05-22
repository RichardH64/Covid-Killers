#include "GameState.h"


const float GameState::cdStateChangeMax = 0.5f;


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

void GameState::initAssets()
{
	sf::Vector2f scale = divideVector(this->window->getDefaultView().getSize(), sf::Vector2f(1280.f, 720.f));

	//===BACKGROUND===//
	int j = 3;
	for (int i = 0; i < 3; i++)
	{
		this->tileBackgrounds[i] = new TileMap();
		this->tileBackgrounds[i]->load(this->textureBackground, scale);
		this->tileBackgrounds[i]->setPosition(sf::Vector2f(0.f, static_cast<float>(--j * this->window->getDefaultView().getSize().y)));
		this->tileBackgrounds[i]->getMovementComponent().isMoving = true;
		this->tileBackgrounds[i]->getMovementComponent().hasRelative = true;
		this->tileBackgrounds[i]->getMovementComponent().velocity = 150.f;
		this->tileBackgrounds[i]->getMovementComponent().direction = sf::Vector2f(0.f, 1.f);
	}
	//---BACKGROUND---//
	
	//===BORDER===//
	this->tileBorder = new TileMap();
	this->tileBorder->load(this->textureBorder, scale);
	this->tileBorder->setPosition(multiplyVector(sf::Vector2f(0.f, 540.f), scale));
	//---BORDER---//
}

void GameState::initButtons()
{
}

//---INITIALIZE FUNCTIONS---//
GameState::GameState(sf::RenderWindow* window, sf::Vector2i* mosPosWindow, sf::Vector2f* mosPosView, std::map<std::string, int>* keyBinds, std::map<std::string, bool>* keyBindPressed, std::map<std::string, bool*> booleans) : State(window, mosPosWindow, mosPosView, keyBinds, keyBindPressed, booleans)
{
	this->initTextures();
	this->initAssets();
	this->initButtons();
	
	sf::Vector2f scale = divideVector(this->window->getDefaultView().getSize(), sf::Vector2f(1280.f, 720.f));

	float scaleX = this->window->getView().getSize().x / 1280.f;
	float scaleY = this->window->getView().getSize().y / 720.f;

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

	this->player = new Player(this->window, this->texturePlayer, this->level, 0.f, 540.f * scaleY, this->keyBinds, this->keyBindPressed);
	this->enemies.push_back(new Enemy(this->window, this->textureEnemy[EnemyType::SARS], this->level, static_cast<float>(rand() % (static_cast<int>(this->window->getView().getSize().x) + 1)), 0.f, EnemyType::SARS));

	//===Init GUI===//
	this->bars[0] = new Bar(0.f, 0.f, 300.f * scaleX, 35.f * scaleY, this->player->getStatPtr('h', false), this->player->getStatPtr('h', true), sf::Color::Red);
	this->bars[1] = new Bar(0.f, 35.f * scaleY, 250.f * scaleX, 35.f * scaleY, this->player->getStatPtr('e', false), this->player->getStatPtr('e', true), sf::Color(0, 97, 255));
	this->bars[2] = new Bar(0.f, 70.f * scaleY, 200.f * scaleX, 35.f * scaleY, this->player->getStatPtr('s', false), this->player->getStatPtr('s', true), sf::Color::Green);
	//---Init GUI---//

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
	this->levelBanner.setScale(sf::Vector2f(scaleX, scaleY));
	this->levelBanner.setPosition(this->window->getView().getSize().x / 2.f - this->levelBanner.getGlobalBounds().width / 2.f, 12.5f);
	//---Init Level Banner---//
}

GameState::~GameState()
{
	//===Delete GUI===//
	for (int i = 0; i < 3; i++)
	{
		delete this->tileBackgrounds[i];
	}
	delete this->tileBorder;

	for (int i = 0; i < 3; i++)
	{
		delete this->bars[i];
		this->bars[i] = nullptr;
	}
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
			this->enemies.push_back(new Enemy(this->window, this->textureEnemy[EnemyType::DELTA], this->level, static_cast<float>(rand() % (static_cast<int>(this->window->getView().getSize().x) + 1)), 0.f, EnemyType::DELTA));

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
			this->enemies.push_back(new Enemy(this->window, this->textureEnemy[EnemyType::OMI], this->level, static_cast<float>(rand() % (static_cast<int>(this->window->getView().getSize().x) + 1)), 0.f, EnemyType::OMI));

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
			this->enemies.push_back(new Enemy(this->window, this->textureEnemy[ran], this->level, static_cast<float>(rand() % (static_cast<int>(this->window->getView().getSize().x) + 1)), 0.f, ran));
			
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
	if(this->player->getSpawnSingleBlast())
	{
		this->blasts.push_back(new Blast(this->window, this->textureBlast[BlastType::SINGLE], this->level, this->player->getSprite().getPosition().x * 2.f + this->player->getSprite().getGlobalBounds().width, this->player->getSprite().getPosition().y));
		this->player->resetSpawnSingleBlast();
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
				this->enemies.push_back(new Enemy(this->window, this->textureEnemy[EnemyType::SARS], this->level, static_cast<float>(rand() % (static_cast<int>(this->window->getView().getSize().x) + 1)), 0.f, EnemyType::SARS));
			}
			break;
		case Level::TWO: 
		{
			if (this->enemies.size() < 2)
			{
				switch (this->enemies.back()->getType())
				{
				case EnemyType::SARS:
					this->enemies.push_back(new Enemy(this->window, this->textureEnemy[EnemyType::DELTA], this->level, static_cast<float>(rand() % (static_cast<int>(this->window->getView().getSize().x) + 1)), 0.f, EnemyType::DELTA));
					break;
				case EnemyType::DELTA:
				default:
					this->enemies.push_back(new Enemy(this->window, this->textureEnemy[EnemyType::SARS], this->level, static_cast<float>(rand() % (static_cast<int>(this->window->getView().getSize().x) + 1)), 0.f, EnemyType::SARS));
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
				this->enemies.push_back(new Enemy(this->window, this->textureEnemy[EnemyType::DELTA], this->level, static_cast<float>(rand() % (static_cast<int>(this->window->getView().getSize().x) + 1)), 0.f, EnemyType::DELTA));
				break;
			case EnemyType::DELTA:
				this->enemies.push_back(new Enemy(this->window, this->textureEnemy[EnemyType::OMI], this->level, static_cast<float>(rand() % (static_cast<int>(this->window->getView().getSize().x) + 1)), 0.f, EnemyType::OMI));
				break;
			case EnemyType::OMI:
			default:
				this->enemies.push_back(new Enemy(this->window, this->textureEnemy[EnemyType::SARS], this->level, static_cast<float>(rand() % (static_cast<int>(this->window->getView().getSize().x) + 1)), 0.f, EnemyType::SARS));
				break;
			}
			break;
		}
		case Level::FOUR:
			EnemyType ran;
			ran = this->randomEnemy();
			this->enemies.push_back(new Enemy(this->window, this->textureEnemy[ran], this->level, static_cast<float>(rand() % (static_cast<int>(this->window->getView().getSize().x) + 1)), 0.f, ran));
			break;
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

void GameState::updateGlobalTimer(const float& dt)
{
	switch (this->stateStack.empty())
	{
	case false:
		this->cdStateDeletion += sf::seconds(dt);
		break;
	case true:
		this->cdStateCreation += sf::seconds(dt);
		break;
	default:
		break;
	}
}

void GameState::updateGlobalInput()
{
	if (this->keyBindPressed->at("PAUSE"))
	{
		switch (this->stateStack.empty())
		{
		case false:
			if (this->cdStateDeletion.asSeconds() >= this->cdStateChangeMax)
			{
				this->stateStack.top()->setQuit();
				this->stateStack.top()->confirmQuit();

				if (this->stateStack.top()->getQuit()) // Done Twice because the it will first confirm that user still chooses to quit, saving etc
				{
					this->stateStack.top()->endState();
					delete this->stateStack.top();
					this->stateStack.pop();
				}

				this->cdStateDeletion = sf::seconds(0.f); // RESET
			}
			break;
		case true:
			if (this->cdStateCreation.asSeconds() >= this->cdStateChangeMax)
			{
				this->stateStack.push(new PauseState(this->window, this->mosPosWindow, this->mosPosView, this->keyBinds, this->keyBindPressed, this->booleansPause));

				this->cdStateCreation = sf::seconds(0.f); // RESET
			}
			break;
		default:
			break;
		}
	}
}

void GameState::updateInput()
{
}

void GameState::updateGameView(const float& dt)
{
	//===BACKGROUND===//
	int relative[] = { 1, 2, 0 };
	for (int i = 0; i < 3; i++)
	{
		this->tileBackgrounds[i]->update(dt, this->window->getDefaultView(), this->tileBackgrounds[relative[i]]->getPosition());
	}
	//---BACKGROUND---//

	//===BORDER===//
	this->tileBorder->update(dt, this->window->getDefaultView());
	//---BORDER---//
}

void GameState::update(const float& dt)
{
	this->updateGlobalTimer(dt);
	this->updateGlobalInput();

	if ( (this->cooldownGameOver >= this->cooldownGameOverMax) || (this->player->getHealth() < 0.0) && (!this->gameOver))
	{
		this->stateStack.push(new GameOverState(this->window, this->mosPosWindow, this->mosPosView, this->keyBinds, this->keyBindPressed, this->booleansGameOver));
		this->gameOver = true;
	}

	if (!this->stateStack.empty()) // If the stack isn't empty, that state will be updated
	{
		this->stateStack.top()->update(dt);
		return;
	}

	this->updateTimers(dt);

	this->updateInput();

	this->updateLevel();

	this->updateGameView(dt);

	//===Update Entities===//
	this->player->update(dt);

	this->updateBlast(dt);

	this->updateEnemies(dt);
	//---Update Entities---//

	//===Update GUI===//
	for (int i = 0; i < 3; i++)
	{
		this->bars[i]->update();
	}

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

void GameState::renderGameView(sf::RenderTarget* target)
{
	//===BACKGROUND===//
	for (int i = 0; i < 3; i++)
	{
		target->draw(*this->tileBackgrounds[i]);
	}
	//---BACKGROUND---//
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

	this->renderGameView(target);
	/*
		for (int i = 0; i < 3; i++)
	{
		this->backgrounds[i]->render(target);
	}
	*/


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

	for (int i = 0; i < 3; i++)
	{
		this->bars[i]->render(target);
	}

	target->draw(*this->tileBorder);

	if (!this->stateStack.empty()) // As long as the stack is not empty, it will render the top
	{
		this->stateStack.top()->render(target);
	}
}
