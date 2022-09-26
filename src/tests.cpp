#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <cassert>
#include "components/Cell.hpp"
#include "components/Grid.hpp"
#include "utils/Canvas.hpp"
#include "utils/Frame.hpp"
#include "utils/Constants.hpp"

using namespace std;

void testCellComponent();
void testGridComponent();

int main()
{
    testCellComponent();
    testGridComponent();
    cout << "All tests passed" << endl;
    return 0;
}

void testCellComponent()
{
    sf::Vector2u cellPosition = {42, 42};
    Cell cell(cellPosition, live);

    assert((cell.getState() == live) && "Failed to get the cell's correct state");

    assert((cell.getPosition() == cellPosition) && "Failed to get the cell's correct position");

    assert((cell.getColorByState() == currentlyLiveColor) && "Failed to get the cell's correct color");

    assert((cell.isCurrentlyLive()) && "The cell should be currently live");

    cell.setState(dead);

    assert((cell.isCurrentlyDead()) && "The cell should be currently dead");

    cell.setState(nextIterationDead);

    assert((cell.isCurrentlyLive()) && "The cell should be currently live");

    cell.setState(nextIterationLive);

    assert((cell.isCurrentlyDead()) && "The cell should be currently dead");
}

void testGridComponent()
{
    // the test patterns: https://conwaylife.com/wiki/Conway's_Game_of_Life#Patterns

    const vector<vector<State>> blockStillLife = {
        {dead, dead, dead, dead},
        {dead, live, live, dead},
        {dead, live, live, dead},
        {dead, dead, dead, dead},
    };

    Grid blockStillLifeInitialGrid(blockStillLife);
    Grid blockStillLifeGrid(blockStillLife);

    assert(!blockStillLifeInitialGrid.getIsPaused() && "The blockStillLifeInitialGrid should not be paused");

    blockStillLifeInitialGrid.toggleIsPaused();

    assert(blockStillLifeInitialGrid.getIsPaused() && "The blockStillLifeInitialGrid should be paused");

    blockStillLifeInitialGrid.computeNextIteration();

    assert((blockStillLifeInitialGrid == blockStillLifeGrid) && "The blockStillLifeInitialGrid should not change after iteration");

    const vector<vector<State>> blinkerInitialState = {
        {dead, live, dead},
        {dead, live, dead},
        {dead, live, dead}};

    Grid blinkerInitialGrid(blinkerInitialState);
    blinkerInitialGrid.computeNextIteration();

    const vector<vector<State>> blinkerAfterOneIteration = {
        {dead, dead, dead},
        {live, live, live},
        {dead, dead, dead}};

    Grid blinkerAfterOneIterationGrid(blinkerAfterOneIteration);

    assert((blinkerInitialGrid == blinkerAfterOneIterationGrid) && "The blinkerInitialGrid should be blinkerAfterOneIterationGrid after iteration");

    assert((blinkerInitialGrid.countLiveCells() == 3) && "The blinkerInitialGrid should have 3 live cells after iteration.");

    blinkerInitialGrid.setCellState(1, 1, dead);
    blinkerInitialGrid.computeCellState(1, 0);
    assert((blinkerInitialGrid.getCell(1, 0).getState() == nextIterationDead) && "The cell should be dead in the next iteration");

    blinkerAfterOneIterationGrid.setCellState(0, 1, live);
    blinkerAfterOneIterationGrid.setCellState(2, 1, live);
    blinkerAfterOneIterationGrid.computeCellState(1, 1);
    assert((blinkerAfterOneIterationGrid.getCell(1, 1).getState() == nextIterationDead) && "The cell should be dead in the next iteration");

    blinkerAfterOneIterationGrid.computeCellState(2, 2);
    assert((blinkerAfterOneIterationGrid.getCell(2, 2).getState() == nextIterationLive) && "The cell should be live in the next iteration");
}
