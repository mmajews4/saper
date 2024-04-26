#include "MSSFMLView.h"
#include <filesystem>

MSSFMLView::MSSFMLView(MinesweeperBoard &b) : board(b)
{
    window_width = 800, window_height = 600;
    height = board.getBoardHeight();
    width = board.getBoardWidth();
    tile_size = 40, spacing = 4, left_offset = 10, top_offset = 10, tile_frame = 3;
    text_left_offset = 13, text_top_offset = 5;
    bomb_size = 12, bomb_offset = 12;
    flag_size = 20, flag_triangles_offset = 10, flag_offset_w = 15, flag_offset_h = 15;
    game_state_size = 90;
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

// Function draws one frame on the window
void MSSFMLView::draw(sf::RenderWindow &window)
{
    // centering board
    left_offset = (window_width - (width * tileLength())) / 2;
    top_offset = (window_height - ((height - 1) * tileLength())) / 2;

    // centering flag and bombs inside a tile
    flag_size = tile_size * 1/5;
    flag_triangles_offset = tile_size * 1/5;
    flag_offset_w = tile_size * 3/10;
    flag_offset_h = tile_size * 3/10;

    bomb_size = tile_size/4;
    bomb_offset = tile_size/4;

    // Assert for setting board too big
    if(left_offset < 0 || top_offset < 0){
        std::cerr << "Window too small to display board" << std::endl;
        exit(EXIT_FAILURE);
        
    }

    // create rectangle object
    sf::RectangleShape rectangle(sf::Vector2f(tile_size, tile_size));
    rectangle.setFillColor(sf::Color(220, 220, 220));
    rectangle.setOutlineThickness(tile_frame);
    rectangle.setOutlineColor(sf::Color(120, 120, 120));

    // I do it that way bezause it somehow works differetn using makefile,vscode and clion
    // Get path to "arial.ttf"
    std::filesystem::path currentPath = std::filesystem::current_path();
    std::filesystem::path fontPath = currentPath / "arial.ttf";

    // Load the font
    sf::Font font;
    if (!font.loadFromFile(fontPath.string())) {
        std::cerr << "Failed to load font." << std::endl;
        exit(EXIT_FAILURE);
    }

    // Create a text object
    sf::Text text;
    text.setFont(font);
    text.setStyle(sf::Text::Bold);
    text.setCharacterSize(tile_size - (2 * text_top_offset));
    text.setFillColor(sf::Color(200, 0, 0));


    // Create triangle for flag
    sf::CircleShape triangle(flag_size, 3);
    triangle.setFillColor(sf::Color(255, 0, 0));

    // Create bomb
    sf::CircleShape bomb(bomb_size);
    bomb.setFillColor(sf::Color::Black);

    // clear the window with black color
    window.clear(sf::Color::Black);

    // Draw outer frame of the board
    rectangle.setPosition(left_offset - tile_frame - (spacing / 2), top_offset - tileLength() - tile_frame - (spacing / 2));
    rectangle.setSize(sf::Vector2f(width * tileLength(), (height + 1) * tileLength()));
    window.draw(rectangle);
    rectangle.setSize(sf::Vector2f(tile_size, tile_size));

    // Draw upper bar
    switch (board.getGameState())
    {
        case GameState::FINISHED_LOSS:
            text.setFillColor(sf::Color(255, 0, 0));
            text.setPosition(left_offset + (width * tileLength()/ 2.0) - game_state_size, top_offset - tileLength());
            text.setString("YOU LOOSE!");
            window.draw(text);
            break;
        case GameState::FINISHED_WIN:
            text.setFillColor(sf::Color(0, 0, 0));
            text.setPosition(left_offset + (width * tileLength()/ 2.0) - game_state_size, top_offset - tileLength());
            text.setString("YOU WIN! :)");
            window.draw(text);
            break;
        case GameState::RUNNING:
            text.setFillColor(sf::Color(150, 150, 150));
            text.setPosition(left_offset + (width * tileLength()/ 2.0) - game_state_size, top_offset - tileLength());
            text.setString("  RESTART");
            window.draw(text);
            break;
        default:
            break;
    }

    // Draw tiles
    // Not in another function because there are too many object to give as arguments
    for(int row = 0; row < height; row++){
        for(int col = 0; col < width; col++){

            // Draw tile
            rectangle.setPosition(col * tileLength() + left_offset, row * tileLength() + top_offset);
            
            // Set text parameters
            tile_text = board.getFieldInfo(row, col);
            text.setString(tile_text);
            text.setPosition(col * tileLength() + left_offset + text_left_offset, row * tileLength() + top_offset);

            // Write symbols in tiles
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
                triangle.setPosition(col * tileLength() + left_offset + flag_offset_w, row * tileLength() + top_offset + flag_offset_h + flag_triangles_offset);
                window.draw(triangle);
                triangle.setRotation(-30);
                triangle.setFillColor(sf::Color(255, 0, 0));
                triangle.setPosition(col * tileLength() + left_offset + flag_offset_w, row * tileLength() + top_offset + flag_offset_h);
                window.draw(triangle);
                break;
            case 'x':
                rectangle.setFillColor(sf::Color(120, 120, 120));
                window.draw(rectangle);
                bomb.setPosition(col * tileLength() + left_offset + bomb_offset, row * tileLength() + top_offset + bomb_offset);
                window.draw(bomb);
                break;
            }
        }
    }

    // Display current frame
    window.display();
}
