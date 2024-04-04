#include "MSTextController.h"

using namespace std;

MSTextController::MSTextController(MinesweeperBoard & b, MSBoardTextView & v) : board(b), view(v)
{

}

void MSTextController::play()
{
    view.display();

    while(board.getGameState() == RUNNING) {
        cin >> col >> row >> action;

        switch (action) {
            case REVEAL:
                board.revealField(row, col);
                break;

            case PLACE_FLAG:
                board.toggleFlag(row, col);
                break;

            default:
                cout << "Error: wrong action number" << endl;
                break;
        }
        board.debug_display();
        view.display();
    }
    if(board.getGameState() == FINISHED_WIN){
        cout << "YOU WIN!" << endl;
    } else {
        cout << "YOU LOSE :(" << endl;
    }

}