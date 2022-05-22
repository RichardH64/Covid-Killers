#include "PauseState.h"


//===INITIALIZE FUNCTIONS===//
void PauseState::initTextures()
{
	//===Init Button Textures===//
	this->textureButton.insert({ "Continue", new sf::Texture });
	this->textureButton.insert({ "Settings", new sf::Texture });
	this->textureButton.insert({ "Quit", new sf::Texture });

	this->textureButton["Continue"]->loadFromFile("Assets/Buttons/ButtonContinue.png");
	this->textureButton["Settings"]->loadFromFile("Assets/Buttons/ButtonSettings.png");
	this->textureButton["Quit"]->loadFromFile("Assets/Buttons/ButtonQuit.png");
	//---Init Button Textures---//
}

void PauseState::initText()
{
	this->textTitle.setFont(this->fontConnectionII);
	this->textTitle.setCharacterSize(static_cast<unsigned int>(128.f * (this->window->getDefaultView().getSize().x + this->window->getDefaultView().getSize().y) / 2000.f));
	this->textTitle.setStyle(sf::Text::Bold);
	this->textTitle.setString("PAUSE");
	this->textTitle.setLetterSpacing(1.5f * (this->window->getDefaultView().getSize().x + this->window->getDefaultView().getSize().y) / 2000.f);

	sf::Vector2f titlePosition;
	titlePosition.x = this->window->getDefaultView().getSize().x / 2.f - this->textTitle.getGlobalBounds().width / 2.f;
	titlePosition.y = this->window->getDefaultView().getSize().y / 2.f - this->textTitle.getGlobalBounds().height / 2.f - 150.f * this->window->getDefaultView().getSize().y / 720.f;

	this->textTitle.setPosition(titlePosition);
}

void PauseState::initAssets()
{

}

void PauseState::initButtons()
{
	this->booleans.insert({"ContinueGameState", &this->quit}); // ContinueGameState = QuitPauseState

	this->buttons.push_back(new Button(this->window, this->textureButton["Continue"], this->booleans["ContinueGameState"], true, 0.f, 150.f));
	this->buttons.push_back(new Button(this->window, this->textureButton["Settings"], new bool, true, 0.f, 225.f));
	this->buttons.push_back(new Button(this->window, this->textureButton["Quit"], this->booleans["QuitGameState"], true, 0.f, 300.f));
}
//---INITIALIZE FUNCTIONS---//

PauseState::PauseState(sf::RenderWindow* window, sf::Vector2i* mosPosWindow, sf::Vector2f* mosPosView, std::map<std::string, int>* keyBinds, std::map<std::string, bool>* keyBindPressed, std::map<std::string, bool*> booleans) : State(window, mosPosWindow, mosPosView, keyBinds, keyBindPressed, booleans)
{
	this->initTextures();
	this->initText();
	this->initAssets();
	this->initButtons();
}

PauseState::~PauseState()
{
	// Delete All The Buttons
	for (auto& i : this->buttons)
	{
		delete i;
	}
	this->buttons.clear();

	delete this->textureButton["Continue"];
	delete this->textureButton["Settings"];
	delete this->textureButton["Quit"];
}

void PauseState::endState()
{

}

void PauseState::confirmQuit()
{

}

void PauseState::resetButton()
{
	for (int i = 0; i < this->buttons.size(); i++)
	{
		this->buttons[i]->reset();
	}
}

void PauseState::updateGlobalInput()
{

}

void PauseState::update(const float& dt)
{
	for (int i = 0; i < this->buttons.size(); i++)
	{
		this->buttons[i]->update(dt, *this->mosPosView);
	}
}

void PauseState::render(sf::RenderTarget* target)
{
	target->draw(this->textTitle);

	for (int i = 0; i < this->buttons.size(); i++)
	{
		this->buttons[i]->render(target);
	}
}
