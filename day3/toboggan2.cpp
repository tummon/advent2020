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

int numTrees(const std::vector<std::vector<char>>& vec, int right, int down)
{
    int index = 0;
    int counter = 0;

    for (int i=0; i<vec.size(); i+=down){
        if (vec[i].at(index) == '#') {
            counter++;
        }
        index = (index+right) % (vec[i].size());
    }

    return counter;
}

int main(int argc, char const *argv[])
{
    auto input = readInput();

    std::vector<int> results;

    results.emplace_back(numTrees(input, 1, 1));
    results.emplace_back(numTrees(input, 3, 1));
    results.emplace_back(numTrees(input, 5, 1));
    results.emplace_back(numTrees(input, 7, 1));
    results.emplace_back(numTrees(input, 1, 2));

    long output = 1;
    for (const auto& num: results) {
        output *= num;
    }

    std::cout << "Result = " << output << "\n";
    return 0;
}
