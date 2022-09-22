#include <SFML/Graphics.hpp>
#include <iostream>
#include "components/Grid.hpp"
#include "utils/Canvas.hpp"
#include "utils/Frame.hpp"
#include "utils/Constants.hpp"

using namespace std;

int main()
{
    Grid grid(colSize, rowSize);

    shuffleCellStates(grid);

    grid.computeNextIteration();

    sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight), "Conway's Game of Life");

    window.setFramerateLimit(frameRateLimit);

    auto cancel = std::make_shared<cancel_token_t>(false);
    auto computeNextIterationLambdaFunction = computeNextIterationLambda(grid);
    setInterval(computeNextIterationLambdaFunction, interval, cancel);

    sf::Font font;
    if (!font.loadFromFile(fontPath))
    {
        std::cerr << "Failed to load font file." << std::endl;
        exit(1);
    }

    sf::Text text;
    text.setFont(font);
    text.setPosition(sideLength * (colSize + 2), sideLength * 2);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear(sf::Color::Black);

        setupGrid(window, grid);

        if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
        {
            std::cout << "click" << endl;
            handleLeftClickCell(window, grid);
        }

        if (sf::Mouse::isButtonPressed(sf::Mouse::Right))
        {
            std::cout << "click" << endl;
            handleRightClickCell(window, grid);
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

        renderLiveCellsStatistics(window, grid, text);

        window.display();
    }

    return 0;
}
