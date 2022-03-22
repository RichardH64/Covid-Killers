#ifndef PAUSESTATE_H
#define PAUSESTATE_H

#include "State.h"

class PauseState : public State
{
private:
	sf::Text textTitle;

	std::map<std::string, sf::Texture*> textureButton;

	sf::Time cooldownCreation, cooldownCreationMax;
	void initTextures() override;
	void initButtons() override;
public:
	PauseState(sf::RenderWindow* window, sf::Vector2i* mosPosWindow, sf::Vector2f* mosPosView, std::map<std::string, bool*> booleans);
	virtual ~PauseState();

	void endState() override;
	void confirmQuit() override;
	void updateInput() override;
	void update(const float& dt) override;
	void render(sf::RenderTarget* target = NULL) override;
};

#endif // !PAUSESTATE_H



