#pragma once

#include <unordered_map>
#include <string>

enum class Direction {
    NORTH = 0,
    EAST = 1,
    SOUTH = 2,
    WEST = 3
};

class Ship {
public:
    Ship();
    void parseCommand(const std::string& command);
    void printManhatten();

private:
    void goLeft(int degrees);
    void goRight(int degrees);
    void goForward(int value);
    void goNorth(int value);
    void goSouth(int value);
    void goEast(int value);
    void goWest(int value);

    Direction currDirection;
    int westEast;
    int northSouth;
};
