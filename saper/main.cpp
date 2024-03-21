#include <iostream>
#include "Array2D.h"
#include "MinesweeperBoard.h"
#include "MSBoardTextView.h"

using namespace std;

int main() {

    MinesweeperBoard board {9, 9, HARD};

    MSBoardTextView view ( board );
    view.display();
    board.revealField(0,5);
    board.revealField(2,3);
    view.display();

    board.revealField(2,2);
    board.debug_display();

    cout << "Mines count around (2,2): " << board.countMines(2,2) << endl;
    cout << "(2,2) has flag? " << board.hasFlag(2,2) << endl;

    return 0;
}
