#ifndef STATE_H
#define STATE_H

#include "../Buttons/Button.h"

class State
{
private:

protected:
	sf::Font fontConnectionII;
	sf::RenderWindow* window;
	sf::Vector2i* mosPosWindow;
	sf::Vector2f* mosPosView;
	bool quit;

	float prevWidth, prevHeight;
	std::map<std::string, bool*> booleans;

	//===KeyBinds===//
	std::map<std::string, int>* keyBinds;
	std::map<std::string, bool>* keyBindPressed;
	//---KeyBinds---//

	//===Resources===//
	std::vector<sf::Texture> textures;
	std::vector<Button*> buttons;
	//---Resources---//

	virtual void initTextures() = 0;
	virtual void initAssets() = 0;
	virtual void initButtons() = 0;

public:
	State(sf::RenderWindow* window, sf::Vector2i* mosPosWindow, sf::Vector2f* mosPosView, std::map<std::string, int>* keyBinds, std::map<std::string, bool>* keyBindPressed);
	State(sf::RenderWindow* window, sf::Vector2i* mosPosWindow, sf::Vector2f* mosPosView, std::map<std::string, int>* keyBinds, std::map<std::string, bool>* keyBindPressed, std::map<std::string, bool*> booleans);
	virtual ~State();

	const bool& getQuit() const;
	void setQuit();

	virtual void endState() = 0;
	virtual void confirmQuit() = 0;
	virtual void resetButton() = 0;

	virtual void updateGlobalInput() = 0;
	virtual void update(const float& dt) = 0;
	virtual void render(sf::RenderTarget* target = NULL) = 0;
};

#endif
