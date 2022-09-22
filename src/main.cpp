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

    sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight), gameTitle);

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
    text.setPosition(textPosition.x, textPosition.y);

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

        handleMouseAndKeyboardOperation(window, grid);

        window.setMouseCursorGrabbed(true);

        renderLiveCellsStatistics(window, grid, text);

        window.display();
    }

    return 0;
}
