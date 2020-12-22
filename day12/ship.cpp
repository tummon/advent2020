#include "ship.hpp"

#include <iostream>

Ship::Ship(): currDirection{Direction::EAST}, westEast{0}, northSouth{0}
{
}

void Ship::parseCommand(const std::string& command)
{
    char instruction = command.at(0);
    int val = std::stoi(command.substr(1));

    switch (instruction)
    {
    case 'N':
        goNorth(val);
        break;
    case 'S':
        goSouth(val);
        break;
    case 'E':
        goEast(val);
        break;
    case 'W':
        goWest(val);
        break;
    case 'L':
        goLeft(val);
        break;
    case 'R':
        goRight(val);
        break;
    case 'F':
        goForward(val);
        break;

    default:
        break;
    }

}

void Ship::printManhatten()
{
    int manhatten = std::abs(northSouth) + std::abs(westEast);
    std::cout << "Manhatten Distance from starting positon = " << manhatten << "\n";
}

void Ship::goNorth(int val)
{
    northSouth -= val;
}

void Ship::goSouth(int val)
{
    northSouth += val;
}

void Ship::goWest(int val)
{
    westEast -= val;
}

void Ship::goEast(int val)
{
    westEast += val;
}

void Ship::goLeft(int degrees)
{
    int change = degrees / 90;
    int oldDirection = static_cast<int>(currDirection);

    if (change > oldDirection) {
        oldDirection += 4;
    }
    int newDirection = (oldDirection - change) % 4;

    currDirection = static_cast<Direction>(newDirection);
}
void Ship::goRight(int degrees)
{
    int change = degrees / 90;
    int oldDirection = static_cast<int>(currDirection);
    int newDirection = (oldDirection + change) % 4;

    currDirection = static_cast<Direction>(newDirection);
}

void Ship::goForward(int val)
{
    switch (currDirection)
    {
    case Direction::NORTH:
        goNorth(val);
        break;
    case Direction::EAST:
        goEast(val);
        break;
    case Direction::SOUTH:
        goSouth(val);
        break;
    case Direction::WEST:
        goWest(val);
        break;

    default:
        break;
    }
}
