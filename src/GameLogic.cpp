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

    font = TTF_OpenFont("assets/Cannonade.ttf", 90);

    player1StatsSurface = TTF_RenderText_Solid(font, "X: 0", {0, 0, 0, 255});
    player1StatsTexture = SDL_CreateTextureFromSurface(render, player1StatsSurface);

    player2StatsSurface = TTF_RenderText_Solid(font, "O: 0", {0, 0, 0, 255});
    player2StatsTexture = SDL_CreateTextureFromSurface(render, player1StatsSurface);

    infoSurface = TTF_RenderText_Blended(font, "'r' - Reset game, 'Esc' - menu", {0, 0, 0, 255});
    infoTexture = SDL_CreateTextureFromSurface(render, infoSurface);

    gameState = menu;

    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1");

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
    mainMenu->setGameMode(&gameMode);

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
                ticTacToeLogic.getStats().xCount = 0;
                ticTacToeLogic.getStats().oCount = 0;
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

        if (gameMode == playerVScomputer &&
            currentUser == computer &&
            !isGameOver) {
            int index = rand() % 9;
            while (ticTacToeLogic.getFieldSymbol(index) != none) {
                index = rand() % 9;
            }
            ticTacToeLogic.setSymbol(O, index);
            Node *n = field->getNodeByName(to_string(index));
            field->drawSymbol(O, n);
            currentUser = player;
        }
        if (ticTacToeLogic.getWinner() != none) {
            isGameOver = true;
        }
        field->logic();
    }
}

void GameLogic::draw() {
    SDL_SetRenderDrawColor(render, 255, 255, 255, 255);
    SDL_RenderClear(render);
    
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

        drawText();
    }

    SDL_SetRenderDrawColor(render, 0, 255, 0, 255);
    SDL_RenderDrawPoint(render, screenWidth / 2, screenHeight / 2);
    
    SDL_RenderPresent(render);
    SDL_Delay(frameTime * 1000.0f);
}

void GameLogic::drawText() {
    SDL_Rect p1Rect {
        16, 16, 50, 44
    };

    SDL_Rect p2Rect {
        16, 70, 50, 44
    };

    SDL_Rect infoRect {
        16, screenHeight - 40, 230, 20
    };

    string p1Stat = "X: " + to_string(ticTacToeLogic.getStats().xCount);
    player1StatsSurface = TTF_RenderText_Solid(font, p1Stat.c_str(), {0, 0, 0, 255});
    player1StatsTexture = SDL_CreateTextureFromSurface(render, player1StatsSurface);

    string p2Stat = "O: " + to_string(ticTacToeLogic.getStats().oCount);
    player2StatsSurface = TTF_RenderText_Solid(font, p2Stat.c_str(), {0, 0, 0, 255});
    player2StatsTexture = SDL_CreateTextureFromSurface(render, player2StatsSurface);

    SDL_RenderCopy(render, player1StatsTexture, nullptr, &p1Rect);
    SDL_RenderCopy(render, player2StatsTexture, nullptr, &p2Rect);
    SDL_RenderCopy(render, infoTexture, nullptr, &infoRect);
}

GameLogic::~GameLogic() {
    field = nullptr;
    mainMenu = nullptr;
    font = nullptr;
    player1StatsSurface = nullptr;
    player1StatsTexture = nullptr;
    player2StatsSurface = nullptr;
    player2StatsTexture = nullptr;

    TTF_CloseFont(font);
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
