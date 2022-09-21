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

    Grid grid(rowSize, colSize);

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
            handleClickCell(window, grid, sideLength, windowWidth, windowHeight);
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
        
        //restricting mouse inside the window -- found name not comparing with direction (col and row should be switched -- currently by switching them in the constants)
        //problem unsolved - mouse set to bottom when y < 0;
        sf::Vector2i mousePosRelative = sf::Mouse::getPosition(window);
        
        if (mousePosRelative.x < 0)
        {
            sf::Mouse::setPosition(sf::Vector2i(0, mousePosRelative.y), window);
        }
        else if (mousePosRelative.x > windowWidth)
        {
            sf::Mouse::setPosition(sf::Vector2i(windowWidth, mousePosRelative.y), window);
        }
        else if (mousePosRelative.y > windowHeight)
        {
            sf::Mouse::setPosition(sf::Vector2i(mousePosRelative.x, windowHeight), window);
        }
        else if (mousePosRelative.y < 15){
            sf::Mouse::setPosition(sf::Vector2i(mousePosRelative.x, 10), window);
        }
        
        
        window.display();
    }

    return 0;
}
