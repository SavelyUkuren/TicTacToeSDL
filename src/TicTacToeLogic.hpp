//
//  TicTacToeLogic.hpp
//  TicTacToe
//
//  Created by Савелий Никулин on 30.06.2024.
//

#ifndef TicTacToeLogic_hpp
#define TicTacToeLogic_hpp

#include <iostream>
#include <vector>

using namespace std;

enum TicTacToeSymbol: int {
    X, O, none
};

enum WinType: int {
    hor0,
    hor1,
    hor2,
    ver0,
    ver1,
    ver2,
    diag0,
    diag1
};

class TicTacToeLogic {
    struct Stats {
        int xCount;
        int oCount;
    };
    
    TicTacToeSymbol field[9] =
    {
        none, none, none,
        none, none, none,
        none, none, none
    };
    
    TicTacToeSymbol winner = TicTacToeSymbol::none;
    Stats stats = {0, 0};
    WinType winType;
    
public:
    void setSymbol(TicTacToeSymbol symbol, int x, int y);
    void setSymbol(TicTacToeSymbol symbol, int index);
    void printField();
    void reset();
    
    TicTacToeSymbol &getWinner();
    Stats &getStats();
    TicTacToeSymbol &getFieldSymbol(int index);
    WinType &getWinType();
    
private:
    void checkWinner();
    void updateStats();
};

#endif /* TicTacToeLogic_hpp */
