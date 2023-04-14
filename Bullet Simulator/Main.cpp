#include <iostream>

#include "Game.hpp"

int main(int argc, char* argv[])
{
    Game game;

    while (game.GetState() == Game::State::STATE_OK)
    {
        game.Update();
        game.HandleEvents();
        game.DrawAll();
    }

    return 0;
}