//
//  Menu.cpp
//  TicTacToe
//
//  Created by Савелий Никулин on 03.07.2024.
//

#include "Menu.hpp"

Menu::Menu(SDL_Renderer *render, float x, float y, float w, float h) {
    this->render = render;
    this->x = x;
    this->y = y;
    this->w = w;
    this->h = h;

    font = TTF_OpenFont("assets/Cannonade.ttf", 48);

    Node playerVSplayerButton = Node();
    playerVSplayerButton.setName("playerVSplayer");
    playerVSplayerButton.setPosition(x + 0, y + 0);
    playerVSplayerButton.setSize(w, 44);

    Node playerVScomputerButton = Node();
    playerVScomputerButton.setName("playerVScomputer");
    playerVScomputerButton.setPosition(x + 0, y + 52);
    playerVScomputerButton.setSize(w, 44);

    playerVSplayerTextSurface = TTF_RenderText_Solid(font, "Player vs Player", SDL_Color{0, 0, 0, 255});
    playerVSplayerTextTexture = SDL_CreateTextureFromSurface(render, playerVSplayerTextSurface);

    playerVScomputerTextSurface = TTF_RenderText_Solid(font, "Player vs Computer", SDL_Color{0, 0, 0, 255});
    playerVScomputerTextTexture = SDL_CreateTextureFromSurface(render, playerVScomputerTextSurface);

    buttons.push_back(playerVSplayerButton);
    buttons.push_back(playerVScomputerButton);
}

void Menu::eventController(SDL_Event &e) {
    int mouseX, mouseY = 0;
    SDL_GetMouseState(&mouseX, &mouseY);

    if (e.type == SDL_MOUSEBUTTONUP) {

        for (Node &button : buttons) {
            if (button.getName() == "playerVSplayer" && button.isInteract(mouseX, mouseY)) {
                *gameState = game;
                *gameMode = playerVSplayer;
            } else if (button.getName() == "playerVScomputer" && button.isInteract(mouseX, mouseY)) {
                *gameState = game;
                *gameMode = playerVScomputer;
            }

        }

    }

}

void Menu::logic() {

}

void Menu::draw() {
    for (Node &button : buttons) {
        SDL_FRect r{
            button.getX(),
            button.getY(),
            button.getW(),
            button.getH()
        };
        SDL_SetRenderDrawColor(render, 0, 255, 0, 255);
        SDL_RenderDrawRectF(render, &r);

        if (button.getName() == "playerVSplayer") {
            SDL_Rect tRect {
                static_cast<int>(r.x + r.w / 2 - 200 / 2),
                static_cast<int>(r.y + r.h / 2 - 40 / 2),
                200,
                40
            };

            SDL_RenderCopy(render, playerVSplayerTextTexture, nullptr, &tRect);

        } else if (button.getName() == "playerVScomputer") {
            SDL_Rect tRect {
                static_cast<int>(r.x + r.w / 2 - 200 / 2),
                static_cast<int>(r.y + r.h / 2 - 40 / 2),
                230,
                40
            };

            SDL_RenderCopy(render, playerVScomputerTextTexture, nullptr, &tRect);
        }
    }
}

void Menu::setGameState(GameState *gameState) {
    this->gameState = gameState;
}

void Menu::setGameMode(GameMode *gameMode) {
    this->gameMode = gameMode;
}

Menu::~Menu() {
    SDL_FreeSurface(playerVScomputerTextSurface);
    SDL_FreeSurface(playerVSplayerTextSurface);
    TTF_CloseFont(font);

    playerVSplayerTextTexture = nullptr;
    playerVScomputerTextTexture = nullptr;
    font = nullptr;
}
