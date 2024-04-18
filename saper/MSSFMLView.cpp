#include "MSSFMLView.h"

MSSFMLView::MSSFMLView(MinesweeperBoard &b) : board(b)
{
    window_width = 800, window_height = 600;
    height = board.getBoardHeight();
    width = board.getBoardWidth();
    tile_size = 50, spacing = 3, left_offset = 10, top_offset = 10, tile_frame = 3;
    text_left_offset = 13, text_top_offset = 5;
    tile_press_row = -1, tile_press_col = -1;
    tile_text = "";
}

int MSSFMLView::getWindowHeight() const
{
    return window_height;
}

int MSSFMLView::getWindowWidth() const
{
    return window_width;
}

void MSSFMLView::draw(sf::RenderWindow &window)
{
    // Wycentrowanie planszy
    left_offset = (window_width - (width*(tile_size + (tile_frame * 2)+ spacing))) / 2;
    top_offset = (window_height - (height*(tile_size + (tile_frame * 2)+ spacing))) / 2;

    // Zabezpieczenie przed ustawieniem zbyt dużej planszy
    if(left_offset < 0 || top_offset < 0){
        std::cout << "Window too small to display board" << std::endl;
        window.close();
    }

    // create rectangle object
    sf::RectangleShape rectangle(sf::Vector2f(tile_size, tile_size));

    rectangle.setFillColor(sf::Color(220, 220, 220));
    rectangle.setOutlineThickness(tile_frame);
    rectangle.setOutlineColor(sf::Color(120, 120, 120));



    // Load a font
    sf::Font font;
    if(!font.loadFromFile("../arial.ttf")) {
//        return EXIT_FAILURE;
    }

    // Create a text object
    sf::Text text;
    text.setFont(font);
    text.setStyle(sf::Text::Bold);
    text.setCharacterSize(tile_size - (2 * text_top_offset));
    text.setFillColor(sf::Color(200, 0, 0));


/*
    // map a 100x100 textured rectangle to the shape
    shape.setTexture(&texture); // texture is a sf::Texture
    shape.setTextureRect(sf::IntRect(10, 10, 100, 100));
*/
    // run the program as long as the window is open
/*    while(window.isOpen())
    {
        // check all the window's events that were triggered since the last iteration of the loop
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
*/
        // clear the window with black color
        window.clear(sf::Color::Black);

        // draw everything here...
        for(int row = 0; row < width; row++){
            for(int col = 0; col < height; col++){
                rectangle.setPosition(col * (tile_size + spacing + (tile_frame * 2)) + left_offset, row * (tile_size + spacing + (tile_frame * 2)) + top_offset);

                tile_text = board.getFieldInfo(row, col);
                text.setString(tile_text);
                text.setPosition(col * (tile_size + spacing + (tile_frame * 2)) + left_offset + text_left_offset, row * (tile_size + spacing + (tile_frame * 2)) + top_offset);

                window.draw(rectangle);
                window.draw(text);
            }
        }


        // end the current frame
        window.display();
//    }
}