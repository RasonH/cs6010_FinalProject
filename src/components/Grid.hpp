#pragma once
#include "Cell.hpp"
#include <vector>
#include <iostream>

class Grid
{
private:
    unsigned int rowSize_;
    unsigned int colSize_;
    std::vector<std::vector<Cell>> cells_;
    bool isPaused_;

public:
    Grid();
    Grid(unsigned int rows, unsigned int cols);
    Grid(const std::vector<std::vector<State>> &states);
    Grid(const Grid &original);
    Grid &operator=(const Grid &original);

    void toggleIsPaused();
    void computeNextIteration();
    void computeCellState(unsigned int row, unsigned int col);
    void computeCellFinalState(unsigned int row, unsigned int col);
    void toggleCellState(unsigned int row, unsigned int col);
    void setCellState(unsigned int row, unsigned int col, State newState);

    unsigned int countLiveNeighbors(unsigned int row, unsigned int col);

    Cell &getCell(unsigned int row, unsigned int col);
    const unsigned int getRowSize() const;
    const unsigned int getColSize() const;
};

Grid::Grid()
{
    rowSize_ = 0;
    colSize_ = 0;
    cells_ = {{}};
    isPaused_ = false;
}

Grid::Grid(unsigned int rows, unsigned int cols)
{
    rowSize_ = rows;
    colSize_ = cols;
    isPaused_ = false;
    for (unsigned int row = 0; row < rowSize_; row++)
    {
        cells_.push_back({});
        for (unsigned int col = 0; col < colSize_; col++)
        {
            cells_[row].push_back(Cell({row, col}, dead));
        }
    }
}

Grid::Grid(const std::vector<std::vector<State>> &states)
{
    rowSize_ = states.size();
    colSize_ = states.back().size();
    isPaused_ = false;
    for (unsigned int row = 0; row < rowSize_; row++)
    {
        for (unsigned int col = 0; col < colSize_; col++)
        {
            cells_[row][col] = Cell({row, col}, states[row][col]);
        }
    }
}

Grid::Grid(const Grid &original)
{
    if (this == &original)
    {
        return;
    }
    rowSize_ = original.rowSize_;
    colSize_ = original.colSize_;
    isPaused_ = false;
    for (int row = 0; row < rowSize_; row++)
    {
        for (int col = 0; col < colSize_; col++)
        {
            cells_[row][col] = original.cells_[row][col];
        }
    }
}

void Grid::toggleIsPaused()
{
    isPaused_ = !isPaused_;
}

Grid &Grid::operator=(const Grid &original)
{
    if (this == &original)
    {
        return *this;
    }
    rowSize_ = original.rowSize_;
    colSize_ = original.colSize_;
    isPaused_ = original.isPaused_;
    for (int row = 0; row < rowSize_; row++)
    {
        for (int col = 0; col < colSize_; col++)
        {
            cells_[row][col] = original.cells_[row][col];
        }
    }
    return *this;
}

unsigned int Grid::countLiveNeighbors(unsigned int row, unsigned int col)
{
    unsigned int liveNeighbors = 0;
    // check horizontal & vertical directions
    const int upDownLeftRightDirs[] = {0, -1, 0, 1, 0};
    for (int i = 0; i < 4; i++)
    {
        if ((row == 0 && upDownLeftRightDirs[i] == -1) || (col == 0 && upDownLeftRightDirs[i + 1] == -1) || (row + upDownLeftRightDirs[i] >= rowSize_) || (col + upDownLeftRightDirs[i + 1] >= colSize_))
        {
            continue;
        }
        unsigned int newRow = row + upDownLeftRightDirs[i], newCol = col + upDownLeftRightDirs[i + 1];
        liveNeighbors += cells_[newRow][newCol].isCurrentlyLive();
    }
    // check diagonal directions
    const int diagonalDirs[] = {-1, 1};
    for (int i : diagonalDirs)
    {
        for (int j : diagonalDirs)
        {
            if ((row == 0 && i == -1) || (col == 0 && j == -1) || (row + i >= rowSize_) || (col + j >= colSize_))
            {
                continue;
            }
            unsigned int newRow = row + i, newCol = col + j;
            liveNeighbors += cells_[newRow][newCol].isCurrentlyLive();
        }
    }
    return liveNeighbors;
}

void Grid::computeCellState(unsigned int row, unsigned int col)
{
    unsigned int liveNeighbors = countLiveNeighbors(row, col);
    // Any live cell with fewer than two live neighbors dies as if caused by under-population.
    if (liveNeighbors < 2 && cells_[row][col].getState() == live)
    {
        cells_[row][col].setState(nextIterationDead);
    }
    // Any live cell with more than three live neighbors dies, as if by over-population.
    else if (liveNeighbors > 3 && cells_[row][col].getState() == live)
    {
        cells_[row][col].setState(nextIterationDead);
    }
    // Any dead cell with exactly three live neighbors becomes a live cell, as if by reproduction.
    else if (liveNeighbors == 3 && cells_[row][col].getState() == dead)
    {
        cells_[row][col].setState(nextIterationLive);
    }
}

void Grid::computeCellFinalState(unsigned int row, unsigned int col)
{
    if (cells_[row][col].getState() == nextIterationDead)
    {
        cells_[row][col].setState(dead);
    }
    else if (cells_[row][col].getState() == nextIterationLive)
    {
        cells_[row][col].setState(live);
    }
}

void Grid::computeNextIteration()
{
    if (isPaused_)
    {
        return;
    }
    for (unsigned row = 0; row < rowSize_; row++)
    {
        for (unsigned col = 0; col < colSize_; col++)
        {
            computeCellState(row, col);
        }
    }

    for (unsigned row = 0; row < rowSize_; row++)
    {
        for (unsigned col = 0; col < colSize_; col++)
        {
            computeCellFinalState(row, col);
        }
    }
}

Cell &Grid::getCell(unsigned int row, unsigned int col)
{
    return cells_[row][col];
}

const unsigned int Grid::getRowSize() const
{
    return rowSize_;
}

const unsigned int Grid::getColSize() const
{
    return colSize_;
}

void Grid::toggleCellState(unsigned int row, unsigned int col)
{
    cells_[row][col].toggleState();
}

void Grid::setCellState(unsigned int row, unsigned int col, State newState)
{
    cells_[row][col].setState(newState);
}