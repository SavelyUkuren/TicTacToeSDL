//
//  GameLogic.hpp
//  TicTacToe
//
//  Created by Савелий Никулин on 30.06.2024.
//

#ifndef GameLogic_hpp
#define GameLogic_hpp

#include <SDL2/SDL.h>
#include <SDL_ttf.h>
#include <SDL2_image/SDL_image.h>

#include <stdio.h>
#include <vector>
#include <iostream>

#include "users.h"
#include "math/point.h"
#include "TicTacToeLogic.hpp"
#include "Node.hpp"
#include "Field.hpp"
#include "GameMode.h"
#include "GameState.h"
#include "Menu.hpp"

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
    const float frameTime = 1.0f / 30.0f;
    
    users currentUser = ::player;
    TicTacToeLogic ticTacToeLogic;
    
    Node rootNode;
    
    const float fieldSize = 360;
    Field *field;
    
    GameState gameState;
    GameMode gameMode;
    Menu *mainMenu;

    TTF_Font *font;
    SDL_Surface *player1StatsSurface;
    SDL_Texture *player1StatsTexture;

    SDL_Surface *player2StatsSurface;
    SDL_Texture *player2StatsTexture;
    
public:
    GameLogic(int screenWidth, int screenHeight);
    
    void StartGame();
    
    ~GameLogic();
    
private:
    void resetGame();
    void eventController();
    void clearScreen();
    void logic();
    void draw();

    void drawText();
};

#endif /* GameLogic_hpp */
