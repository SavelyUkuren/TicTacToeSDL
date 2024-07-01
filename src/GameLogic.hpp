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
#include <vector>
#include <iostream>

#include "object.h"
#include "users.h"
#include "math/point.h"
#include "TicTacToeLogic.hpp"

using namespace std;

class GameLogic {
    
    int screenWidth, screenHeight = 0;
    
    SDL_Window *window;
    SDL_Renderer *render;
    SDL_Event event;
    
    bool isGameOpen = false;
    bool isGameOver = false;
    
    Uint32 startTime, endTime = 0;
    float delta = 0;
    
    const int frameTime = 1 / 30;
    
    const float rectSize = 120;
    vector<object> rectsOfField;
    
    users currentUser = ::player;
    TicTacToeLogic ticTacToeLogic;
    
    vector<point> winLinePoints;
    
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
