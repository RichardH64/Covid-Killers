#ifndef GAME_H
#define GAME_H


#include "States/TitleState.h"
#include "States/GameState.h"


class Game
{
private:
	//Variables
	//Window
	sf::RenderWindow* window;
	sf::Event ev;

	sf::Clock dtClock;
	float dt;

	//bool fullScreen;

	//===Booleans (Map)===//
	std::map<std::string, bool*> booleans;
	//---Booleans (Map)---//

	//===Keybind (Map)===//
	std::map<std::string, int> supportedKeys;
	std::map<std::string, int> keyBinds;
	std::map<std::string, bool> keyBindPressed;
	//---Keybind (Map)---//

	std::stack<State*> states;

	//===MOUSE POSITION===//
	sf::Vector2i mosPosWindow;
	sf::Vector2f mosPosView;
	//---MOUSE POSITION---//

	//===PRIVATE FUNCTIONS===//
	void initWindow();
	void initBooleans();
	void initSupportedKeys();
	void initKeyBinds();
	void initStates();
	//---PRIVATE FUNCTIONS---//
public:
	//===CONSTRUCTORS||DESTRUCTORS===//
	Game();
	virtual ~Game();
	//---CONSTRUCTORS||DESTRUCTORS---//


	//===PUBLIC FUNCTIONS===//
	void endApplication();

	//===UPDATE===//
	void updateDeltaTime();
	void updateEvents();
	void updateMousePostions();

	void updateBools();
	void updateStates();
	void update();
	//---UPDATE---//

	//===RENDER===//
	void renderStates();
	void render();
	//---RENDER--//

	//===CORE===//
	void run();
	//---CORE---//
	//---PUBLIC FUNCTIONS---//
};

#endif
