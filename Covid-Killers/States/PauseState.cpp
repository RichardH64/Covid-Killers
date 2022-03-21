#include "PauseState.h"

//===INITIALIZE FUNCTIONS===//
void PauseState::initTextures()
{
	this->textTitle.setFont(this->fontConnectionII);
	this->textTitle.setCharacterSize(128);
	this->textTitle.setStyle(sf::Text::Bold);
	this->textTitle.setString("PAUSE");
	this->textTitle.setLetterSpacing(1.5f);

	float titleX = this->window->getSize().x / 2.f - this->textTitle.getGlobalBounds().width / 2.f;
	float titleY = this->window->getSize().y / 2.f - this->textTitle.getGlobalBounds().height / 2.f - 150.f;

	this->textTitle.setPosition(sf::Vector2f(titleX, titleY));
}

void PauseState::initButtons()
{
	this->booleans.insert({"ContinueGameState", &this->quit}); // ContinueGameState = QuitPauseState

	this->buttons.push_back(new Button(this->window, "Assets/PauseState/ButtonContinue.png", this->booleans["ContinueGameState"], true, 0.f, 150.f));
	this->buttons.push_back(new Button(this->window, "Assets/ButtonSettings.png", new bool, true, 0.f, 225.f));
	this->buttons.push_back(new Button(this->window, "Assets/ButtonQuit.png", this->booleans["QuitGameState"], true, 0.f, 300.f));
}
//---INITIALIZE FUNCTIONS---//
PauseState::PauseState(sf::RenderWindow* window, sf::Vector2i* mosPosWindow, sf::Vector2f* mosPosView, std::map<std::string, bool*> booleans) : State(window, mosPosWindow, mosPosView, booleans)
{
	this->initTextures();
	this->initButtons();

	this->cooldownCreationMax = sf::seconds(0.5f);
}

PauseState::~PauseState()
{
	// Delete All The Buttons
	for (auto& i : this->buttons)
	{
		delete i;
	}
	this->buttons.clear();
}

void PauseState::endState()
{
	*this->booleans["PauseGameState"] = false;
}

void PauseState::confirmQuit()
{
}

void PauseState::updateInput()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
	{
		if (this->cooldownCreation >= this->cooldownCreationMax)
		{
			this->quit = true;
		}
	}
}

void PauseState::update(const float& dt)
{
	this->cooldownCreation += sf::seconds(dt);
	this->updateInput();
	for (auto& i : this->buttons)
	{
		i->update(*this->mosPosView);
	}
}

void PauseState::render(sf::RenderTarget* target)
{
	target->draw(this->textTitle);

	for (auto& i : this->buttons)
	{
		i->render(target);
	}
}
