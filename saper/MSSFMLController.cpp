#include "MSSFMLController.h"

MSSFMLController::MSSFMLController()
{

}
/*
void MSSFMLController::play()
{
    sf::Event event;
        while(window.pollEvent(event))
        {
            // "close requested" event: we close the window
            if(event.type == sf::Event::Closed)
                window.close();
            else if(event.type == sf::Event::MouseButtonPressed)
            {
                // calculate on wich tile action was taken, floor to not count -0.xx as 0
                tile_press_col = floor((event.mouseButton.x - left_offset)/(tile_size + spacing + (tile_frame * 2)));
                tile_press_row = floor((event.mouseButton.y - top_offset)/(tile_size + spacing + (tile_frame * 2)));

                if(!(tile_press_col >= 0 && tile_press_col < width && tile_press_row >= 0 && tile_press_row < height))
                {
                    std::cout << "Press out of board" << std::endl;
                }
                else if(event.mouseButton.button == sf::Mouse::Left)
                {
                    std::cout << "Reveal (" << tile_press_col << "," << tile_press_row << ")" << std::endl;
                }
                else if(event.mouseButton.button == sf::Mouse::Right)
                {
                    std::cout << "Place flag (" << tile_press_col << "," << tile_press_row << ")" << std::endl;
                }
            }
        }
}*/