#ifndef STATS_H
#define STATS_H

#include "../Includes.h"

class Stats
{
private:
	float* time;
	double* score;
	int* kills;

    sf::Font fontConnectionII;
    sf::Text textTime;
    sf::Text textScore;
    sf::Text textKills;

	float x, y, w, l;

	sf::RectangleShape back, front;
public:
	Stats(float* time, double* score, int* kills);
	virtual ~Stats();

    void updateText();
	void update();
	void render(sf::RenderTarget* target);
};

#endif