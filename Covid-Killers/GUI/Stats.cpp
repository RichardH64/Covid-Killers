#include "Stats.h"

Stats::Stats(float* time, double* score, int* kills)
{
    this->time = time;
    this->score = score;
    this->kills = kills;
    this-fontConnectionII.loadFromFile("Assets/Fonts/ConnectionIi-2wj8.otf");

    this->textTime.setFont(this->fontConnectionII);
	this->textTime.setCharacterSize(32);
	this->textTime.setStyle(sf::Text::Bold);
	this->textTime.setString("Time: 0:00");
	this->textTime.setLetterSpacing(1.1f);

    this->textScore.setFont(this->fontConnectionII);
	this->textScore.setCharacterSize(32);
	this->textScore.setStyle(sf::Text::Bold);
	this->textScore.setString("Score: 0");
	this->textScore.setLetterSpacing(1.1f);

    this->textKills.setFont(this->fontConnectionII);
	this->textKills.setCharacterSize(32);
	this->textKills.setStyle(sf::Text::Bold);
	this->textKills.setString("Kills: 0");
	this->textKills.setLetterSpacing(1.1f);
}

Stats::~Stats()
{

}