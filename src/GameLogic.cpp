//
//  GameLogic.cpp
//  TicTacToe
//
//  Created by Савелий Никулин on 30.06.2024.
//

#include "GameLogic.hpp"

GameLogic::GameLogic(int screenWidth, int screenHeight) {
    this->screenWidth = screenWidth;
    this->screenHeight = screenHeight;
    
    window = SDL_CreateWindow(
                              "TicTacToe",
                              SDL_WINDOWPOS_UNDEFINED,
                              SDL_WINDOWPOS_UNDEFINED,
                              screenWidth,
                              screenHeight,
                              0
                              );
    
    render = SDL_CreateRenderer(window, -1, SDL_RENDERER_SOFTWARE);
    
}

void GameLogic::StartGame() {
    
    isGameOpen = true;
    
    while (isGameOpen) {
        startTime = SDL_GetTicks();
        delta = (float)(startTime - endTime) / 1000;
        
        eventController();
        clearScreen();
        logic();
        draw();
        
        endTime = startTime;
    }
    
}

void GameLogic::eventController() {
    while (SDL_PollEvent(&event)) {
        switch (event.type)
        {
        case SDL_QUIT:
            isGameOpen = false;
            break;
        }
    }
}

void GameLogic::clearScreen() {
    SDL_SetRenderDrawColor(render, 0, 0, 0, 255);
    SDL_RenderClear(render);
}

void GameLogic::logic() {
    
}

void GameLogic::draw() {
    
    
    
    SDL_RenderPresent(render);
    SDL_Delay(frameTime);
}

GameLogic::~GameLogic() {
    SDL_DestroyRenderer(render);
    SDL_DestroyWindow(window);
    SDL_Quit();
}
