#ifndef GAMEOVERSTATE_H
#define GAMEOVERSTATE_H

#include "State.h"
class GameOverState : public State
{
private:
	sf::Text textTitle;

	std::map<std::string, sf::Texture*> textureButton;

	void initTextures() override;
	void initButtons() override;
public:
	GameOverState(sf::RenderWindow* window, sf::Vector2i* mosPosWindow, sf::Vector2f* mosPosView, std::map<std::string, int>* keyBinds, std::map<std::string, bool>* keyBindPressed, std::map<std::string, bool*> booleans);
	virtual ~GameOverState();

	void endState() override;
	void confirmQuit() override;
	void resetButton() override;
	void updateInput() override;
	void update(const float& dt) override;
	void render(sf::RenderTarget* target = NULL) override;
};

#endif

