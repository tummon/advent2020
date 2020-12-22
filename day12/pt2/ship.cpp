#include "ship.hpp"

#include <iostream>


Ship::Ship(): westEast{0}, northSouth{0}
{
}

void Ship::parseCommand(const std::string& command)
{
    char instruction = command.at(0);
    int val = std::stoi(command.substr(1));

    switch (instruction)
    {
    case 'N':
        waypoint.goNorth(val);
        break;
    case 'S':
        waypoint.goSouth(val);
        break;
    case 'E':
        waypoint.goEast(val);
        break;
    case 'W':
        waypoint.goWest(val);
        break;
    case 'L':
        waypoint.rotateLeft(val);
        break;
    case 'R':
        waypoint.rotateRight(val);
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

void Ship::goForward(int val)
{
    northSouth += val * waypoint.northSouth();
    westEast += val * waypoint.westEast();
}
