#ifndef MINESWEEPERBOARD_H
#define MINESWEEPERBOARD_H

#include "Array2D.h"
#include <iostream>
#include <iomanip>
#include <random>

enum GameMode  { DEBUG, EASY, NORMAL, HARD };
enum GameState { RUNNING, FINISHED_WIN, FINISHED_LOSS };

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
    int mineCount;            // ilość min do odkrycia
    int moveCount;
    GameMode mode;
    GameState state;

    // checks if position is outside the board
    bool outsideBoard(int row, int col) const; 

    // Generates mine - for more code readbility
    // returns 1 if succesfully generated
    // returns 0 in not
    bool genMine();

    // Update state such as:
    // - FINISHED_WIN  - if the player won the game (all unrevealed fields have mines)
    // - RUNNING       - if the game is not yet finished 
    void updateGameState();

    // If reveald field minecount is 0, then reveal all fields around it
    void emptyFieldExpansion(int row, int col);

    // Rearranges mines if they are in range of the first move
    void firstMove(int row, int col);

    // Reveal all fields with mines at loss
    void revealMines();

public:
    MinesweeperBoard();
    MinesweeperBoard(int, int, GameMode);

    // Resets board to its starting state
    void restart();

    // simple getters - return appropriate values (passed to or calculated in constructor)
    int getBoardWidth() const;
    int getBoardHeight() const;
    int getMineCount() const;

    // count mines around (row,col) position
    // if the field at (row,col) was not revealed - return -1
    // if either row or col is outside board      - return -1
    // otherwise - return mine count around this field
    int countMines(int row, int col) const;  

    // return true if the field at (row,col) position was marked with flag
    // return false if any of the following is true:
    // - row or col is outside board
    // - there is no flag on the field
    // - field was already revealed
    bool hasFlag(int row, int col) const;

    // if the field at (row,col) was not revealed - change flag status for this field 
    // Do nothing if any of the following is true
    // - field was already revealed
    // - either row or col is outside board
    // - game is already finished
    void toggleFlag(int row, int col);


    // try to reveal the field at (row,col)
    // Do nothing if any of the following is true
    // - field was already revealed
    // - either row or col is outside board
    // - game is already finished
    // - there is a flag on the field
    //
    // If the field was not revealed and there is no mine on it - reveal it
    // If the field was not revealed and there is a mine on it1:  
    // - if its the first player action - move mine to another location, reveal field (not in DEBUG mode!)
    // - reveal it and finish game
    void revealField(int row, int col);

    // return true if the field was revealed
    // return false if the field is not revealed or if it is outside the board
    bool isRevealed(int row, int col) const;

    // return current game state:
    // - FINISHED_LOSS - if the player revealed field with mine
    // - FINISHED_WIN  - if the player won the game (all unrevealed fields have mines)
    // - RUNNING       - if the game is not yet finished 
    GameState getGameState() const;

    // convenience function - returns useful information about field in one function call
    // if row or col is outside board                         - return '#' character
    // if the field is not revealed and has a flag            - return 'F' character
    // if the field is not revealed and does not have a flag  - return '_' (underscore) character
    // if the field is revealed and has mine                  - return 'x' character
    // if the field is revealed and has 0 mines around        - return ' ' (space) character
    // if the field is revealed and has some mines around     - return '1' ... '8' (number of mines as a digit)
    char getFieldInfo(int row, int col) const;
    
    void debug_display() const;
};

#endif