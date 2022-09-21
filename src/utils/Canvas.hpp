#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <stdlib.h>
#include "../components/Cell.hpp"
#include "../components/Grid.hpp"

void resetTheGrid(Grid &Grid);
State computeRandomState();
void shuffleCellStates(Grid &grid);
void setupGrid(sf::RenderWindow &window, const unsigned int sideLength, Grid &grid);
void drawCell(sf::RenderWindow &window, const unsigned int sideLength, Cell &cell);
bool isValidClick(const sf::Vector2i &position, const unsigned int windowWidth, const unsigned int windowHeight);
sf::Vector2i computeIndexPosition(const sf::Vector2i &position, const unsigned int sideLength);
bool isValidIndexPostion(const sf::Vector2i &position);
void handleClickCell(sf::RenderWindow &window, Grid &grid, const unsigned int sideLength, const unsigned int windowWidth, const unsigned int windowHeight);

void resetTheGrid(Grid &grid)
{
    for (int row = 0; row < grid.getRowSize(); row++)
    {
        for (int col = 0; col < grid.getColSize(); col++)
        {
            grid.setCellState(row, col, dead);
        }
    }
}

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

void setupGrid(sf::RenderWindow &window, const unsigned int sideLength, Grid &grid)
{
    for (unsigned int row = 0; row < grid.getRowSize(); row++)
    {
        for (unsigned int col = 0; col < grid.getColSize(); col++)
        {
            drawCell(window, sideLength, grid.getCell(row, col));
        }
    }
}

void drawCell(sf::RenderWindow &window, const unsigned int sideLength, Cell &cell)
{
    sf::RectangleShape shape(sf::Vector2f(sideLength * 0.95, sideLength * 0.95));
    sf::Vector2u position = cell.getPosition();
    int rowPos = sideLength * (position.x + 1); //real position - upleft corner
    int colPos = sideLength * (position.y + 1);

    shape.setPosition(rowPos, colPos);

    shape.setFillColor(cell.getColorByState());

    window.draw(shape);
}

bool isValidClick(const sf::Vector2i &position, const unsigned int windowWidth, const unsigned int windowHeight)
{
    return 0 <= position.x && position.x <= windowWidth && 0 <= position.y && position.y <= windowHeight;
}

sf::Vector2i computeIndexPosition(const sf::Vector2i &position, const unsigned int sideLength)
{//to do: need to modify
    int rowIndex = (position.y / sideLength) - 1;
    bool isValidRow = (rowIndex + 1) * sideLength <= position.y && position.y <= (rowIndex + 2) * sideLength;
    int colIndex = (position.x / sideLength) - 1;
    bool isValidCol = (colIndex + 1) * sideLength <= position.x && position.x <= (colIndex + 2) * sideLength;
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

void handleClickCell(sf::RenderWindow &window, Grid &grid, const unsigned int sideLength, const unsigned int windowWidth, const unsigned int windowHeight)
{
    sf::Vector2i clickPosition = sf::Mouse::getPosition(window);
    if (isValidClick(clickPosition, windowWidth, windowHeight))
    {
        sf::Vector2i indexPosition = computeIndexPosition(clickPosition, sideLength);
        if (isValidIndexPostion(indexPosition))
        {
            std::cout << "handle valid cell click" << std::endl;
            grid.toggleCellState(indexPosition.x, indexPosition.y);
        }
    }
}
