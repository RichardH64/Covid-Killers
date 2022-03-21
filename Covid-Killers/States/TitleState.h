#ifndef TITLESTATE_H
#define TITLESTATE_H

#include "State.h"
#include "../Buttons/Button.h"
#include "../TileSets/GSTileSet.h"


class TitleState : public State
{
private:
	sf::Text textTitle;
	sf::Texture* textureBackground;
	GSTileSet* background;

	void initTextures() override;
	void initButtons() override;
public:
	//===CONSTRUCTORS||DESTRUCTORS===//
	TitleState(sf::RenderWindow* window, sf::Vector2i* mosPosWindow, sf::Vector2f* mosPosView, std::map<std::string, bool*> booleans);
	virtual ~TitleState();

	void endState() override;
	void confirmQuit() override;
	void updateInput() override;
	void update(const float& dt) override;
	void render(sf::RenderTarget* target = NULL) override;
};
#endif




