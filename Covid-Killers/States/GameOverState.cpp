#include "GameOverState.h"

//===INITIALIZE FUNCTIONS===//
void GameOverState::initTextures()
{
	this->textTitle.setFont(this->fontConnectionII);
	this->textTitle.setCharacterSize(128);
	this->textTitle.setStyle(sf::Text::Bold);
	this->textTitle.setString("GAME OVER");
	this->textTitle.setLetterSpacing(1.5f);

	float titleX = this->window->getSize().x / 2.f - this->textTitle.getGlobalBounds().width / 2.f;
	float titleY = this->window->getSize().y / 2.f - this->textTitle.getGlobalBounds().height / 2.f - 150.f;

	this->textTitle.setPosition(sf::Vector2f(titleX, titleY));
}

void GameOverState::initButtons()
{
	this->buttons.push_back(new Button(this->window, "Assets/PauseState/ButtonContinue.png", this->booleans["RetryGameState"], true, 0.f, 225.f));
	this->buttons.push_back(new Button(this->window, "Assets/ButtonQuit.png", this->booleans["QuitGameState"], true, 0.f, 300.f));
}
//---INITIALIZE FUNCTIONS---//

GameOverState::GameOverState(sf::RenderWindow* window, sf::Vector2i* mosPosWindow, sf::Vector2f* mosPosView, std::map<std::string, bool*> booleans) : State(window, mosPosWindow, mosPosView, booleans)
{
	this->initTextures();
	this->initButtons();
}

GameOverState::~GameOverState()
{
	// Delete All The Buttons
	for (auto& i : this->buttons)
	{
		delete i;
	}
	this->buttons.clear();
}

void GameOverState::endState()
{

}

void GameOverState::confirmQuit()
{
}

void GameOverState::updateInput()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
	{
		this->quit = true;
	}
}

void GameOverState::update(const float& dt)
{
	//this->updateInput();
	for (auto& i : this->buttons)
	{
		i->update(*this->mosPosView);
	}
}

void GameOverState::render(sf::RenderTarget* target)
{
	target->draw(this->textTitle);

	for (auto& i : this->buttons)
	{
		i->render(target);
	}
}
