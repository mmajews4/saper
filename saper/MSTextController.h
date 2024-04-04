#ifndef SAPER_MSTEXTCONTROLLER_H
#define SAPER_MSTEXTCONTROLLER_H

#include <iostream>
#include "MinesweeperBoard.h"
#include "MSBoardTextView.h"

enum Action { REVEAL, PLACE_FLAG };

class MSTextController {

    MinesweeperBoard &board;
    MSBoardTextView &view;
    int row;
    int col;
    int action;

public:
    MSTextController(MinesweeperBoard &, MSBoardTextView &);
    void play();
};


#endif //SAPER_MSTEXTCONTROLLER_H
