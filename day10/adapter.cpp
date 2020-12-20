#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>

std::vector<int> readInput()
{
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

    // Add 0 as the initial adapter has a rating of 0
    input.push_back(0);

    std::sort(input.begin(), input.end());

    // Add 3 to the highest adapter and push it into the vector
    // as the adapter in your device is always 3 higher than the
    // highest adapter.
    input.push_back(input.back()+3);

    std::unordered_map<int, int> differences;
    differences.insert({1, 0});
    differences.insert({3, 0});

    // Iterate through the list of sorted numbers, increment the
    // value of the difference between each element and it's next
    // element.
    // This is to get the total amount of differences of 1 and 3.
    for (int i=0; i<input.size()-1; i++) {
        int diff = input.at(i+1) - input.at(i);
        differences.at(diff) += 1;
    }

    std::cout << "Differences of 1 = " << differences.at(1) << "\n";
    std::cout << "Differences of 3 = " << differences.at(3) << "\n";
    std::cout << "1 jolt diffs x 3 jolt diffs =  " << differences.at(1)*differences.at(3) << "\n";

    return 0;
}
