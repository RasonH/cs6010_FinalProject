#include <SFML/Graphics.hpp>
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include "components/Grid.hpp"
#include "utils/Canvas.hpp"

using namespace std;

int main()
{
    srand(time(nullptr));

    const unsigned int radius = 18;
    const unsigned int rowSize = 25;
    const unsigned int colSize = 25;

    const unsigned int windowWidth = radius * (3 * colSize + 3);
    const unsigned int windowHeight = radius * (3 * rowSize + 3);

    Grid grid(rowSize, colSize);

    shuffleCellStates(grid);

    grid.computeNextIteration();

    // create the window and set the window title
    sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight), "Conway's Game of Life");

    window.setFramerateLimit(15);

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

        setupGrid(window, radius, grid);
        // end the current frame

        if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
        {
            std::cout << "click" << endl;
            handleClickCell(window, grid, radius, windowWidth, windowHeight);
        }

        window.display();
    }

    return 0;
}
