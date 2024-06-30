//
//  GameLogic.hpp
//  TicTacToe
//
//  Created by Савелий Никулин on 30.06.2024.
//

#ifndef GameLogic_hpp
#define GameLogic_hpp

#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>

#include <stdio.h>

class GameLogic {
    
    int screenWidth, screenHeight = 0;
    
    SDL_Window *window;
    SDL_Renderer *render;
    SDL_Event event;
    
    bool isGameOpen = false;
    
    Uint32 startTime, endTime = 0;
    float delta = 0;
    
public:
    GameLogic(int screenWidth, int screenHeight);
    
    void StartGame();
    
    ~GameLogic();
    
private:
    void eventController();
    void clearScreen();
    void logic();
    void draw();
};

#endif /* GameLogic_hpp */
