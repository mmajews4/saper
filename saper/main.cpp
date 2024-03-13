#include <iostream>
#include "Array2D.h"
#include "MinesweeperBoard.h"

using namespace std;

int main() {

    MinesweeperBoard board {5, 7, HARD};

    board.debug_display();

    cout << "Mines count around (2,2): " << board.countMines(2,2) << endl;
    cout << "(2,2) has flag? " << board.hasFlag(2,2) << endl;

    return 0;
}
