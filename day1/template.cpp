#include <vector>
#include <iostream>
#include <fstream>

std::vector<int> readInput() {
    std::vector<int> result;
    std::string line;
    std::fstream inputFile {"input"};

    if (inputFile.is_open()) {
        while (getline(inputFile, line)) {
            result.push_back(std::stoi(line));
        }
    }

    return result;
}

int main(int argc, char const *argv[])
{
    auto input = readInput();
    for (const auto& i: input) {
        std::cout << i << "\n";
    }
    return 0;
}
