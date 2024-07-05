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

#include "GameMode.h"
#include "GameState.h"
#include "Node.hpp"

using namespace std;

class Menu {
    
    SDL_Renderer *render;
    float x, y, w, h = 0;

    GameState *gameState;
    GameMode *gameMode;

    vector<Node> buttons;
    TTF_Font *font;
    SDL_Surface *playerVSplayerTextSurface;
    SDL_Texture *playerVSplayerTextTexture;

    SDL_Surface *playerVScomputerTextSurface;
    SDL_Texture *playerVScomputerTextTexture;

public:
    Menu(SDL_Renderer *render,
         float x, float y,
         float w, float h);

    void eventController(SDL_Event &e);
    void logic();
    void draw();

    void setGameState(GameState *gameState);
    void setGameMode(GameMode *gameMode);

    ~Menu();
};

#endif /* Menu_hpp */
