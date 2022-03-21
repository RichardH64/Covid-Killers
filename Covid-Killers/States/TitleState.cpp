#include "TitleState.h"

//===INITIALIZE FUNCTIONS===//
void TitleState::initTextures()
{
	this->textureBackground = new sf::Texture;
	this->textureBackground->loadFromFile("Assets/GameState/Background.png");

	this->background = new GSTileSet(this->window, this->textureBackground, 0.f);

	this->textTitle.setFont(this->fontConnectionII);
	this->textTitle.setCharacterSize(128);
	this->textTitle.setStyle(sf::Text::Bold);
	this->textTitle.setString("COVID KILLERS");
	this->textTitle.setLetterSpacing(1.1f);

	float titleX = this->window->getSize().x / 2.f - this->textTitle.getGlobalBounds().width / 2.f;
	float titleY = this->window->getSize().y / 2.f - this->textTitle.getGlobalBounds().height / 2.f - 150.f;

	this->textTitle.setPosition(sf::Vector2f(titleX, titleY));
}

void TitleState::initButtons()
{
	this->booleans.insert({"QuitGame", &this->quit});
	this->buttons.push_back(new Button(this->window, "Assets/TitleState/ButtonStart.png", this->booleans["CreateGameState"], true, -132.5f, 150.f));
	this->buttons.push_back(new Button(this->window, "Assets/TitleState/ButtonHighScore.png", new bool, true, 132.5f, 150.f));
	this->buttons.push_back(new Button(this->window, "Assets/ButtonSettings.png", new bool, true, 132.5f, 225.f));
	this->buttons.push_back(new Button(this->window, "Assets/ButtonQuit.png", this->booleans["QuitGame"], true, 0.f, 300.f));
}
//---INITIALIZE FUNCTIONS---//

TitleState::TitleState(sf::RenderWindow* window, sf::Vector2i* mosPosWindow, sf::Vector2f* mosPosView, std::map<std::string, bool*> booleans) : State(window, mosPosWindow, mosPosView, booleans)
{
	this->initTextures();
	this->initButtons();
}

TitleState::~TitleState()
{
	// Delete All The Buttons
	for (auto& i : this->buttons)
	{
		delete i;
	}
	this->buttons.clear();
}

void TitleState::endState()
{
}

void TitleState::confirmQuit()
{
}

void TitleState::updateInput()
{
}

void TitleState::update(const float& dt)
{
	for (auto& i : this->buttons)
	{
		i->update(*this->mosPosView);
	}
}

void TitleState::render(sf::RenderTarget* target)
{
	this->background->render(target);

	for (auto& i : this->buttons)
	{
		i->render(target);
	}

	target->draw(this->textTitle);
}
