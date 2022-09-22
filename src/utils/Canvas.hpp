#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <string>
#include <stdlib.h>
#include "../components/Cell.hpp"
#include "../components/Grid.hpp"
#include "RandomNumberGenerator.hpp"
#include "Constants.hpp"
#include "SoundManager.hpp"

void resetTheGrid(Grid &Grid);
bool isOdd(unsigned int num);
State computeRandomState();
void shuffleCellStates(Grid &grid);
void setupGrid(sf::RenderWindow &window, Grid &grid);
void drawCell(sf::RenderWindow &window, Cell &cell);
bool isValidClick(const sf::Vector2i &position);
sf::Vector2i computeIndexPosition(const sf::Vector2i &position);
bool isValidIndexPostion(const sf::Vector2i &position);
void onClickSetCellState(sf::RenderWindow &window, Grid &grid, State state);
void handleLeftClickCell(sf::RenderWindow &window, Grid &grid);
void handleRightClickCell(sf::RenderWindow &window, Grid &grid);
void renderLiveCellsStatistics(sf::RenderWindow &window, Grid &grid, sf::Text &text);

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

bool isOdd(unsigned int num)
{
    return num & 1;
}

State computeRandomState()
{
    return isOdd(randomNumberGenerator()) ? live : dead;
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
    return position.x >= 0 && position.y >= 0 && position.x <= (colSize - 1) && position.y <= (rowSize - 1);
}

void onClickSetCellState(sf::RenderWindow &window, Grid &grid, State state)
{
    sf::Vector2i clickPosition = sf::Mouse::getPosition(window);
    if (isValidClick(clickPosition))
    {
        sf::Vector2i indexPosition = computeIndexPosition(clickPosition);
        if (isValidIndexPostion(indexPosition))
        {
            globalSoundManager.playClickSound();
            grid.setCellState(indexPosition.x, indexPosition.y, state);
        }
    }
}

void handleLeftClickCell(sf::RenderWindow &window, Grid &grid)
{
    onClickSetCellState(window, grid, live);
}

void handleRightClickCell(sf::RenderWindow &window, Grid &grid)
{
    onClickSetCellState(window, grid, dead);
}

void renderLiveCellsStatistics(sf::RenderWindow &window, Grid &grid, sf::Text &text)
{
    std::string liveCellsCount = std::to_string(grid.countLiveCells());
    text.setString("Current alive cells: " + liveCellsCount +
                   "\n\nkeyboard controls:\nR - Reset the grid to an empty grid\nS - Shuffle the cell states\nP - Pause / restart the cell iteration\nQ - Quit the program\n\nmouse controls:\nLeft click - 'draw', set cell state alive\nRight click - 'erase', set cell state dead");
    window.draw(text);
}

