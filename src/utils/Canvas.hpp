#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <stdlib.h>
#include <string>
#include "../components/Cell.hpp"
#include "../components/Grid.hpp"
#include "Constants.hpp"
#include "SoundManager.hpp"

void resetTheGrid(Grid &Grid);
State computeRandomState();
void shuffleCellStates(Grid &grid);
void setupGrid(sf::RenderWindow &window, Grid &grid);
void drawCell(sf::RenderWindow &window, Cell &cell);
bool isValidClick(const sf::Vector2i &position);
sf::Vector2i computeIndexPosition(const sf::Vector2i &position);
bool isValidIndexPostion(const sf::Vector2i &position);
void handleLeftClickCell(sf::RenderWindow &window, Grid &grid);
void handleRightClickCell(sf::RenderWindow &window, Grid &grid);

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

void setupGrid(sf::RenderWindow &window, Grid &grid)
{
    for (unsigned int row = 0; row < grid.getRowSize(); row++)
    {
        for (unsigned int col = 0; col < grid.getColSize(); col++)
        {
            drawCell(window, grid.getCell(row, col));
        }
    }
}

void drawCell(sf::RenderWindow &window, Cell &cell)
{
    sf::RectangleShape shape(sf::Vector2f(sideLength * 0.95, sideLength * 0.95));
    sf::Vector2u position = cell.getPosition();
    // real position - upleft corner
    int rowPos = sideLength * (position.x + 1); 
    int colPos = sideLength * (position.y + 1);

    shape.setPosition(rowPos, colPos);

    shape.setFillColor(cell.getColorByState());

    window.draw(shape);
}

bool isValidClick(const sf::Vector2i &position)
{
    return 0 <= position.x && position.x <= windowWidth + 100 && 0 <= position.y && position.y <= windowHeight + 100;
}

sf::Vector2i computeIndexPosition(const sf::Vector2i &position)
{
    int rowIndex = (position.y / sideLength) - 1;
    bool isValidRow = (rowIndex + 1) * sideLength <= position.y && position.y <= (rowIndex + 2) * sideLength;
    int colIndex = (position.x / sideLength) - 1;
    bool isValidCol = (colIndex + 1) * sideLength <= position.x && position.x <= (colIndex + 2) * sideLength;
    sf::Vector2i indexPosition(-1, -1);
    if (isValidRow && isValidCol)
    {
        indexPosition.x = colIndex;
        indexPosition.y = rowIndex;
    }
    return indexPosition;
}

bool isValidIndexPostion(const sf::Vector2i &position)
{
    return position.x >= 0 && position.y >= 0 && position.x <= (colSize -1) && position.y <= (rowSize - 1);
}

void handleLeftClickCell(sf::RenderWindow &window, Grid &grid)
{
    sf::Vector2i clickPosition = sf::Mouse::getPosition(window);
    if (isValidClick(clickPosition))
    {
        sf::Vector2i indexPosition = computeIndexPosition(clickPosition);
        if (isValidIndexPostion(indexPosition))
        {
            globalSoundManager.playClickSound();
            std::cout
                << "handle valid cell click" << std::endl;
            grid.setCellState(indexPosition.x, indexPosition.y, live);
        }
    }
}

void handleRightClickCell(sf::RenderWindow &window, Grid &grid)
{
    sf::Vector2i clickPosition = sf::Mouse::getPosition(window);
    if (isValidClick(clickPosition))
    {
        sf::Vector2i indexPosition = computeIndexPosition(clickPosition);
        if (isValidIndexPostion(indexPosition))
        {
            globalSoundManager.playClickSound();
            std::cout
                << "handle valid cell click" << std::endl;
            grid.setCellState(indexPosition.x, indexPosition.y, dead);
        }
    }
}
