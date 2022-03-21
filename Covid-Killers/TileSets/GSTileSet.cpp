#include "GSTileSet.h"

const float GSTileSet::scaleThird = 1.f / 3.f;

GSTileSet::GSTileSet(sf::RenderWindow* window, sf::Texture* texture, float start)
{
	this->window = window;
	this->texture = texture;

	//===Create Scales===//
	this->scaleX = this->window->getSize().x / 1280.f;
	this->scaleY = this->window->getSize().y / 720.f;

	this->totScaleX = this->scaleThird * this->scaleX;
	this->totScaleY = this->scaleThird * this->scaleY;
	//---Create Scales---//

	//===Create Initial Position===//
	this->rowPosYOne = 0.f + start;
	this->rowPosYTwo = this->rowPosYOne + this->texture->getSize().y * this->totScaleY;
	this->rowPosYThree = this->rowPosYTwo + this->texture->getSize().y * this->totScaleY;

	this->colPosXOne = 0.f;
	this->colPosXTwo = this->scaleThird * this->window->getSize().x;
	this->colPosXThree = 2 * this->scaleThird * this->window->getSize().x;
	//---Create Initial Position---//

	this->backgroundTileSet = {
	{new sf::Sprite(*this->texture), new sf::Sprite(*this->texture), new sf::Sprite(*this->texture)},
	{new sf::Sprite(*this->texture), new sf::Sprite(*this->texture), new sf::Sprite(*this->texture)},
	{new sf::Sprite(*this->texture), new sf::Sprite(*this->texture), new sf::Sprite(*this->texture)}
	};

	//===ROW ONE===//
	// Top Left
	this->backgroundTileSet[0][0]->setScale(sf::Vector2f(totScaleX, totScaleY));
	this->backgroundTileSet[0][0]->setPosition(this->colPosXOne, this->rowPosYOne);
	// Top Middle
	this->backgroundTileSet[0][1]->setScale(sf::Vector2f(totScaleX, totScaleY));
	this->backgroundTileSet[0][1]->setPosition(this->colPosXTwo, this->rowPosYOne);
	// Top Right
	this->backgroundTileSet[0][2]->setScale(sf::Vector2f(totScaleX, totScaleY));
	this->backgroundTileSet[0][2]->setPosition(this->colPosXThree, this->rowPosYOne);

	//---ROW ONE---//

	//===ROW TWO===//
	// Middle Left
	this->backgroundTileSet[1][0]->setScale(sf::Vector2f(totScaleX, totScaleY));
	this->backgroundTileSet[1][0]->setPosition(this->colPosXOne, this->rowPosYTwo);
	// Middle Middle
	this->backgroundTileSet[1][1]->setScale(sf::Vector2f(totScaleX, totScaleY));
	this->backgroundTileSet[1][1]->setPosition(this->colPosXTwo, this->rowPosYTwo);
	// Middle Right
	this->backgroundTileSet[1][2]->setScale(sf::Vector2f(totScaleX, totScaleY));
	this->backgroundTileSet[1][2]->setPosition(this->colPosXThree, this->rowPosYTwo);
	//---ROW TWO---//

	//===ROW THREE===//
	// Bottom Left
	this->backgroundTileSet[2][0]->setScale(sf::Vector2f(totScaleX, totScaleY));
	this->backgroundTileSet[2][0]->setPosition(this->colPosXOne, this->rowPosYThree);
	// Bottom Middle
	this->backgroundTileSet[2][1]->setScale(sf::Vector2f(totScaleX, totScaleY));
	this->backgroundTileSet[2][1]->setPosition(this->colPosXTwo, this->rowPosYThree);
	// Bottom Right
	this->backgroundTileSet[2][2]->setScale(sf::Vector2f(totScaleX, totScaleY));
	this->backgroundTileSet[2][2]->setPosition(this->colPosXThree, this->rowPosYThree);
	//---ROW THREE---//
}

GSTileSet::~GSTileSet()
{
	// Delete All Tile Sprites
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			delete this->backgroundTileSet[i][j];
		}
		this->backgroundTileSet[i].clear();
	}
}

