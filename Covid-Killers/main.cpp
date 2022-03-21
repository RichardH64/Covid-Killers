#include <iostream>

#include "Game.h"

int main()
{
    //Init srand
    std::srand(static_cast<unsigned>(time(NULL)));

    //Init Game Engine
    Game game;

    game.run();

    return 0;
}