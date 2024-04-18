#include "MinesweeperBoard.h"

using namespace std;

MinesweeperBoard::MinesweeperBoard() {

    width = 5;
    height = 7;
    mineCount = 2;
    mode = DEBUG;
    state = RUNNING;
    moveCount = 0;
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


MinesweeperBoard::MinesweeperBoard(int w, int h, GameMode m) {

    width = w;
    height = h;
    mode = m;
    state = RUNNING;
    moveCount = 0;

    double procent_of_mines;

    if(mode == EASY){
        procent_of_mines = 0.1;
    } else if(mode == NORMAL){
        procent_of_mines = 0.2;
    } else if(mode == HARD){
        procent_of_mines = 0.3;
    }
    mineCount = ceil(width*height*procent_of_mines);

    board.resize(height,width);

    for(int row = 0; row < height; row++){
        for(int col = 0; col < width; col++){
            board[row][col] = {0, 0, 0};
        }
    }
    

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
        int mines_placed = 0;
        
        while(mines_placed < mineCount)
        {
            mines_placed = mines_placed + genMine();
        }
    }
}


bool MinesweeperBoard::genMine(){
    // Generacja losowej liczby
    random_device dev;
    mt19937 rng(dev());
    uniform_int_distribution<mt19937::result_type> rand_width(0, width-1);
    uniform_int_distribution<mt19937::result_type> rand_height(0, height-1);

    int col = rand_width(rng);
    int row = rand_height(rng);
    // returns 0 if the place has mine already
    if(board[row][col].hasMine) return false;

    board[row][col].hasMine = true;
    // returns 1 if succesfully generated
    return true;
}


int MinesweeperBoard::getBoardWidth() const {
    return width;
}

int MinesweeperBoard::getBoardHeight() const {
    return height;
}

int MinesweeperBoard::getMineCount() const {
    return mineCount;
}

// return current game state:
// - FINISHED_LOSS - if the player revealed field with mine
// - FINISHED_WIN  - if the player won the game (all unrevealed fields have mines)
// - RUNNING       - if the game is not yet finished
GameState MinesweeperBoard::getGameState() const {
    return state;
}

bool MinesweeperBoard::outsideBoard(int row, int col) const {
    return (row < 0 || row >= height || col < 0 || col >= width);
}

int MinesweeperBoard::countMines(int row, int col) const {

    int mines = 0;

    // if the field at (row,col) was not revealed - return -1
    // if either row or col is outside board      - return -1
    if(outsideBoard(row, col)) return -1;
    if(!board[row][col].isRevealed) return -1;

    for(int row_offset = -1; row_offset <= 1; row_offset++){      // Przejscie po wszystkich polach wokol pola sprawdzanego
        for(int col_offset = -1; col_offset <= 1; col_offset++){  // Zabezpieczenie przed wyjsciem poza plansze (Segmentation faultem)
            if(!(outsideBoard(row + row_offset, col + col_offset))){
//                if(board[row + row_offset][col + col_offset].hasMine)
//                  mines++;
                mines += board[row + row_offset][col + col_offset].hasMine;
            }
        }
    }
    return mines;
}


bool MinesweeperBoard::hasFlag(int row, int col) const {
    // return false if any of the following is true:
    // - row or col is outside board
    // - there is no flag on the field
    // - field was already revealed
    if(outsideBoard(row, col)) return false;
    if(board[row][col].isRevealed || !board[row][col].hasFlag) return false;

    // return true if the field at (row,col) position was marked with flag
    //if(board[row][col].hasFlag) 
    return true;    // theretically doesn't need if statement
}


void MinesweeperBoard::toggleFlag(int row, int col){
    // Do nothing if any of the following is true
    // - field was already revealed
    // - either row or col is outside board
    // - game is already finished
    if(outsideBoard(row, col)) return;
    if(board[row][col].isRevealed) return;
    if(state != RUNNING) return;

    // if the field at (row,col) was not revealed - change flag status for this field 
    board[row][col].hasFlag = 1;
}


