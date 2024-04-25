#include <iostream>
#include <SFML/Graphics.hpp>
#include "Array2D.h"
#include "MinesweeperBoard.h"
#include "MSBoardTextView.h"
#include "MSTextController.h"
#include "MSSFMLView.h"
#include "MSSFMLController.h"

using namespace std;
/*
int main() {

    MinesweeperBoard board (5, 5, GameMode::NORMAL);
    MSBoardTextView console_view ( board );
    MSTextController console_ctrl ( board, console_view );

    console_ctrl.play();
    return 0;
}
*/
int main()
{
    MinesweeperBoard board(9, 9, NORMAL);
    MSSFMLView view (board);
    MSSFMLController ctrl (board, view);

    sf::RenderWindow window(sf::VideoMode(view.getWindowWidth(), view.getWindowHeight()), "Grafika w C++/SFML");
    window.setVerticalSyncEnabled(false);
    window.setFramerateLimit(30);

    // symulujemy rozgrywkę
/*    board.toggleFlag(0,0);
    board.revealField(2,3);
    board.revealField(0,2);
    board.revealField(5,0);
    board.revealField(6,1);
    board.revealField(5,3);
    board.revealField(6,3);
*/
    MSBoardTextView console_view ( board );
    console_view.display();
//    MSTextController console_ctrl ( board, console_view );
//    console_ctrl.play();

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        ctrl.play(window);
    }

    return 0;
}