#include <SFML/Graphics.hpp>

int main()
{
    int height = 9, width = 9;
    float tile_size = 50, distance = 10, offset;



    // create the window
    sf::RenderWindow window(sf::VideoMode(800, 600), "My window");

    // define a 120x50 rectangle
    sf::RectangleShape rectangle(sf::Vector2f(tile_size, tile_size));

    // change the size to 100x100
    rectangle.setFillColor(sf::Color(100, 250, 50));
    // set a 10-pixel wide orange outline
    rectangle.setOutlineThickness(5);
    rectangle.setOutlineColor(sf::Color(250, 150, 100));




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
                rectangle.setPosition(, 350);
                window.draw(rectangle);
            }
        }

        rectangle.setPosition(300, 350);
        window.draw(rectangle);


        // end the current frame
        window.display();
    }

    return 0;
}