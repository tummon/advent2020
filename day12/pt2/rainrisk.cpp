/**
 * Before you can give the destination to the captain,
 * you realize that the actual action meanings were printed on the back of the instructions the whole time.
 *
 * Almost all of the actions indicate how to move a waypoint which is relative to the ship's position:
 *  Action N means to move the waypoint north by the given value.
 *  Action S means to move the waypoint south by the given value.
 *  Action E means to move the waypoint east by the given value.
 *  Action W means to move the waypoint west by the given value.
 *  Action L means to rotate the waypoint around the ship left (counter-clockwise) the given number of degrees.
 *  Action R means to rotate the waypoint around the ship right (clockwise) the given number of degrees.
 *  Action F means to move forward to the waypoint a number of times equal to the given value.
 *
 * The waypoint starts 10 units east and 1 unit north relative to the ship. The waypoint is relative to the ship;
 * that is, if the ship moves, the waypoint moves with it.
 *
 *
 * After these operations, the ship's Manhattan distance from its starting position is 214 + 72 = 286.
 *
 * Figure out where the navigation instructions actually lead.
 * What is the Manhattan distance between that location and the ship's starting position?
 */

#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>

#include "ship.hpp"

std::vector<std::string> readInput() {
    std::vector<std::string> result;
    std::string line;
    std::fstream inputFile {"/Users/atummon/dev/personal/advent2020/day12/input"};

    if (inputFile.is_open()) {
        while (getline(inputFile, line)) {
            result.push_back(line);
        }
    }

    return result;
}

int main(int argc, char const *argv[])
{
    auto input = readInput();
    Ship ship;
    for (const auto& command: input) {
        ship.parseCommand(command);
    }

    ship.printManhatten();
    return 0;
}
