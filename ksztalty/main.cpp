#include <SFML/Graphics.hpp>
#include <iostream>

// g++ main.cpp -o sfml-app -lsfml-graphics -lsfml-window -lsfml-system


int main()
{
    int window_width = 800, window_height = 600;
    int height = 9, width = 15;
    float tile_size = 50, spacing = 3, left_offset = 10, top_offset = 10, tile_frame = 3;

    // Wycentrowanie planszy
    left_offset = (window_width - (width*(tile_size + (tile_frame * 2)+ spacing))) / 2;
    top_offset = (window_height - (height*(tile_size + (tile_frame * 2)+ spacing))) / 2;

    // Zabezpieczenie przed ustawieniem zbyt dużej planszy
    if(left_offset < 0 || top_offset < 0){
        std::cout << "Window too small to display board" << std::endl;
        return 0;
    }

    // create the window
    sf::RenderWindow window(sf::VideoMode(window_width, window_height), "Saper");

    // define a 120x50 rectangle
    sf::RectangleShape rectangle(sf::Vector2f(tile_size, tile_size));

    // change the size to 100x100
    rectangle.setFillColor(sf::Color(220, 220, 220));
    // set a 10-pixel wide orange outline
    rectangle.setOutlineThickness(tile_frame);
    rectangle.setOutlineColor(sf::Color(120, 120, 120));




/*
    // map a 100x100 textured rectangle to the shape
    shape.setTexture(&texture); // texture is a sf::Texture
    shape.setTextureRect(sf::IntRect(10, 10, 100, 100));
*/
    // run the program as long as the window is open
    while (window.isOpen())
    {
        // check all the window's events that were triggered since the last iteration of the loop
        sf::Event event;
        while (window.pollEvent(event))
        {
            // "close requested" event: we close the window
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // clear the window with black color
        window.clear(sf::Color::Black);

      // draw everything here...
        for(int row = 0; row < width; row++){
            for(int col = 0; col < height; col++){
                rectangle.setPosition(col * (tile_size + spacing + (tile_frame * 2)) + left_offset, row * (tile_size + spacing + (tile_frame * 2)) + top_offset);
                window.draw(rectangle);
            }
        }


        // end the current frame
        window.display();
    }

    return 0;
}