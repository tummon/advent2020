#include <vector>
#include <iostream>
#include <fstream>
#include <string>

using Seating = std::vector<std::vector<char>>;
Seating readInput() {
    Seating result;
    std::string line;
    std::fstream inputFile {"/Users/atummon/dev/personal/advent2020/day11/input"};

    if (inputFile.is_open()) {
        while (getline(inputFile, line)) {
            result.emplace_back(std::vector<char>(line.begin(), line.end()));
        }
    }

    return result;
}

// Instead of considering just the eight immediately adjacent seats,
// consider the first seat in each of those eight directions.
int countOccupiedNeighbours(const Seating & buffer, int row, int col)
{
    int count = 0;

    // (-1, -1)   (-1, 0)    (-1, 1)
    // ( 0, -1)  (row, col)  ( 0, 1)
    // ( 1, -1)   ( 1, 0)    ( 1, 1)
    for (int i = -1; i<=1; i++) {
        for (int j = -1; j<=1; j++) {
            // Don't check self
            if (i == 0 && j == 0)
                continue;

            // Use ii and jj to continuously move in the direction
            bool finished = false;
            int ii = i;
            int jj = j;
            // While we haven't reached a seat or gone out of bounds
            while (true) {
                bool rowOutOfBounds = (row+ii < 0) || (row+ii > buffer.size()-1);
                bool colOutOfBounds = (col+jj < 0) || (col+jj > buffer.at(0).size()-1);

                if (rowOutOfBounds || colOutOfBounds) {
                    break;
                }

                // If empty seat break and don't increment count
                if (buffer.at(row+ii).at(col+jj) == 'L') {
                    break;
                }

                // If seat occupied break and increment count
                if (buffer.at(row+ii).at(col+jj) == '#') {
                    count++;
                    break;
                }

                // Move one seat in the given direction
                ii += i;
                jj += j;
            }

        }
    }
    return count;
}

bool doRound(Seating& input) {
    // Use a back buffer so we don't modify the seats
    // that we are using to calculate.
    auto backBuffer = input;

    for (int row=0; row<input.size(); row++) {
        for (int col=0; col<input.at(row).size(); col++) {

            // No seat
            if (input.at(row).at(col) == '.')
                continue;

            int count = countOccupiedNeighbours(input, row, col);

            if (input.at(row).at(col) == 'L' && count == 0)
                backBuffer.at(row).at(col) = '#';
            if (input.at(row).at(col) == '#' && count >= 5)
                backBuffer.at(row).at(col) = 'L';
        }
    }

    // If the new seating is the same as the previous
    // we are finished.
    if (backBuffer == input)
        return true;

    input = backBuffer;
    return false;
}

long countTotalOccupied(const Seating& input) {
    long count = 0;

    for (const auto& row: input) {
        for (const auto& col: row) {
            if (col == '#')
                count++;
        }
    }

    return count;
}

int main(int argc, char const *argv[])
{
    auto input = readInput();

    bool finished = false;
    while (!finished) {
        finished = doRound(input);
    }

    std::cout << "Total occupied: " << countTotalOccupied(input) << "\n";

    return 0;
}
