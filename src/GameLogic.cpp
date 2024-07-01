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
    
    
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            object r { 0, (float)j * rectSize, (float)i * rectSize, rectSize, rectSize };
            rectsOfField.push_back(r);
        }
    }
    
    // Centering field on screen
    float startX = (screenWidth / 2);
    float startY = (screenHeight / 2);
    for (int i = 0; i < rectsOfField.size(); i++) {
        rectsOfField[i].x += startX - (rectSize * 3) / 2;
        rectsOfField[i].y += startY - (rectSize * 3) / 2;
    }
    
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
                isGameOver = false;
                ticTacToeLogic.reset();
                currentUser = ::player;
                for (int i = 0; i < rectsOfField.size(); i++) {
                    rectsOfField[i].id = 0;
                }
            }
        }
        
        if (event.type == SDL_MOUSEBUTTONUP) {
            int x, y;
            SDL_GetMouseState(&x, &y);
            if (!isGameOver) {
                for (int i = 0; i < rectsOfField.size(); i++) {
                    if (rectsOfField[i].isInteract(x, y)
                        && ticTacToeLogic.getFieldSymbol(i) == ::none) {
                        if (currentUser == ::player) {
                            rectsOfField[i].id = 1; // 1 = X
                            ticTacToeLogic.setSymbol(::X, i);
                            currentUser = ::computer;
                        }
                        else {
                            rectsOfField[i].id = 2; // 2 = O
                            ticTacToeLogic.setSymbol(::O, i);
                            currentUser = ::player;
                        }
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
//    if (ticTacToeLogic.getWinner() == ::X) {
//        cout << "X win" << endl;
//    } else if (ticTacToeLogic.getWinner() == ::O) {
//        cout << "O win" << endl;
//    }
    
    if (ticTacToeLogic.getWinner() != none) {
        isGameOver = true;
        point p1 {0, 0};
        point p2 {0, 0};
        if (ticTacToeLogic.getWinType() == hor0 ||
            ticTacToeLogic.getWinType() == hor1 ||
            ticTacToeLogic.getWinType() == hor2) {
            
            object *o = nullptr;
            if (ticTacToeLogic.getWinType() == hor0)
                o = &rectsOfField[0];
            if (ticTacToeLogic.getWinType() == hor1)
                o = &rectsOfField[3];
            if (ticTacToeLogic.getWinType() == hor2)
                o = &rectsOfField[6];
            
            p1 = {
                o->x,
                o->y + o->height / 2
            };
            
            p2 = {
                o->x + (o->width * 3),
                o->y + o->height / 2
            };
            
        } else if (ticTacToeLogic.getWinType() == ver0 ||
                   ticTacToeLogic.getWinType() == ver1 ||
                   ticTacToeLogic.getWinType() == ver2) {
            
            object *o = nullptr;
            if (ticTacToeLogic.getWinType() == ver0)
                o = &rectsOfField[0];
            if (ticTacToeLogic.getWinType() == ver1)
                o = &rectsOfField[1];
            if (ticTacToeLogic.getWinType() == ver2)
                o = &rectsOfField[2];
            
            p1 = {
                o->x + o->width / 2,
                o->y
            };
            
            p2 = {
                o->x + o->width / 2,
                o->y + o->height * 3
            };
            
        } else if (ticTacToeLogic.getWinType() == diag0) {
            object *o = &rectsOfField[0];
            p1 = {
                o->x,
                o->y
            };
            
            p2 = {
                o->x + o->width * 3,
                o->y + o->height * 3
            };
        } else if (ticTacToeLogic.getWinType() == diag1) {
            object *o = &rectsOfField[2];
            p1 = {
                o->x + o->width,
                o->y
            };
            
            p2 = {
                o->x + o->width - o->width * 3,
                o->y + o->height * 3
            };
        }
        
        winLinePoints.push_back(p1);
        winLinePoints.push_back(p2);
    }
    
}

void GameLogic::draw() {
    
    for (int i = 0; i < rectsOfField.size(); i++) {
        SDL_FRect r = {
            rectsOfField[i].x,
            rectsOfField[i].y,
            rectsOfField[i].width,
            rectsOfField[i].height
        };
        
        SDL_SetRenderDrawColor(render, 255, 0, 0, 255);
        SDL_RenderDrawRectF(render, &r);
        
        if (rectsOfField[i].id == 1) {
            SDL_SetRenderDrawColor(render, 255, 0, 0, 255);
            SDL_RenderDrawLineF(render,
                                r.x, r.y, r.x + r.w, r.y + r.h);
            SDL_RenderDrawLineF(render,
                                r.x + r.w, r.y, r.x, r.y + r.h);
        }
        
        if (rectsOfField[i].id == 2) {
            SDL_SetRenderDrawColor(render, 255, 0, 0, 255);
            float zeroSize = rectSize - 40;
            SDL_FRect zero {
                r.x + (r.w / 2) - zeroSize / 2,
                r.y + (r.h / 2) - zeroSize / 2,
                rectSize - 40,
                rectSize - 40
            };
            SDL_RenderDrawRectF(render, &zero);
        }
        
    }
    
    if (ticTacToeLogic.getWinner() != ::none) {
        SDL_SetRenderDrawColor(render, 0, 255, 0, 255);
        
        if (winLinePoints.size() >= 2) {
            for (int j = 0; j < winLinePoints.size() - 1; j++) {
                SDL_RenderDrawLineF(render,
                                    winLinePoints[j].x,
                                    winLinePoints[j].y,
                                    winLinePoints[j + 1].x,
                                    winLinePoints[j + 1].y);
            }
        }
        
        winLinePoints.clear();
    }
    
    SDL_SetRenderDrawColor(render, 0, 255, 0, 255);
    SDL_RenderDrawPoint(render, screenWidth / 2, screenHeight / 2);
    
    SDL_RenderPresent(render);
    SDL_Delay(frameTime);
}

GameLogic::~GameLogic() {
    SDL_DestroyRenderer(render);
    SDL_DestroyWindow(window);
    SDL_Quit();
}
