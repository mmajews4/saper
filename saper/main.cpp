#include <iostream>
#include <SFML/Graphics.hpp>
#include "Array2D.h"
#include "MinesweeperBoard.h"
#include "MSBoardTextView.h"
#include "MSTextController.h"
#include "MSSFMLView.h"
#include "MSSFMLController.h"

using namespace std;

int main()
{
    MinesweeperBoard board(9, 9, NORMAL);
    MSSFMLView view (board);
    MSSFMLController ctrl (board, view);

    sf::RenderWindow window(sf::VideoMode(view.getWindowWidth(), view.getWindowHeight()), "Saper", sf::Style::Titlebar | sf::Style::Close);
    window.setVerticalSyncEnabled(false);
    window.setFramerateLimit(30);

    MSBoardTextView console_view ( board );

    while (window.isOpen())
    {
        ctrl.play(window);
    }

    return 0;
}