float* GSTileSet::getPosPtr()
{
	return &this->rowPosYOne;
}

void GSTileSet::setOtherTilePos(float* otp)
{
	this->otherTilePos = otp;
}

void GSTileSet::updateSize(float prevWidth, float prevHeight)
{
	this->scaleY = this->window->getSize().y / 720.f;

	this->totScaleY = this->scaleThird * this->scaleY;

	/*
	if (static_cast<float>(this->window->getSize().y) < 720.f)
	{
		this->scaleY = 1.f;
		this->totScaleY = this->scaleThird * this->scaleY;
	}
	*/

	this->rowPosYOne = this->rowPosYOne * (static_cast<float>(this->window->getSize().y) / prevHeight) + 1.f;
	this->rowPosYTwo = this->rowPosYOne + this->texture->getSize().y * this->totScaleY;
	this->rowPosYThree = this->rowPosYTwo + this->texture->getSize().y * this->totScaleY;

	//===ROW ONE===//
	// Top Left
	this->backgroundTileSet[0][0]->setScale(sf::Vector2f(totScaleX, totScaleY));
	this->backgroundTileSet[0][0]->setPosition(this->colPosXOne, this->rowPosYOne);
	// Top Middle
	this->backgroundTileSet[0][1]->setScale(sf::Vector2f(totScaleX, totScaleY));
	this->backgroundTileSet[0][1]->setPosition(this->colPosXTwo, this->rowPosYOne);
	// Top Right
	this->backgroundTileSet[0][2]->setScale(sf::Vector2f(totScaleX, totScaleY));
	this->backgroundTileSet[0][2]->setPosition(this->colPosXThree, this->rowPosYOne);

	//---ROW ONE---//

	//===ROW TWO===//
	// Middle Left
	this->backgroundTileSet[1][0]->setScale(sf::Vector2f(totScaleX, totScaleY));
	this->backgroundTileSet[1][0]->setPosition(this->colPosXOne, this->rowPosYTwo);
	// Middle Middle
	this->backgroundTileSet[1][1]->setScale(sf::Vector2f(totScaleX, totScaleY));
	this->backgroundTileSet[1][1]->setPosition(this->colPosXTwo, this->rowPosYTwo);
	// Middle Right
	this->backgroundTileSet[1][2]->setScale(sf::Vector2f(totScaleX, totScaleY));
	this->backgroundTileSet[1][2]->setPosition(this->colPosXThree, this->rowPosYTwo);
	//---ROW TWO---//

	//===ROW THREE===//
	// Bottom Left
	this->backgroundTileSet[2][0]->setScale(sf::Vector2f(totScaleX, totScaleY));
	this->backgroundTileSet[2][0]->setPosition(this->colPosXOne, this->rowPosYThree);
	// Bottom Middle
	this->backgroundTileSet[2][1]->setScale(sf::Vector2f(totScaleX, totScaleY));
	this->backgroundTileSet[2][1]->setPosition(this->colPosXTwo, this->rowPosYThree);
	// Bottom Right
	this->backgroundTileSet[2][2]->setScale(sf::Vector2f(totScaleX, totScaleY));
	this->backgroundTileSet[2][2]->setPosition(this->colPosXThree, this->rowPosYThree);
	//---ROW THREE---//

}

