#include "TitleState.h"

//===INITIALIZE FUNCTIONS===//
void TitleState::initTextures()
{
	//===Init Button Textures===//
	this->textureButton.insert({ "Start", new sf::Texture });
	this->textureButton.insert({"HighScore", new sf::Texture});
	this->textureButton.insert({"Blank", new sf::Texture});
	this->textureButton.insert({"Settings", new sf::Texture});
	this->textureButton.insert({"Quit", new sf::Texture});

	this->textureButton["Start"]->loadFromFile("Assets/Buttons/ButtonStart.png");
	this->textureButton["HighScore"]->loadFromFile("Assets/Buttons/ButtonHighScore.png");
	this->textureButton["Blank"]->loadFromFile("Assets/Buttons/ButtonBlank.png");
	this->textureButton["Settings"]->loadFromFile("Assets/Buttons/ButtonSettings.png");
	this->textureButton["Quit"]->loadFromFile("Assets/Buttons/ButtonQuit.png");
	//---Init Button Textures---//

	//===Init Background Texture===//
	this->textureBackground = new sf::Texture;
	this->textureBackground->loadFromFile("Assets/Tiles/Background.png");
	//---Init Background Texture---//

	this->textTitle.setFont(this->fontConnectionII);
	this->textTitle.setCharacterSize(static_cast<unsigned int>(128.f * (this->window->getView().getSize().x + this->window->getView().getSize().y) / 2000.f));
	this->textTitle.setStyle(sf::Text::Bold);
	this->textTitle.setString("COVID KILLERS");
	this->textTitle.setLetterSpacing(1.1f * (this->window->getView().getSize().x + this->window->getView().getSize().y) / 2000.f);

	float titleX = this->window->getView().getSize().x / 2.f - this->textTitle.getGlobalBounds().width / 2.f;
	float titleY = this->window->getView().getSize().y / 2.f - this->textTitle.getGlobalBounds().height / 2.f - 150.f * this->window->getView().getSize().y / 720.f;

	this->textTitle.setPosition(sf::Vector2f(titleX, titleY));
}

void TitleState::initAssets()
{
	sf::Vector2f scale = divideVector(this->window->getDefaultView().getSize(), sf::Vector2f(1280.f, 720.f));

	this->tileBackground = new TileMap();
	this->tileBackground->load(this->textureBackground, scale);
	this->tileBackground->setPosition(multiplyVector(sf::Vector2f(0.f, 0.f), scale));
}

void TitleState::initButtons()
{
	this->booleans.insert({"QuitGame", &this->quit});

	this->buttons.push_back(new Button(this->window, this->textureButton["Start"], this->booleans["CreateGameState"], true, -132.5f, 150.f));
	this->buttons.push_back(new Button(this->window, this->textureButton["HighScore"], new bool, true, 132.5f, 150.f));
	this->buttons.push_back(new Button(this->window, this->textureButton["Blank"], new bool, true, -132.5f, 225.f));
	this->buttons.push_back(new Button(this->window, this->textureButton["Settings"], new bool, true, 132.5f, 225.f));
	this->buttons.push_back(new Button(this->window, this->textureButton["Quit"], this->booleans["QuitGame"], true, 0.f, 300.f));
}
//---INITIALIZE FUNCTIONS---//

TitleState::TitleState(sf::RenderWindow* window, sf::Vector2i* mosPosWindow, sf::Vector2f* mosPosView, std::map<std::string, int>* keyBinds, std::map<std::string, bool>* keyBindPressed,  std::map<std::string, bool*> booleans) : State(window, mosPosWindow, mosPosView, keyBinds, keyBindPressed, booleans)
{
	this->initTextures();
	this->initAssets();
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

	delete this->tileBackground;

	delete this->textureBackground;
	delete this->textureButton["Start"];
	delete this->textureButton["HighScore"];
	delete this->textureButton["Blank"];
	delete this->textureButton["Settings"];
	delete this->textureButton["Quit"];

}

void TitleState::endState()
{
}

void TitleState::confirmQuit()
{
}

void TitleState::resetButton()
{
	for (int i = 0; i < this->buttons.size(); i++)
	{
		this->buttons[i]->reset();
	}
}

void TitleState::updateGlobalInput()
{
}

void TitleState::update(const float& dt)
{
	for (int i = 0; i < this->buttons.size(); i++)
	{
		this->buttons[i]->update(dt, *this->mosPosView);
	}
}

void TitleState::render(sf::RenderTarget* target)
{
	target->draw(*this->tileBackground);

	for (int i = 0; i < this->buttons.size(); i++)
	{
		this->buttons[i]->render(target);
	}

	target->draw(this->textTitle);
}
