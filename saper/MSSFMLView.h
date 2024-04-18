#ifndef SAPER_MSSFMLVIEW_H
#define SAPER_MSSFMLVIEW_H
#include "MinesweeperBoard.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <cmath>

class MSSFMLView {

    MinesweeperBoard board;

    int window_width, window_height;
    int height, width;
    double tile_size, spacing, left_offset, top_offset, tile_frame;
    int text_left_offset, text_top_offset;
    int tile_press_row, tile_press_col;
    std::string tile_text;

public:
    MSSFMLView(MinesweeperBoard &);
    int getWindowHeight() const;
    int getWindowWidth() const;
    void draw(sf::RenderWindow &);

};


#endif //SAPER_MSSFMLVIEW_H