#include "waypoint.hpp"

Waypoint::Waypoint(): north{1}, south{0}, east{10}, west{0}
{
}

int Waypoint::northSouth()
{
    return south - north;
}

int Waypoint::westEast()
{
    return east - west;
}

void Waypoint::goNorth(int val)
{
    north += val;
}

void Waypoint::goSouth(int val)
{
    south += val;
}

void Waypoint::goWest(int val)
{
    west += val;
}

void Waypoint::goEast(int val)
{
    east += val;
}

void Waypoint::rotateLeft(int degrees)
{
    int change = degrees / 90;

    for (int i = 1; i <= change; i++) {
        doRotateLeft();
    }
}

void Waypoint::rotateRight(int degrees)
{
    int change = degrees / 90;

    for (int i = 1; i <= change; i++) {
        doRotateRight();
    }
}

void Waypoint::doRotateLeft()
{
    int copyNorth = north;
    int copySouth = south;
    int copyEast = east;
    int copyWest = west;

    north = copyEast;
    east = copySouth;
    south = copyWest;
    west = copyNorth;
}

void Waypoint::doRotateRight()
{
    int copyNorth = north;
    int copySouth = south;
    int copyEast = east;
    int copyWest = west;

    north = copyWest;
    east = copyNorth;
    south = copyEast;
    west = copySouth;
}
