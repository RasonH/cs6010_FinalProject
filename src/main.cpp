#include <SFML/Graphics.hpp>
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include "components/Grid.hpp"
//#include "components/Snake.hpp"
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
    auto computeNextIterationLambdaFunction = computeNextIterationLambda(grid);
    setInterval(computeNextIterationLambdaFunction, interval, cancel);
    
    sf::Font font;
    if (!font.loadFromFile(getFontPath()))
    {
        return EXIT_FAILURE;
    }
    sf::Text text;
    text.setFont(font);
    text.setPosition(sideLength * (colSize + 2) , sideLength *2);
    text.setCharacterSize(30);

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
        
        std::string sumOfCells = to_string(grid.sumAlive());
        
        text.setString("Current alive cells: "
                       + sumOfCells +
                       "\n\nkeyboard controls:\nR - Reset the grid to an empty grid\nS - Shuffle the cell states\nP - Pause / restart the cell iteration\nQ - Quit the program\n\nmouse controls:\nLeft click - 'draw', set cell state alive\nRight click - 'erase', set cell state dead");
        window.draw(text);
        window.display();
    }

    return 0;
}
