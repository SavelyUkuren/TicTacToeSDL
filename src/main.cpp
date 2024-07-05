#include <iostream>

#include "GameLogic.hpp"
#include "TicTacToeLogic.hpp"

using namespace std;

int main()
{
    std::srand(static_cast<unsigned int>(std::time(0)));
    TTF_Init();

    GameLogic gameLogic(640, 480);
    gameLogic.StartGame();

    TTF_Quit();
    return 0;
}
