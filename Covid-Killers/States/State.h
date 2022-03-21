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

	//===Resources===//
	std::vector<sf::Texture> textures;
	std::vector<Button*> buttons;
	//---Resources---//

	//Functions
	//virtual void initKeybinds() = 0;
	virtual void initTextures() = 0;
	virtual void initButtons() = 0;

public:
	State(sf::RenderWindow* window, sf::Vector2i* mosPosWindow, sf::Vector2f* mosPosView);
	State(sf::RenderWindow* window, sf::Vector2i* mosPosWindow, sf::Vector2f* mosPosView, std::map<std::string, bool*> booleans);
	virtual ~State();

	const bool& getQuit() const;
	virtual void endState() = 0;
	virtual void confirmQuit() = 0;
	virtual void updateInput() = 0;
	virtual void update(const float& dt) = 0;
	virtual void render(sf::RenderTarget* target = NULL) = 0;
};

#endif
