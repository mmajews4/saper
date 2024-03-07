#include <iostream>
#include "Array2D.h"

using namespace std;

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
    MinesweeperBoard(int = 5, int = 7);
    void debug_display() const;
};

MinesweeperBoard::MinesweeperBoard(int w, int h) {

    width = w;
    height = h;
    board.resize(height,width);

    for(int row = 0; row < height; row++){
        for(int col = 0; col < width; col++){
            board[row][col] = {0, 0, 0};
        }
    }

    board[0][0] = {1, 0, 0};
    board[1][1] = {0, 0, 1};
    board[0][2] = {1, 1, 0};
}

void MinesweeperBoard::debug_display() const {
    cout << " ";
    for(int col = 0; col < width; col++){
        cout << "   " << col << "  ";
    }
    cout << endl;


    for(int row = 0; row < height; row++){
        cout << row;
        for(int col = 0; col < width; col++){
            cout << " [";\

            if(board[row][col].hasMine){
                cout << "M";
            } else {
                cout << ".";
            }

            if(board[row][col].isRevealed){
                cout << "o";
            } else {
                cout << ".";
            }

            if(board[row][col].hasFlag){
                cout << "f";
            } else {
                cout << ".";
            }

            cout << "]";
        }
        cout << endl;
    }
}

int main() {

    MinesweeperBoard board {5, 7};

    board.debug_display();

    return 0;
}
