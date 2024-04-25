#ifndef SAPER_MSSFMLCONTROLLER_H
#define SAPER_MSSFMLCONTROLLER_H
#include "MinesweeperBoard.h"
#include "MSSFMLView.h"

class MSSFMLController {

    MinesweeperBoard &board;
    MSSFMLView &view;
    int tile_press_row, tile_press_col;

public:
    MSSFMLController(MinesweeperBoard &, MSSFMLView &);

    void play(sf::RenderWindow &);

};


#endif //SAPER_MSSFMLCONTROLLER_H