void MinesweeperBoard::emptyFieldExpansion(int row, int col){

    if(countMines(row, col) != 0) return;

    for(int row_offset = -1; row_offset <= 1; row_offset++){      // Przejscie po wszystkich polach wokol pola sprawdzanego
        for(int col_offset = -1; col_offset <= 1; col_offset++){  // Zabezpieczenie przed wyjsciem poza plansze (Segmentation faultem)
            if(!(outsideBoard(row + row_offset, col + col_offset))){
                revealField(row + row_offset, col + col_offset);
            }
        }
    }
}


void MinesweeperBoard::updateGameState(){

    for(int row = 0; row < height; row++){
        for(int col = 0; col < width; col++){
            if(!board[row][col].hasMine && !board[row][col].isRevealed) {
                state = RUNNING;
                return;
            }
        }
    }
    state = FINISHED_WIN;
}

// Rearranges mines if they are in range of the first move
void MinesweeperBoard::firstMove(int row, int col){

    if(countMines(row, col) == 0) return;

    for(int row_offset = -1; row_offset <= 1; row_offset++){      // Przejscie po wszystkich polach wokol pola sprawdzanego
        for(int col_offset = -1; col_offset <= 1; col_offset++){  // Zabezpieczenie przed wyjsciem poza plansze (Segmentation faultem)
            if(!(outsideBoard(row + row_offset, col + col_offset))){
                if(board[row + row_offset][col + col_offset].hasMine){

                    while(!genMine()){};    // generates mines untill it succeds
                    board[row + row_offset][col + col_offset].hasMine = false;
                }
            }
        }
    }
    board[row][col].isRevealed = true;
    moveCount++;

    // It tries to rearrange mines until it succeds
    firstMove(row, col);
}


void MinesweeperBoard::revealField(int row, int col){
    // Do nothing if any of the following is true
    // - field was already revealed
    // - either row or col is outside board
    // - game is already finished
    // - there is a flag on the field
    if(outsideBoard(row, col)) return;
    if(board[row][col].isRevealed) return;
    if(state != RUNNING) return;
    if(board[row][col].hasFlag) return;

    // If the field was not revealed and there is no mine on it - reveal it
    if(!board[row][col].hasMine) board[row][col].isRevealed = true;

    // If the field was not revealed and there is a mine on it1:  
    // - if its the first player action - move mine to another location, reveal field (not in DEBUG mode!)
    // - reveal it and finish game
    if(moveCount == 0){
        firstMove(row, col);
    }

    if(moveCount != 0 && board[row][col].hasMine){
        board[row][col].isRevealed = true;
        state = FINISHED_LOSS;
        moveCount++;
        return;
    }

    emptyFieldExpansion(row, col);
    updateGameState();
}


bool MinesweeperBoard::isRevealed(int row, int col) const {
    // return false if the field is not revealed or if it is outside the board
    if(outsideBoard(row, col)) return false;
    if(!board[row][col].isRevealed) return false;
    // return true if the field was revealed
    return true;
}


// convenience function - returns useful information about field in one function call
// if row or col is outside board                         - return '#' character
// if the field is not revealed and has a flag            - return 'F' character
// if the field is not revealed and does not have a flag  - return '_' (underscore) character
// if the field is revealed and has mine                  - return 'x' character
// if the field is revealed and has 0 mines around        - return ' ' (space) character
// if the field is revealed and has some mines around     - return '1' ... '8' (number of mines as a digit)
char MinesweeperBoard::getFieldInfo(int row, int col) const {
    if(outsideBoard(row, col)) return '#';
    if(!board[row][col].isRevealed && board[row][col].hasFlag) return 'F';
    if(!board[row][col].isRevealed && !board[row][col].hasFlag) return '_';
    if(board[row][col].isRevealed && board[row][col].hasMine) return 'x';

    int minesAround = countMines(row, col);

    if(board[row][col].isRevealed && minesAround == 0) return ' ';
    if(board[row][col].isRevealed && minesAround > 0) return ('0' + minesAround);

    // zwróć błąd '%' żeby było bezpieczniej i bo kompliator płacze
    return '%';
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
