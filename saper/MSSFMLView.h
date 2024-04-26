#ifndef SAPER_MSSFMLVIEW_H
#define SAPER_MSSFMLVIEW_H
#include "MinesweeperBoard.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <cmath>

class MSSFMLView {

    MinesweeperBoard &board;

    int window_width, window_height;
    int height, width;
    double tile_size, spacing, left_offset, top_offset, tile_frame;
    int text_left_offset, text_top_offset;
    int bomb_size, bomb_offset;
    int flag_size, flag_triangles_offset, flag_offset_w, flag_offset_h;
    int game_state_size;
    std::string tile_text;
    sf::Font font;
    sf::RectangleShape rectangle;
    sf::Text text;

public:
    MSSFMLView(MinesweeperBoard &);

    // Simple getters
    int getWindowHeight() const;
    int getWindowWidth() const;
    double getTopOffset() const;
    double getLeftOffset() const;

    // function returns space between start of one tile and start of second tile
    double tileLength() const;

    // Function draws one frame on the window
    void draw(sf::RenderWindow &);
};

#endif //SAPER_MSSFMLVIEW_H