void GSTileSet::update(const float& dt)
{

	if (this->rowPosYOne >= static_cast<float>(this->window->getSize().y))
	{
		this->rowPosYOne = -1.f * static_cast<float>(this->window->getSize().y);
		this->rowPosYTwo = this->rowPosYOne + this->backgroundTileSet[0][0]->getLocalBounds().height * this->backgroundTileSet[0][0]->getScale().y;
		this->rowPosYThree = this->rowPosYTwo + this->backgroundTileSet[0][0]->getLocalBounds().height * this->backgroundTileSet[0][0]->getScale().y;
	}


	/*
	if(this->window->getView().getViewport().intersects(this->backgroundTileSet[0][0]->getGlobalBounds()) && this->rowPosYOne < -720.f)
	{
		if (static_cast<float>(this->window->getSize().y) == 720.f)
		{
			this->rowPosYOne = -720.f;
		}
	}
	*/

	/*
	if (this->rowPosYOne >= this->window->getSize().y)
	{
		std::cout << this->rowPosYOne << std::endl;
		if (static_cast<float>(this->window->getSize().y) == 720.f)
		{
			this->rowPosYOne = -720.f;
		}
		else
		{
			this->rowPosYOne = -720.f - (static_cast<float>(this->window->getSize().y) - 720.f);
		}
		//this->rowPosYOne = -721.f + (static_cast<float>(this->window->getSize().y)/720.f);
		this->rowPosYTwo = this->rowPosYOne + this->backgroundTileSet[0][0]->getGlobalBounds().height;
		this->rowPosYThree = this->rowPosYTwo + this->backgroundTileSet[0][0]->getGlobalBounds().height;
	}
	*/

	/*
	if (this->rowPosYOne >= this->window->getSize().y)
	{
		this->rowPosYOne = *this->otherTilePos - this->backgroundTileSet[0][0]->getGlobalBounds().height * 3 + 1;
		this->rowPosYTwo = this->scaleThird * (*this->otherTilePos - this->backgroundTileSet[0][0]->getGlobalBounds().height * 3) + 1;
		this->rowPosYThree = 2 * this->scaleThird * (*this->otherTilePos - this->backgroundTileSet[0][0]->getGlobalBounds().height * 3) + 1;
	}
	*/

	/*
	if (this->rowPosYOne >= this->window->getSize().y)
	{
		this->rowPosYOne = 0.f + (-720.f * (this->window->getSize().y / 720.f));
		this->rowPosYTwo = this->scaleThird * this->window->getSize().y + (-720.f * (this->window->getSize().y / 720.f));
		this->rowPosYThree = 2 * this->scaleThird * this->window->getSize().y + (-720.f * (this->window->getSize().y / 720.f));
	}
	*/

	/*
	if (this->rowPosYOne >= this->window->getSize().y)
	{
		this->rowPosYOne = 0.f + (-720.f * (this->window->getSize().y / 720.f));
		this->rowPosYTwo = this->scaleThird * this->window->getSize().y + (-720.f * (this->window->getSize().y / 720.f));
		this->rowPosYThree = 2 * this->scaleThird * this->window->getSize().y + (-720.f * (this->window->getSize().y / 720.f));
	}
	*/

	this->rowPosYOne++;
	this->rowPosYTwo++;
	this->rowPosYThree++;

	//===ROW ONE===//
	this->backgroundTileSet[0][0]->setPosition(this->colPosXOne, this->rowPosYOne);
	this->backgroundTileSet[0][1]->setPosition(this->colPosXTwo, this->rowPosYOne);
	this->backgroundTileSet[0][2]->setPosition(this->colPosXThree, this->rowPosYOne);
	//---ROW ONE---//
	//===ROW TWO===//
	this->backgroundTileSet[1][0]->setPosition(this->colPosXOne, this->rowPosYTwo);
	this->backgroundTileSet[1][1]->setPosition(this->colPosXTwo, this->rowPosYTwo);
	this->backgroundTileSet[1][2]->setPosition(this->colPosXThree, this->rowPosYTwo);
	//---ROW TWO---//
	//===ROW THREE===//
	this->backgroundTileSet[2][0]->setPosition(this->colPosXOne, this->rowPosYThree);
	this->backgroundTileSet[2][1]->setPosition(this->colPosXTwo, this->rowPosYThree);
	this->backgroundTileSet[2][2]->setPosition(this->colPosXThree, this->rowPosYThree);
	//---ROW THREE---//
}

void GSTileSet::render(sf::RenderTarget* target)
{
	for (auto& i : this->backgroundTileSet)
	{
		for (auto& j : i)
		{
			target->draw(*j);
		}
	}
}
