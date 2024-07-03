//
//  GameLogic.cpp
//  TicTacToe
//
//  Created by Савелий Никулин on 30.06.2024.
//

#include "GameLogic.hpp"
#include <functional>
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

    gameState = menu;

    field = new Field(render,
                      screenWidth / 2 - fieldSize / 2,
                      screenHeight / 2 - fieldSize / 2,
                      fieldSize, fieldSize);
    field->setTicTacToeLogic(&ticTacToeLogic);

    mainMenu = new Menu(render,
        screenWidth / 2 - 300 / 2,
        screenHeight / 2 - 100 / 2,
        300, 100);
    mainMenu->setGameState(&gameState);

    rootNode = Node();
    rootNode.setName("rootNode");
    rootNode.setPosition(0, 0);
    rootNode.setSize(screenWidth, screenHeight);

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
        if (event.type == SDL_QUIT)
            isGameOpen = false;

        if (event.type == SDL_KEYUP) {
            if (event.key.keysym.sym == SDLK_r) {
                resetGame();
            }
            if (event.key.keysym.sym == SDLK_ESCAPE) {
                gameState = menu;
                resetGame();
            }
        }

        if (gameState == menu) {
            mainMenu->eventController(event);
        } else if (gameState == game) {
            if (event.type == SDL_MOUSEBUTTONUP) {
                int x, y;
                SDL_GetMouseState(&x, &y);

                if (!isGameOver) {
                    Node *n = field->interactWithCell(x, y);
                    int index = stoi(n->getName());

                    if (n != nullptr && ticTacToeLogic.getFieldSymbol(index) == none) {
                        if (currentUser == player) {
                            ticTacToeLogic.setSymbol(X, index);
                            field->drawSymbol(X, n);
                            currentUser = computer;
                        } else {
                            ticTacToeLogic.setSymbol(O, index);
                            field->drawSymbol(O, n);
                            currentUser = player;
                        }

                    }

                    if (ticTacToeLogic.getWinner() != none) {
                        isGameOver = true;
                    }
                }
            }
        }

    }
}

void GameLogic::clearScreen() {
    SDL_SetRenderDrawColor(render, 0, 0, 0, 255);
    SDL_RenderClear(render);
}

void GameLogic::logic() {
    if (gameState == menu) {
        mainMenu->logic();
    } else if (gameState == game) {
        field->logic();
    }
}

void GameLogic::draw() {
    
    if (gameState == menu) {
        
        mainMenu->draw();
        
    } else if (gameState == game) {
        
        field->draw();
        
        for (Node &node : rootNode.getNodes()) {
            SDL_SetRenderDrawColor(render, 0, 255, 0, 255);
            
            SDL_FRect r {
                node.getX(),
                node.getY(),
                node.getW(),
                node.getH()
            };
            SDL_RenderDrawRectF(render, &r);
        }
        
    }
    
    SDL_SetRenderDrawColor(render, 0, 255, 0, 255);
    SDL_RenderDrawPoint(render, screenWidth / 2, screenHeight / 2);
    
    SDL_RenderPresent(render);
    SDL_Delay(frameTime);
}

GameLogic::~GameLogic() {
    field = nullptr;
    mainMenu = nullptr;
    
    SDL_DestroyRenderer(render);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

void GameLogic::resetGame() {
    isGameOver = false;
    ticTacToeLogic.reset();
    currentUser = ::player;
    field->clear();
}
