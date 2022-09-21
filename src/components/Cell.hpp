#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <map>

enum State
{
    live = 1,
    dead = 0,
    nextIterationLive = 2,
    nextIterationDead = -1
};

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

    void setState(State newState);
    void toggleState();
    void printCellInfo();
    bool isCurrentlyLive();
    bool isCurrentlyDead();

    sf::Color getColorByState();
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

void Cell::printCellInfo()
{
    std::cout << "Position: " << position_.x << " , " << position_.y << std::endl;
    std::cout << "State: " << (state_ ? 'live' : 'dead') << std::endl
              << std::endl;
}

bool Cell::isCurrentlyDead()
{
    return state_ == dead || state_ == nextIterationLive;
}

bool Cell::isCurrentlyLive()
{
    return state_ == live || state_ == nextIterationDead;
}

void Cell::toggleState()
{
    if (isCurrentlyDead())
    {
        setState(live);
    }
    else
    {
        setState(dead);
    }
}

sf::Color Cell::getColorByState()
{
    if (isCurrentlyLive())
    {
        return sf::Color::Blue;
    }
    else
    {
        return sf::Color::White;
    }
}
