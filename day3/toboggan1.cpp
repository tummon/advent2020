#include <vector>
#include <iostream>
#include <fstream>

std::vector<std::vector<char>> readInput() {
    std::vector<std::vector<char>> result;
    std::string line;
    std::fstream inputFile {"input"};

    if (inputFile.is_open()) {
        while (getline(inputFile, line)) {
            std::vector<char> vec;
            std::copy(line.begin(), line.end(), std::back_inserter(vec));
            result.push_back(vec);
        }
    }

    return result;
}

int main(int argc, char const *argv[])
{
    auto input = readInput();
    int index = 0;
    int counter = 0;
    std::cout << "input length " << input.size() << "\n";
    std::cout << "in length " << input[0].size() << "\n";
    for (const auto& in: input){
        if (in.at(index) == '#') {
            counter++;
        }
        index = (index+3) % (in.size());
    }

    std::cout << "num trees = " << counter << "\n";
    return 0;
}
