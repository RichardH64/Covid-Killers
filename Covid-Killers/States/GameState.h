#ifndef GAMESTATE_H
#define GAMESTATE_H


#include "../TileSets/GSTileSet.h"
#include "../TileSets/GSBorderTileSet.h"
#include "../Entity/Enemy.h"
#include "../Entity/Player.h"
#include "PauseState.h"
#include "GameOverState.h"

class GameState : public State
{
private:
	float prevWidth, prevHeight;
	sf::Sprite levelBanner;

	GSTileSet* backgrounds[2];
	GSBorderTileSet* border;

	//===Textures===//
	sf::Texture* textureBackground;
	sf::Texture* textureBorder;

	sf::Texture* texturePlayer;
	sf::Texture* textureBoss;
	sf::Texture* textureBlast[2];

	std::map<EnemyType, sf::Texture*> textureEnemy;
	std::map<Level, sf::Texture*> textureLevel;
	//---Textures---//

	//===Booleans===//
	bool pause, restart, gameOver;

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
	//---Timers---//

	std::stack<State*> stateStack;
	Level level;

	void initTextures() override;
	void initBackground();
	void initButtons() override;
public:
	//===CONSTRUCTORS||DESTRUCTORS===//
	GameState(sf::RenderWindow* window, sf::Vector2i* mosPosWindow, sf::Vector2f* mosPosView, std::map<std::string, bool*> booleans);
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
	void render(sf::RenderTarget* target = NULL) override;
};

#endif