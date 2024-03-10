#include "MinesweeperBoard.h"

using namespace std;

MinesweeperBoard::MinesweeperBoard() {

    width = 5;
    height = 7;
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


MinesweeperBoard::MinesweeperBoard(int w, int h, GameMode mode) {

    width = w;
    height = h;

    float procent_of_mines;

    if(mode == EASY){
        procent_of_mines = 0.1;
    } else if(mode == NORMAL){
        procent_of_mines = 0.2;
    } else if(mode == HARD){
        procent_of_mines = 0.3;
    }

    board.resize(height,width);

    for(int row = 0; row < height; row++){
        for(int col = 0; col < width; col++){
            board[row][col] = {0, 0, 0};
        }
    }
    
    // Generacja losowej liczby
    random_device dev;
    mt19937 rng(dev());
    uniform_int_distribution<mt19937::result_type> rand_width(0, width-1);
    uniform_int_distribution<mt19937::result_type> rand_height(0, height-1);

    if(mode == DEBUG){
        for(int diagonal = 0; diagonal < 4; diagonal++){
            board[diagonal][diagonal].hasMine = 1;
        }
        for(int col = 0; col < width; col++){
            board[0][col].hasMine = 1;
        }
        for(int row = 0; row < height; row=row+2){
            board[row][0].hasMine = 1;
        }
    } 
    else
    {
        int mines_to_place = ceil(width*height*procent_of_mines);
        
        while(mines_to_place > 0)
        {
            int col = rand_width(rng);
            int row = rand_height(rng);

            if(board[row][col].hasMine == 0){
                mines_to_place--;
            }
            board[row][col].hasMine = 1;
        }
    }
}

void MinesweeperBoard::debug_display() const {
    for(int col = 0; col < width; col++){
        cout << setw(6) << col;
    }
    cout << endl;

    for(int row = 0; row < height; row++){
        cout << setw(2) << row;
        for(int col = 0; col < width; col++){
            cout << " [";

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
