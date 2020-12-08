#include <vector>
#include <iostream>
#include <fstream>
#include <string>

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

int main(int argc, char const *argv[])
{
    auto input = readInput();
    for (const auto& i: input) {
        std::cout << i << "\n";
    }
    return 0;
}
