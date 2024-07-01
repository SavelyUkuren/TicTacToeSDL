//
//  rect.cpp
//  TicTacToe
//
//  Created by Савелий Никулин on 30.06.2024.
//

#include <stdio.h>
#include <string>

struct object {
    int id;
    float x;
    float y;
    float width;
    float height;
    
    bool isInteract(float x, float y) {
        if (x > this->x && x < this->x + width &&
            y > this->y && y < this->y + height) {
            return true;
        }
        return false;
    }
};
