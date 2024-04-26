#ifndef SAPER_MSBOARDTEXTVIEW_H
#define SAPER_MSBOARDTEXTVIEW_H

#include "MinesweeperBoard.h"

class MSBoardTextView{

    MinesweeperBoard &board;

public:
    MSBoardTextView( MinesweeperBoard & );

    // Function displays board on serial terminal
    void display();
};

#endif //SAPER_MSBOARDTEXTVIEW_H
