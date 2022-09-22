#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <set>

enum State
{
    live = 1,
    dead = 0,
    nextIterationLive = 2,
    nextIterationDead = -1
};

const std::set<State> currentlyDeadStates = {dead, nextIterationLive};

const std::set<State> currentlyLiveStates = {live, nextIterationDead};

const sf::Color currentlyLiveColor = sf::Color::Blue;

const sf::Color currentlyDeadColor = sf::Color::White;

class Cell
{
private:
    sf::Vector2u position_;
    State state_;

public:
    Cell();
    Cell(const sf::Vector2u &initialPosition, State initialState);
    State getState() const;
    sf::Vector2u getPosition() const;
    sf::Color getColorByState();
    void setState(State newState);
    bool isCurrentlyLive();
    bool isCurrentlyDead();
};

Cell::Cell()
{
    position_ = sf::Vector2u(0.0, 0.0);
    state_ = dead;
}

Cell::Cell(const sf::Vector2u &initialPosition, State initialState)
{
    position_ = initialPosition;
    state_ = initialState;
}

State Cell::getState() const
{
    return state_;
}

sf::Vector2u Cell::getPosition() const
{
    return position_;
}

void Cell::setState(State newState)
{
    state_ = newState;
}

bool Cell::isCurrentlyDead()
{
    return currentlyDeadStates.find(state_) != currentlyDeadStates.end();
}

bool Cell::isCurrentlyLive()
{
    return currentlyLiveStates.find(state_) != currentlyLiveStates.end();
}

sf::Color Cell::getColorByState()
{
    if (isCurrentlyLive())
    {
        return currentlyLiveColor;
    }
    else
    {
        return currentlyDeadColor;
    }
}
