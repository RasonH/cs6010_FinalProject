#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <stdlib.h>
#include "../components/Cell.hpp"
#include "../components/Grid.hpp"


State computeRandomState();
void shuffleCellStates(Grid &grid);
void setupGrid(sf::RenderWindow &window, const unsigned int radius, Grid &grid);
void drawCell(sf::RenderWindow &window, const unsigned int radius, Cell &cell);
bool isValidClick(const sf::Vector2i &position, const unsigned int windowWidth, const unsigned int windowHeight);
sf::Vector2i computeIndexPosition(const sf::Vector2i &position, const unsigned int radius);
bool isValidIndexPostion(const sf::Vector2i &position);
void handleClickCell(sf::RenderWindow &window, Grid &grid, const unsigned int radius, const unsigned int windowWidth, const unsigned int windowHeight);

State computeRandomState()
{
    return ((float)rand() / RAND_MAX) > 0.5 ? live : dead;
}

void shuffleCellStates(Grid &grid)
{
    for (unsigned int row = 0; row < grid.getRowSize(); row++)
    {
        for (unsigned int col = 0; col < grid.getColSize(); col++)
        {
            grid.setCellState(row, col, computeRandomState());
        }
    }
}

void setupGrid(sf::RenderWindow &window, const unsigned int radius, Grid &grid)
{
    for (unsigned int row = 0; row < grid.getRowSize(); row++)
    {
        for (unsigned int col = 0; col < grid.getColSize(); col++)
        {
            drawCell(window, radius, grid.getCell(row, col));
        }
    }
}

void drawCell(sf::RenderWindow &window, const unsigned int radius, Cell &cell)
{
    sf::CircleShape shape(radius);
    sf::Vector2u position = cell.getPosition();
    int rowPos = radius * (3 * position.x + 2);
    int colPos = radius * (3 * position.y + 2);

    shape.setPosition(rowPos, colPos);

    shape.setFillColor(cell.getColorByState());

    window.draw(shape);
}

bool isValidClick(const sf::Vector2i &position, const unsigned int windowWidth, const unsigned int windowHeight)
{
    return 0 <= position.x && position.x <= windowWidth && 0 <= position.y && position.y <= windowHeight;
}

sf::Vector2i computeIndexPosition(const sf::Vector2i &position, const unsigned int radius)
{
    int rowIndex = ((position.y / radius) - 1) / 3;
    bool isValidRow = (rowIndex * 3 + 1) * radius <= position.y && position.y <= (rowIndex * 3 + 3) * radius;
    int colIndex = ((position.x / radius) - 1) / 3;
    bool isValidCol = (colIndex * 3 + 1) * radius <= position.x && position.x <= (colIndex * 3 + 3) * radius;
    sf::Vector2i indexPosition(-1, -1);
    if (isValidRow && isValidCol)
    {
        indexPosition.x = rowIndex;
        indexPosition.y = colIndex;
    }
    return indexPosition;
}

bool isValidIndexPostion(const sf::Vector2i &position)
{
    return position.x != -1 && position.y != -1;
}

void handleClickCell(sf::RenderWindow &window, Grid &grid, const unsigned int radius, const unsigned int windowWidth, const unsigned int windowHeight)
{
    sf::Vector2i clickPosition = sf::Mouse::getPosition(window);
    if (isValidClick(clickPosition, windowWidth, windowHeight))
    {
        sf::Vector2i indexPosition = computeIndexPosition(clickPosition, radius);
        if (isValidIndexPostion(indexPosition))
        {
            std::cout << "handle valid cell click" << std::endl;
            grid.toggleCellState(indexPosition.x, indexPosition.y);
            grid.computeNextIteration();
        }
    }
}