#ifndef STATS_H
#define STATS_H

#include "GUI.h"

class Stats : public GUI
{
private:
	float* time;
	double* score;
	int* kills;

    sf::Font fontConnectionII;
    sf::Text textTime;
    sf::Text textScore;
    sf::Text textKills;

	sf::RectangleShape back, front;
public:
	Stats(float x, float y, float w, float l, float* time, double* score, int* kills);
	virtual ~Stats();

    void updateText();
	void update() override;
	void render(sf::RenderTarget* target) override;
};

#endif