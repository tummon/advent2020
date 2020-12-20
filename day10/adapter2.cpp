#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>
#include <chrono>

/**
 * This took me a long time to figure out but I'm very happy with the solution.
 *
 * I imagined this as a tree with X paths to the last node. X was the result
 * that the challenge was looking for.
 *
 * For a long time I was trying to cache all the paths and list them out when I
 * had no need to at all. All I needed was the amount of paths to the end. This saved
 * all copying/moving/allocating pain and I just had to use some longs instead.
 */
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

using Cache = std::unordered_map<int, long>;
long findNumberOfPaths(const std::vector<int> & input, std::vector<int>::const_iterator start, Cache & cache)
{
    long numPaths;

    // We've reached the end
    if (std::next(start) == input.end()) {
        return 1;
    }

    // If we have calculated the number of paths from this node before
    if (cache.contains(*start)) {
        return cache.at(*start);
    }

    // There is a max of 3 nodes we can reach from any single node
    // Check is the next node is not the end, and has a difference of 3 or less.
    if (std::next(start, 1) != input.end() && *std::next(start, 1) - *start <= 3) {
        numPaths = findNumberOfPaths(input, std::next(start, 1), cache);

        // If the first node has a difference of <=3 than check the second node
        if (std::next(start, 2) != input.end() && *std::next(start, 2) - *start <= 3) {
            numPaths += findNumberOfPaths(input, std::next(start, 2), cache);

            // If the first two nodes have a difference of <=3 check the third node
            if (std::next(start, 3) != input.end() && *std::next(start, 3) - *start <= 3) {
                numPaths += findNumberOfPaths(input, std::next(start, 3), cache);
            }
        }
    }

    // Once number of paths is calculated for a node, insert it into the cache so
    // we don't have to recalculate any nodes.
    cache.insert({*start, numPaths});

    return numPaths;
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

    Cache cache;
    auto numPaths = findNumberOfPaths(input, input.begin(), cache);

    std::cout << "Number of solutions = " << numPaths << "\n";

    return 0;
}
