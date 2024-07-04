//
//  Menu.hpp
//  TicTacToe
//
//  Created by Савелий Никулин on 03.07.2024.
//

#ifndef Menu_hpp
#define Menu_hpp

#include <stdio.h>
#include <iostream>
#include <vector>

#include <SDL2/SDL.h>
#include <SDL_ttf.h>

#include "GameState.h"
#include "Node.hpp"

using namespace std;

class Menu {
    
    SDL_Renderer *render;
    float x, y, w, h = 0;

    GameState *gameState;

    vector<Node> buttons;
    TTF_Font *font;
    SDL_Surface *startGameTextSurface;
    SDL_Texture *startGameTextTexture;

public:
    Menu(SDL_Renderer *render,
         float x, float y,
         float w, float h);

    void eventController(SDL_Event &e);
    void logic();
    void draw();

    void setGameState(GameState *gameState);

    ~Menu();
};

#endif /* Menu_hpp */
