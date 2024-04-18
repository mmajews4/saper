#include <iostream>
#include <SFML/Graphics.hpp>
#include "Array2D.h"
#include "MinesweeperBoard.h"
#include "MSBoardTextView.h"
#include "MSTextController.h"
#include "MSSFMLView.h"

using namespace std;
/*
int main() {

    MinesweeperBoard board (5, 5, GameMode::NORMAL);
    MSBoardTextView view ( board );
    MSTextController ctrl ( board, view );

    ctrl.play();
    return 0;
}
*/
int main()
{
    MinesweeperBoard board(7, 4, DEBUG);
    MSSFMLView view (board);  // przekazujemy przez referencję planszę jako argument konstruktora

    sf::RenderWindow window(sf::VideoMode(view.getWindowWidth(), view.getWindowHeight()), "Grafika w C++/SFML");
    window.setVerticalSyncEnabled(false);
    window.setFramerateLimit(30);

    // symulujemy rozgrywkę
    board.toggleFlag(0,0);
    board.revealField(2,3);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        view.draw(window);
        window.display();
    }

    return 0;
}