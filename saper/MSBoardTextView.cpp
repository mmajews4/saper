#include "MSBoardTextView.h"

using namespace std;

MSBoardTextView::MSBoardTextView( MinesweeperBoard & b ) : board(b)
{

}


void MSBoardTextView::display()
{
    for(int row = 0; row < board.getBoardHeight(); row++){
        for(int col = 0; col < board.getBoardWidth(); col++){
            cout << board.getFieldInfo(row, col) << " ";
        }
        cout << endl;
    }
    cout << endl;
}
