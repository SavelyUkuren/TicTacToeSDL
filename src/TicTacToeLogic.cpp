//
//  TicTacToeLogic.cpp
//  TicTacToe
//
//  Created by Савелий Никулин on 30.06.2024.
//

#include "TicTacToeLogic.hpp"


void TicTacToeLogic::setSymbol(TicTacToeSymbol symbol, int x, int y) {
    if (x < 0 || x > 2) {
        cerr << "Error. 'X' Position must be from 0 to 2." << endl;
        return;
    }
    if (y < 0 || y > 2) {
        cerr << "Error. 'Y' Position must be from 0 to 2." << endl;
        return;
    }
    
    field[y * 3 + x] = symbol;
    checkWinner();
    updateStats();
}

void TicTacToeLogic::printField() {
    int index = 0;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (field[index] == TicTacToeSymbol::X)
                cout << "X ";
            if (field[index] == TicTacToeSymbol::O)
                cout << "O ";
            if (field[index] == TicTacToeSymbol::none)
                cout << "- ";
            
            index++;
        }
        cout << endl;
    }
}

void TicTacToeLogic::checkWinner() {
    // Check horizontal
    if (field[0] == field[1] && field[1] == field[2]) {
        winner = field[0];
        return;
    }
    if (field[3] == field[4] && field[4] == field[5]) {
        winner = field[3];
        return;
    }
    if (field[6] == field[7] && field[7] == field[8]) {
        winner = field[6];
        return;
    }
    
    // Check vertical
    if (field[0] == field[3] && field[3] == field[6]) {
        winner = field[0];
        return;
    }
    if (field[1] == field[4] && field[4] == field[7]) {
        winner = field[1];
        return;
    }
    if (field[2] == field[5] && field[5] == field[8]) {
        winner = field[2];
        return;
    }
    
    //Check diagonal
    if (field[0] == field[4] && field[4] == field[8]) {
        winner = field[0];
        return;
    }
    if (field[2] == field[4] && field[4] == field[6]) {
        winner = field[2];
        return;
    }
}

void TicTacToeLogic::updateStats() {
    if (winner == ::X)
        stats.xCount++;
    else if (winner == ::O)
        stats.oCount++;
}

void TicTacToeLogic::reset() {
    for (int i = 0; i < 9; i++) {
        field[i] = ::none;
    }
    winner = ::none;
}

TicTacToeSymbol &TicTacToeLogic::getWinner() {
    return winner;
}

TicTacToeLogic::Stats &TicTacToeLogic::getStats() {
    return stats;
}
