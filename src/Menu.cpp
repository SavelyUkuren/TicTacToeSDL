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

    Node startButton = Node();
    startButton.setName("StartButton");
    startButton.setPosition(x + 0, y + 0);
    startButton.setSize(w, 44);

    buttons.push_back(startButton);
}

void Menu::eventController(SDL_Event &e) {
    int mouseX, mouseY = 0;
    SDL_GetMouseState(&mouseX, &mouseY);

    if (e.type == SDL_MOUSEBUTTONUP) {

        for (Node &button : buttons) {
            if (button.getName() == "StartButton" && button.isInteract(mouseX, mouseY)) {
                *gameState = game;
            }

        }

    }

}

void Menu::logic() {

}

void Menu::draw() {
    for (Node &button : buttons) {
        if (button.getName() == "StartButton") {
            SDL_FRect r{
                button.getX(),
                button.getY(),
                button.getW(),
                button.getH()
            };
            SDL_SetRenderDrawColor(render, 0, 255, 0, 255);
            SDL_RenderDrawRectF(render, &r);
        }

    }
}

void Menu::setGameState(GameState *gameState) {
    this->gameState = gameState;
}
