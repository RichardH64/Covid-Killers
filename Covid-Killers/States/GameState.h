#ifndef GAMESTATE_H
#define GAMESTATE_H

#include "../TileSets/TileMap.h"

#include "../Entity/Enemy.h"
#include "../Entity/Player.h"
#include "../GUI/Bar.h"
#include "PauseState.h"
#include "GameOverState.h"

class GameState : public State
{
private:
	int levelFlashCount;

	//===Textures===//
	sf::Texture* textureBackground;
	sf::Texture* textureBorder;

	sf::Texture* texturePlayer;
	sf::Texture* textureBoss;

	std::map<Level, sf::Texture*> textureLevel;
	std::map<EnemyType, sf::Texture*> textureEnemy;
	std::map<BlastType, sf::Texture*> textureBlast;
	//---Textures---//

	//===GUI===//
	sf::Sprite levelBanner;

	TileMap* tileBackgrounds[3];
	TileMap* tileBorder;

	Bar* bars[3];
	//===GUI===//

	//===Booleans===//
	bool pause, restart, gameOver, renderBanner;

	std::map<std::string, bool*> booleansPause;
	std::map<std::string, bool*> booleansGameOver;
	//---Booleans---//

	//===Entities===//
	Player* player;
	std::vector<Blast*> blasts;
	std::vector<Enemy*> enemies;
	//---Entities---//

	//===Timers===//
	sf::Time cooldownEnemySpawn, cooldownEnemySpawnMax; // Enemy Spawn Cooldown
	sf::Time cooldownPauseCreation, cooldownPauseCreationMax; // Pause State Creation Timer
	sf::Time cooldownGameOver, cooldownGameOverMax; // Pause State Creation Timer
	sf::Time cdLevelHide, cooldownLevelHideMax;
	sf::Time cdLevelStay, cooldownLevelStayMax;
	sf::Time cdLevelFull, cooldownLevelFullMax;

	sf::Time cdStateCreation, cdStateDeletion;
	static const float cdStateChangeMax;
	//---Timers---//

	std::stack<State*> stateStack;
	Level level;

	void initTextures() override;
	void initAssets() override;
	void initButtons() override;
public:
	//===CONSTRUCTORS||DESTRUCTORS===//
	GameState(sf::RenderWindow* window, sf::Vector2i* mosPosWindow, sf::Vector2f* mosPosView, std::map<std::string, int>* keyBinds, std::map<std::string, bool>* keyBindPressed, std::map<std::string, bool*> booleans);
	virtual ~GameState();

	void endState() override;
	void confirmQuit() override;
	void resetButton() override;
	
	EnemyType randomEnemy();

	void updateGlobalTimer(const float& dt);
	void updateGlobalInput() override;

	void updateLevel(); 
	void updateTimers(const float& dt);
	void updateGameOver(const float& dt);
	void updateBlast(const float& dt);
	void updateEnemies(const float& dt);

	void updateInput();

	//===GAME VIEW===//
	void updateGameView(const float& dt);
	//---GAME VIEW---//

	void update(const float& dt) override;

	void renderLevelBanner(sf::RenderTarget* target);

	//===GAME VIEW===//
	void renderGameView(sf::RenderTarget* target);
	//---GAME VIEW---//

	void render(sf::RenderTarget* target = NULL) override;
};

#endif