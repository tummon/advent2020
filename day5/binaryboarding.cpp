#include <vector>
#include <iostream>
#include <string>
#include <fstream>
#include <numeric>
#include <set>
#include <bitset>

std::vector<std::string> readInput() {
    std::vector<std::string> result;
    std::string line;
    std::fstream inputFile {"input"};

    if (inputFile.is_open()) {
        while (getline(inputFile, line)) {
            result.push_back(line);
        }
    }

    return result;
}

int calculateRow(const std::string& boardingPass)
{
    std::string rowString = boardingPass.substr(0, 7);
    std::string binary;

    int high = 127;
    int low = 0;
    int midpoint = 0;
    int guess = 0;


    for (const auto& letter: rowString) {
        midpoint = (high+low) / 2;
        if (letter == 'F') {
            high = midpoint;
            guess = high;

            binary += "0";
        }
        else if (letter == 'B') {
            low = midpoint+1;
            guess = low;

            binary += "1";
        }
    }

    // Translating straight to binary works too!
    std::cout << "row: " << std::bitset<7>(binary).to_ulong() << "\n";

    return guess;
}

int calculateColumn(const std::string& boardingPass)
{
    std::string columnString = boardingPass.substr(7);
    std::string binary;

    int high = 7;
    int low = 0;
    int midpoint = 0;
    int guess = 0;

    for (const auto& letter: columnString) {
        midpoint = (high+low) / 2;
        if (letter == 'L') {
            high = midpoint;
            guess = high;

            binary += "0";
        }
        else if (letter == 'R') {
            low = midpoint+1;
            guess = low;

            binary += "1";
        }
    }

    // Translating straight to binary works too!
    std::cout << "col: " << std::bitset<3>(binary).to_ulong() << "\n";

    return guess;
}

int calculateSeatId(const std::string& boardingPass)
{
    return (calculateRow(boardingPass) * 8) + calculateColumn(boardingPass);
}

int main(int argc, char const *argv[])
{
    auto input = readInput();
    int highestId = 0;
    std::set<int> seats;

    for (const auto& i: input) {
        int seatId = calculateSeatId(i);
        seats.insert(seatId);
        if (seatId > highestId)
            highestId = seatId;
    }

    std::cout << "Highest ID: " << highestId << std::endl;

    for (int i: seats) {
        if (!seats.contains(i+1) && seats.contains(i+2)) {
            std::cout << "Your seat is " << i+1 << std::endl;
            break;
        }
    }

    return 0;
}
