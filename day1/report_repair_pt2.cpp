#include <unordered_set>
#include <iostream>
#include <fstream>

std::unordered_set<int> readInput() {
    std::unordered_set<int> result;
    std::string line;
    std::fstream inputFile {"input"};

    if (inputFile.is_open()) {
        while (getline(inputFile, line)) {
            result.emplace(std::stoi(line));
        }
    }

    return result;
}

int main(int argc, char const *argv[])
{
    auto input = readInput();
    for (const auto& i: input) {
        for (const auto & j: input) {
            if (i == j)
                continue;

            if (i+j < 2020) {
                int diff = 2020-(i+j);
                if (input.contains(diff)) {
                    std::cout << ( diff * i * j ) << "\n";
                    return 0;
                }
            }
        }
    }
    return 0;
}
