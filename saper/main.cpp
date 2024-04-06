#include <iostream>
#include "Array2D.h"
#include "MinesweeperBoard.h"
#include "MSBoardTextView.h"
#include "MSTextController.h"

using namespace std;

int main() {

    MinesweeperBoard board (5, 5, GameMode::NORMAL);
    MSBoardTextView view ( board );
    MSTextController ctrl ( board, view );

    ctrl.play();
    return 0;
}
