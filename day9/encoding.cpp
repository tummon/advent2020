#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include <set>

std::vector<long> readInput() {
    std::vector<long> result;
    std::string line;
    std::fstream inputFile {"input"};

    if (inputFile.is_open()) {
        while (getline(inputFile, line)) {
            result.push_back(std::stol(line));
        }
    }

    return result;
}

/*
    For a sliding window of 26 numbers, check if the 26th number can
    be made by summing any 2 of the previous 25 numbers.

    return the 26th number if it can't be made by summing any 2 of the
    previous 25 numbers.

    This is a very greedy solution. Ideally you could keep a large set of
    the sums cached. Maybe I'll come back to this...doubtful...
*/
long getInvalidNum(const std::vector<long>& input)
{
    long invalidNum = 0;

    for (int start = 0; start+25<input.size(); start++) {
        int end = start+25;
        std::set<long> sumSet {};
        // Calculate all the sums of the permutations of pairs
        for (int i=start; i<end-1; i++) {
            for (int j=i; j<end; j++) {
                sumSet.insert(input.at(i) + input.at(j));
            }
        }
        // if the current "next" number is not in the set of sums, it's invalid
        if (!sumSet.contains(input.at(end))) {
            return input.at(end);
        }
    }

    // I expect there to be an invalid num
    assert(invalidNum != 0);
    return invalidNum;
}

/*
    Calculate the set (all numbers will be different) of consecutive numbers that
    sum up to the invalid number.

    Return the sum of the maximum and minimum numbers in the set. (First and last of sorted set)
*/
long calculateEncryptionWeakness(const std::vector<long>& input, long invalidNum) {
    for (int start = 0; start+25<input.size(); start++) {
        int end = start+25;

        std::set<long> usedNumbers {};
        long totalSum = 0;

        // Get total sum of sliding window of 25 numbers.
        // This should probably not be limited to 25 numbers.
        // Technically it can be more than 25 consectutive numbers
        // but it seems it was less than 25 in this case ¯\_(ツ)_/¯
        for (int i=start; i<end; i++) {
            totalSum += input.at(i);
            usedNumbers.insert(input.at(i));
            if (totalSum > invalidNum) {
                break;
            }
            else if (totalSum == invalidNum) {
                long max = *std::prev(usedNumbers.end());
                long min = *usedNumbers.begin();
                return max+min;
            }
        }
    }

    // I expect to return before here... I don't think this is normal coding practise but I'm tired...
    assert(false);
    return 0;
}

/*
    Tired this evening and didn't even attempt a non brute force method :)

    Not my best effort but still 2 gold stars...
*/
int main(int argc, char const *argv[])
{
    auto input = readInput();
    std::cout << "Encryption Weakness = " << calculateEncryptionWeakness(input, getInvalidNum(input)) << std::endl;
    return 0;
}
