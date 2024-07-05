//
//  Field.hpp
//  TicTacToe
//
//  Created by Савелий Никулин on 02.07.2024.
//

#ifndef Field_hpp
#define Field_hpp

#include <stdio.h>
#include <SDL2/SDL.h>
#include <vector>
#include <iostream>
#include <functional>

#include "TicTacToeLogic.hpp"
#include "Node.hpp"
#include "TicTacToeLogic.hpp"

using namespace std;

class Field {
    
    SDL_Renderer *render;
    float x, y, width, height = 0;
    TicTacToeLogic *ticTacToeLogic;
    
    Node fieldNode;
    vector<Node> symbols;
    
    bool isWin = false;
    Node winLineStart;
    Node winLineEnd;
    
public:
    Field();
    Field(SDL_Renderer *render,
          float x,
          float y,
          float width,
          float height);
    
    void logic();
    void draw();
    
    void clear();
    Node *interactWithCell(int x, int y);
    void drawSymbol(TicTacToeSymbol symbol, Node *node);

    void setTicTacToeLogic(TicTacToeLogic *ticTacToeLogic);
    Node *getNodeByName(string name);
};

#endif /* Field_hpp */
