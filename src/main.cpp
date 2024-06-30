#include <iostream>
#include <vector>
#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>

#include "TicTacToeLogic.hpp"

using namespace std;

#define FPS 60

int main()
{
    TicTacToeLogic logic;
    logic.setSymbol(TicTacToeSymbol::X, 0, 0);
    logic.setSymbol(TicTacToeSymbol::X, 1, 0);
    logic.setSymbol(TicTacToeSymbol::X, 2, 0);
    logic.printField();
    
    
    return 0;
    SDL_Init(SDL_INIT_VIDEO);

    SDL_Window *window = SDL_CreateWindow(
        "TicTacToe",
        SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED,
        640,
        480,
        0
        );

    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_SOFTWARE);
    
    Uint32 startTime = SDL_GetTicks();
    Uint32 endTime = 0;
    float delta = 0;
    bool isquit = false;
    SDL_Event event;
    while (!isquit) {
        startTime = SDL_GetTicks();
        delta = (float)(startTime - endTime) / 1000;
        
        while (SDL_PollEvent(&event)) {
            switch (event.type)
            {
            case SDL_QUIT:
                isquit = true;
                break;
            }
        }
        
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);



        
        SDL_RenderPresent(renderer);
        SDL_Delay(1 / FPS);
        endTime = startTime;
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
