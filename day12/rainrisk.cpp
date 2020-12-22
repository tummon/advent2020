/**
 * The navigation instructions (your puzzle input) consists of a sequence of single-character actions paired with integer input values.
 * After staring at them for a few minutes, you work out what they probably mean:
 *
 *  Action N means to move north by the given value.
 *  Action S means to move south by the given value.
 *  Action E means to move east by the given value.
 *  Action W means to move west by the given value.
 *  Action L means to turn left the given number of degrees.
 *  Action R means to turn right the given number of degrees.
 *  Action F means to move forward by the given value in the direction the ship is currently facing.
 *
 * The ship starts by facing east. Only the L and R actions change the direction the ship is facing.
 * (That is, if the ship is facing east and the next instruction is N10, the ship would move north 10 units,
 *  but would still move east if the following action were F.)
 *
 * At the end of these instructions, the ship's Manhattan distance
 * (sum of the absolute values of its east/west position and its north/south position)
 * from its starting position is 17 + 8 = 25.
 *
 * Figure out where the navigation instructions lead.
 *  What is the Manhattan distance between that location and the ship's starting position?
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
