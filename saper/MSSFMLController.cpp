#include "MSSFMLController.h"

MSSFMLController::MSSFMLController(MinesweeperBoard &b, MSSFMLView &v) : board(b), view(v)
{
    tile_press_row = -1, tile_press_col = -1;
}

void MSSFMLController::play(sf::RenderWindow &window)
{
    view.draw(window);

    sf::Event event;
    while(window.pollEvent(event))
    {
        // "close requested" event: we close the window
        if(event.type == sf::Event::Closed)
            window.close();
        else if(event.type == sf::Event::MouseButtonPressed)
        {
            // calculate on wich tile action was taken, floor to not count -0.xx as 0
            tile_press_col = floor((event.mouseButton.x - view.getLeftOffset())/view.tileLength());
            tile_press_row = floor((event.mouseButton.y - view.getTopOffset())/view.tileLength());

            if(!(tile_press_col >= 0 && tile_press_col < board.getBoardWidth() && tile_press_row >= -1 && tile_press_row < board.getBoardHeight()))
            {
            }
            else if(tile_press_row == -1)
            {
                board.restart();
            }
            else if(event.mouseButton.button == sf::Mouse::Left)
            {
                board.revealField(tile_press_row, tile_press_col);
            }
            else if(event.mouseButton.button == sf::Mouse::Right)
            {
                board.toggleFlag(tile_press_row, tile_press_col);
            }
            view.draw(window);
        }
    }
}