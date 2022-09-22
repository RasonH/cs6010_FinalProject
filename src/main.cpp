#include <SFML/Graphics.hpp>
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include "components/Grid.hpp"
#include "utils/Canvas.hpp"
#include "utils/Frame.hpp"
#include "utils/Constants.hpp"

using namespace std;

int main()
{
    srand(time(nullptr));

    Grid grid(colSize, rowSize);

    shuffleCellStates(grid);

    grid.computeNextIteration();

    sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight), "Conway's Game of Life");

    window.setFramerateLimit(frameRateLimit);

    auto cancel = std::make_shared<cancel_token_t>(false);
    std::chrono::milliseconds oneSecond = 1s;
    std::chrono::milliseconds interval = oneSecond / frameRateLimit;
    auto computeNextIterationLambdaFunction = computeNextIterationLambda(grid);
    setInterval(computeNextIterationLambdaFunction, interval, cancel);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear(sf::Color::Black);
        
        setupGrid(window, sideLength, grid);

        if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
        {
            std::cout << "click" << endl;
            handleLeftClickCell(window, grid, sideLength, windowWidth, windowHeight, colSize, rowSize);
        }
        
        if (sf::Mouse::isButtonPressed(sf::Mouse::Right))
        {
            std::cout << "click" << endl;
            handleRightClickCell(window, grid, sideLength, windowWidth, windowHeight, colSize, rowSize);
        }
        
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::R))
        {
            std::cout << "reset the grid to an empty grid" << std::endl;
            resetTheGrid(grid);
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
        {
            std::cout << "shuffle the cell states" << std::endl;
            shuffleCellStates(grid);
        }
        
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::P))
        {
            std::cout << "Pause / Restart the cell iteration" << std::endl;
            grid.toggleIsPaused();
        }
        
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
        {
            std::cout << "Quit the program" << std::endl;
            break;
        }
        window.setMouseCursorGrabbed(true);
        
        
        window.display();
    }

    return 0;
}
