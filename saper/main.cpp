#include <iostream>
#include "Array2D.h"
#include "MinesweeperBoard.h"

using namespace std;

int main() {

    MinesweeperBoard board {5, 7, HARD};

    board.debug_display();

    return 0;
}
