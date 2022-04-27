#include "GameOverState.h"

//===INITIALIZE FUNCTIONS===//
void GameOverState::initTextures()
{
	//===Init Button Textures===//
	this->textureButton.insert({ "Retry", new sf::Texture });
	this->textureButton.insert({ "Quit", new sf::Texture });

	this->textureButton["Retry"]->loadFromFile("Assets/Buttons/ButtonRetry.png");
	this->textureButton["Quit"]->loadFromFile("Assets/Buttons/ButtonQuit.png");
	//---Init Button Textures---//

	this->textTitle.setFont(this->fontConnectionII);
	this->textTitle.setCharacterSize(static_cast<unsigned int>(128.f * (this->window->getView().getSize().x + this->window->getView().getSize().y) / 2000.f));
	this->textTitle.setStyle(sf::Text::Bold);
	this->textTitle.setString("GAME OVER");
	this->textTitle.setLetterSpacing(1.5f * (this->window->getView().getSize().x + this->window->getView().getSize().y) / 2000.f);

	float titleX = this->window->getView().getSize().x / 2.f - this->textTitle.getGlobalBounds().width / 2.f;
	float titleY = this->window->getView().getSize().y / 2.f - this->textTitle.getGlobalBounds().height / 2.f - 150.f * this->window->getView().getSize().y / 720.f;

	this->textTitle.setPosition(sf::Vector2f(titleX, titleY));
}

void GameOverState::initButtons()
{
	this->buttons.push_back(new Button(this->window, this->textureButton["Retry"], this->booleans["RetryGameState"], true, 0.f, 225.f));
	this->buttons.push_back(new Button(this->window, this->textureButton["Quit"], this->booleans["QuitGameState"], true, 0.f, 300.f));
}
//---INITIALIZE FUNCTIONS---//

GameOverState::GameOverState(sf::RenderWindow* window, sf::Vector2i* mosPosWindow, sf::Vector2f* mosPosView, std::map<std::string, int>* keyBinds, std::map<std::string, bool>* keyBindPressed, std::map<std::string, bool*> booleans) : State(window, mosPosWindow, mosPosView, keyBinds, keyBindPressed, booleans)
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

	delete this->textureButton["Blank"];
	delete this->textureButton["Quit"];
}

void GameOverState::endState()
{

}

void GameOverState::confirmQuit()
{
}

void GameOverState::resetButton()
{
	for (int i = 0; i < this->buttons.size(); i++)
	{
		this->buttons[i]->reset();
	}
}


void GameOverState::updateInput()
{
} 

void GameOverState::update(const float& dt)
{
	for (int i = 0; i < this->buttons.size(); i++)
	{
		this->buttons[i]->update(dt, *this->mosPosView);
	}
}

void GameOverState::render(sf::RenderTarget* target)
{
	target->draw(this->textTitle);

	for (int i = 0; i < this->buttons.size(); i++)
	{
		this->buttons[i]->render(target);
	}
}
