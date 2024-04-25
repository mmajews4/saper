#include "MSSFMLView.h"

MSSFMLView::MSSFMLView(MinesweeperBoard &b) : board(b)
{
    window_width = 800, window_height = 600;
    height = board.getBoardHeight();
    width = board.getBoardWidth();
    tile_size = 50, spacing = 3, left_offset = 10, top_offset = 10, tile_frame = 3;
    text_left_offset = 13, text_top_offset = 5;
//    flag_tri_h_offset_1 = 0;
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

double MSSFMLView::tileLength() const
{
    return (tile_size + spacing + (tile_frame * 2));
}

double MSSFMLView::getTopOffset() const
{
    return top_offset;
}

double MSSFMLView::getLeftOffset() const
{
    return left_offset;
}

void MSSFMLView::draw(sf::RenderWindow &window)
{
    // Wycentrowanie planszy
    left_offset = (window_width - (width*(tile_size + (tile_frame * 2)+ spacing))) / 2;
    top_offset = (window_height - (height*(tile_size + (tile_frame * 2)+ spacing))) / 2;

    // Zabezpieczenie przed ustawieniem zbyt dużej planszy
    if(left_offset < 0 || top_offset < 0){
        std::cerr << "Window too small to display board" << std::endl;
        exit(EXIT_FAILURE);
    }

    // create rectangle object
    sf::RectangleShape rectangle(sf::Vector2f(tile_size, tile_size));
    rectangle.setFillColor(sf::Color(220, 220, 220));
    rectangle.setOutlineThickness(tile_frame);
    rectangle.setOutlineColor(sf::Color(120, 120, 120));

    sf::Font font;

    // Create a text object
    sf::Text text;
    text.setFont(font);
    text.setStyle(sf::Text::Bold);
    text.setCharacterSize(tile_size - (2 * text_top_offset));
    text.setFillColor(sf::Color(200, 0, 0));

    // Load a font
    if(!font.loadFromFile("../arial.ttf")) {  // Działa na clionie
        exit(EXIT_FAILURE);
    }
/*    if(!font.loadFromFile("arial.ttf")) {   // Działa na vscodzie
        exit(EXIT_FAILURE);
    }
*/

    // triangle for flag
    sf::CircleShape triangle(10, 3);
    triangle.setFillColor(sf::Color(255, 0, 0));

    // bomb
    sf::CircleShape bomb(13);
    bomb.setFillColor(sf::Color::Black);


    // clear the window with black color
    window.clear(sf::Color::Black);

    // Draw outer frame of the board
    rectangle.setPosition(left_offset, top_offset);
    rectangle.setSize(sf::Vector2f(height * tileLength(), tile_size * width));
    window.draw(rectangle);
    rectangle.setSize(sf::Vector2f(tile_size, tile_size));

    // draw everything here...
    for(int row = 0; row < height; row++){
        for(int col = 0; col < width; col++){
            rectangle.setPosition(col * (tile_size + spacing + (tile_frame * 2)) + left_offset, row * (tile_size + spacing + (tile_frame * 2)) + top_offset);

            tile_text = board.getFieldInfo(row, col);
            text.setString(tile_text);
            text.setPosition(col * (tile_size + spacing + (tile_frame * 2)) + left_offset + text_left_offset, row * (tile_size + spacing + (tile_frame * 2)) + top_offset);

            // Wstawić funkcje
            switch(board.getFieldInfo(row, col)){
                case '_':
                    rectangle.setFillColor(sf::Color(220, 220, 220));
                    window.draw(rectangle);
                    break;
                case ' ':
                    rectangle.setFillColor(sf::Color(120, 120, 120));
                    window.draw(rectangle);
                    break;
                case '1':
                    rectangle.setFillColor(sf::Color(120, 120, 120));
                    window.draw(rectangle);
                    text.setFillColor(sf::Color(0, 0, 255));
                    window.draw(text);
                    break;
                case '2':
                    rectangle.setFillColor(sf::Color(120, 120, 120));
                    window.draw(rectangle);
                    text.setFillColor(sf::Color(0, 255, 0));
                    window.draw(text);
                    break;
                case '3':
                    rectangle.setFillColor(sf::Color(120, 120, 120));
                    window.draw(rectangle);
                    text.setFillColor(sf::Color(255, 0, 0));
                    window.draw(text);
                    break;
                case '4':
                    rectangle.setFillColor(sf::Color(120, 120, 120));
                    window.draw(rectangle);
                    text.setFillColor(sf::Color(0, 0, 45));
                    window.draw(text);
                    break;
                case '5':
                    rectangle.setFillColor(sf::Color(120, 120, 120));
                    window.draw(rectangle);
                    text.setFillColor(sf::Color(255, 100, 0));
                    window.draw(text);
                    break;
                case '6':
                    rectangle.setFillColor(sf::Color(120, 120, 120));
                    window.draw(rectangle);
                    text.setFillColor(sf::Color(100, 100, 255));
                    window.draw(text);
                    break;
                case '7':
                    rectangle.setFillColor(sf::Color(120, 120, 120));
                    window.draw(rectangle);
                    text.setFillColor(sf::Color(255, 100, 100));
                    window.draw(text);
                    break;
                case '8':
                    rectangle.setFillColor(sf::Color(120, 120, 120));
                    window.draw(rectangle);
                    text.setFillColor(sf::Color(0, 0, 0));
                    window.draw(text);
                    break;
                case 'F':
                    rectangle.setFillColor(sf::Color(220, 220, 220));
                    window.draw(rectangle);
                    triangle.setRotation(0);
                    triangle.setFillColor(sf::Color(0, 0, 0));
                    triangle.setPosition(col * (tile_size + spacing + (tile_frame * 2)) + left_offset + 15, row * (tile_size + spacing + (tile_frame * 2)) + top_offset + 25);
                    window.draw(triangle);
                    triangle.setRotation(-30);
                    triangle.setFillColor(sf::Color(255, 0, 0));
                    triangle.setPosition(col * (tile_size + spacing + (tile_frame * 2)) + left_offset + 15, row * (tile_size + spacing + (tile_frame * 2)) + top_offset + 15);
                    window.draw(triangle);
                    break;
                case 'x':
                    rectangle.setFillColor(sf::Color(120, 120, 120));
                    window.draw(rectangle);
                    bomb.setPosition(col * (tile_size + spacing + (tile_frame * 2)) + left_offset + 12, row * (tile_size + spacing + (tile_frame * 2)) + top_offset + 12);
                    window.draw(bomb);
                    break;
            }


        }
    }


    // end the current frame
    window.display();

}