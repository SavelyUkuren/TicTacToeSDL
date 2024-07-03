//
//  Field.cpp
//  TicTacToe
//
//  Created by Савелий Никулин on 02.07.2024.
//

#include "Field.hpp"

Field::Field() {}

Field::Field(SDL_Renderer *render,
             float x,
             float y,
             float width,
             float height) {
    
    this->render = render;
    this->x = x;
    this->y = y;
    this->width = width;
    this->height = height;
    
    fieldNode = Node();
    fieldNode.setName("Field");
    fieldNode.setPosition(x, y);
    fieldNode.setSize(width, height);
    
    int index = 0;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            Node s = Node();
            float nW = width / 3;
            float nH = height / 3;
            s.setPosition(x + (float)j * nW, y + (float)i * nH);
            s.setSize(nW, nH);
            s.setName(to_string(index));
            index++;
            fieldNode.addNode(&s);
        }
    }
}

void Field::logic() {
    
    if (ticTacToeLogic->getWinner() != none && !isWin) {
        isWin = true;
        
        Node n = Node();
        if (ticTacToeLogic->getWinType() == hor0 ||
            ticTacToeLogic->getWinType() == hor1 ||
            ticTacToeLogic->getWinType() == hor2) {
            
            if (ticTacToeLogic->getWinType() == hor0)
                n = fieldNode.getNodeByName("0");
            if (ticTacToeLogic->getWinType() == hor1)
                n = fieldNode.getNodeByName("3");
            if (ticTacToeLogic->getWinType() == hor2)
                n = fieldNode.getNodeByName("6");
            
            winLineStart.setName("WinLineStart");
            winLineStart.setPosition(n.getX(), n.getY() + n.getH() / 2);
            
            winLineEnd.setName("WinLineEnd");
            winLineEnd.setPosition(n.getX() + (n.getW() * 3), n.getY() + n.getH() / 2);
            
        }
        else if (ticTacToeLogic->getWinType() == ver0 ||
                 ticTacToeLogic->getWinType() == ver1 ||
                 ticTacToeLogic->getWinType() == ver2) {
            
            if (ticTacToeLogic->getWinType() == ver0)
                n = fieldNode.getNodeByName("0");
            if (ticTacToeLogic->getWinType() == ver1)
                n = fieldNode.getNodeByName("1");
            if (ticTacToeLogic->getWinType() == ver2)
                n = fieldNode.getNodeByName("2");
            
            winLineStart.setName("WinLineStart");
            winLineStart.setPosition(n.getX() + n.getW() / 2,
                                     n.getY());
            
            winLineEnd.setName("WinLineEnd");
            winLineEnd.setPosition(n.getX() + n.getW() / 2,
                                   n.getY() + n.getH() * 3);
            
        } else if (ticTacToeLogic->getWinType() == diag0) {
            n = fieldNode.getNodeByName("0");
            
            winLineStart.setName("WinLineStart");
            winLineStart.setPosition(n.getX(),
                                     n.getY());
            
            winLineEnd.setName("WinLineEnd");
            winLineEnd.setPosition(n.getX() + n.getW() * 3,
                                   n.getY() + n.getH() * 3);
            
        } else if (ticTacToeLogic->getWinType() == diag1) {
            n = fieldNode.getNodeByName("2");
            
            winLineStart.setName("WinLineStart");
            winLineStart.setPosition(n.getX() + n.getW(),
                                     n.getY());
            
            winLineEnd.setName("WinLineEnd");
            winLineEnd.setPosition(n.getX() + n.getW() - n.getW() * 3,
                                   n.getY() + n.getH() * 3);
            
        }
    }
}

void Field::draw() {
    
    // Draw field
    for (Node &fNode : fieldNode.getNodes()) {
        SDL_SetRenderDrawColor(render, 255, 0, 0, 255);
        
        SDL_FRect r {
            fNode.getX(),
            fNode.getY(),
            fNode.getW(),
            fNode.getH()
        };
        SDL_RenderDrawRectF(render, &r);
    }
    
    // Draw symbols X or O
    for (Node &sNode : symbols) {
        float x = sNode.getX();
        float y = sNode.getY();
        float w = sNode.getW();
        float h = sNode.getH();
        
        SDL_SetRenderDrawColor(render, 255, 0, 0, 255);
        
        if (sNode.getName() == "X") {
            SDL_RenderDrawLineF(render,
                                x, y, x + w, y + h);
            SDL_RenderDrawLineF(render,
                                x + w, y, x, y + h);
        } else if (sNode.getName() == "O") {
            float zeroSize = (width / 3) - 40;
            SDL_FRect zero {
                x + (w / 2) - zeroSize / 2,
                y + (h / 2) - zeroSize / 2,
                (width / 3) - 40,
                (height / 3) - 40
            };
            SDL_RenderDrawRectF(render, &zero);
        }
    }
    
    // Draw win line
    SDL_SetRenderDrawColor(render, 0, 255, 0, 255);
    SDL_RenderDrawLine(render,
                       winLineStart.getX(),
                       winLineStart.getY(),
                       winLineEnd.getX(),
                       winLineEnd.getY());
    
}

void Field::clear() {
    symbols.clear();
    isWin = false;
    winLineStart.setPosition(-1, -1);
    winLineEnd.setPosition(-1, -1);
}

Node *Field::interactWithCell(int x, int y) {
    for (Node &n : fieldNode.getNodes()) {
        if (n.isInteract(x, y))
            return &n;
    }
    return nullptr;
}

void Field::drawSymbol(TicTacToeSymbol symbol, Node *node) {
    
    Node newSymbolNode = Node();
    newSymbolNode.setPosition(node->getX(), node->getY());
    newSymbolNode.setSize(node->getW(), node->getH());
    
    switch (symbol) {
    case X:
        newSymbolNode.setName("X");
        break;
    case O:
        newSymbolNode.setName("O");
        break;
        case none:
            break;
    }
    
    // Check for dublicates
    for (Node &sNode : symbols) {
        if (newSymbolNode == sNode)
            return;
    }
    
    symbols.push_back(newSymbolNode);
}

void Field::setTicTacToeLogic(TicTacToeLogic *ticTacToeLogic) {
    this->ticTacToeLogic = ticTacToeLogic;
}
