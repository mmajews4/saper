#ifndef MINESWEEPERBOARD_H
#define MINESWEEPERBOARD_H

#include "Array2D.h"
#include <iostream>
#include <iomanip>
#include <random>

enum GameMode  { DEBUG, EASY, NORMAL, HARD };

struct Field
{
    bool hasMine;
    bool hasFlag;
    bool isRevealed;
};

class MinesweeperBoard
{
    Array2D<Field> board {5, 7};

    int width;                // rzeczywista szerokość planszy
    int height;               // rzeczywista wysokość planszy

public:
    MinesweeperBoard();
    MinesweeperBoard(int, int, GameMode);
    void debug_display() const;
};

#endif