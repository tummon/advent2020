#pragma once

#include "waypoint.hpp"

#include <string>

class Ship {
public:
    Ship();
    void parseCommand(const std::string& command);
    void printManhatten();

private:
    void goForward(int value);

    Waypoint waypoint;
    int westEast;
    int northSouth;
};
