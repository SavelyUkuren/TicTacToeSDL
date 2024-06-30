//
//  TicTacToeLogic.hpp
//  TicTacToe
//
//  Created by Савелий Никулин on 30.06.2024.
//

#ifndef TicTacToeLogic_hpp
#define TicTacToeLogic_hpp

#include <iostream>

using namespace std;

enum TicTacToeSymbol: int {
    X, O, none
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
    
public:
    void setSymbol(TicTacToeSymbol symbol, int x, int y);
    void printField();
    void reset();
    
    TicTacToeSymbol &getWinner();
    Stats &getStats();
    
private:
    void checkWinner();
    void updateStats();
};

#endif /* TicTacToeLogic_hpp */
