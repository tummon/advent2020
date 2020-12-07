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
        if (input.contains(2020-i)) {
            std::cout << (i*(2020-i)) << "\n";
            break;
        }
    }
    return 0;
}
