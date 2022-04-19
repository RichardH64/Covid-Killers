#ifndef GAMESTATE_H
#define GAMESTATE_H

#include "../TileSets/TileMoving.h"
#include "../Entity/Enemy.h"
#include "../Entity/Player.h"
#include "PauseState.h"
#include "GameOverState.h"

class GameState : public State
{
private:
	float prevWidth, prevHeight;
	int levelFlashCount;
	sf::Sprite levelBanner;

	TileMoving* backgrounds[2];
	Tile* border;

	//===Textures===//
	sf::Texture* textureBackground;
	sf::Texture* textureBorder;

	sf::Texture* texturePlayer;
	sf::Texture* textureBoss;

	std::map<Level, sf::Texture*> textureLevel;
	std::map<EnemyType, sf::Texture*> textureEnemy;
	std::map<BlastType, sf::Texture*> textureBlast;
	//---Textures---//

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
	sf::Time cooldownLevelHide, cooldownLevelHideMax;
	sf::Time cooldownLevelStay, cooldownLevelStayMax;
	sf::Time cooldownLevelFull, cooldownLevelFullMax;
	//---Timers---//

	std::stack<State*> stateStack;
	Level level;

	void initTextures() override;
	void initBackground();
	void initButtons() override;
public:
	//===CONSTRUCTORS||DESTRUCTORS===//
	GameState(sf::RenderWindow* window, sf::Vector2i* mosPosWindow, sf::Vector2f* mosPosView, std::map<std::string, int>* keyBinds, std::map<std::string, bool>* keyBindPressed, std::map<std::string, bool*> booleans);
	virtual ~GameState();

	void endState() override;
	void confirmQuit() override;
	void resetButton() override;
	
	EnemyType randomEnemy();

	void updateLevel(); 
	void updateTimers(const float& dt);
	void updateGameOver(const float& dt);
	void updateBlast(const float& dt);
	void updateEnemies(const float& dt);
	void updateInput() override;
	void updateSize();
	void update(const float& dt) override;

	void renderLevelBanner(sf::RenderTarget* target);
	void render(sf::RenderTarget* target = NULL) override;
};

#endif