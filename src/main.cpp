#include <iostream>
#include <vector>
#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>

#include "GameLogic.hpp"
#include "TicTacToeLogic.hpp"

using namespace std;

int main()
{
    GameLogic gameLogic(640, 480);
    gameLogic.StartGame();

    return 0;
}
