#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include <set>

int sumGroup(std::vector<std::set<char>>& group)
{
    int sum = 0;

    // Compare against one person
    auto comparison = group.back();
    group.pop_back();

    // For each letter in the comparison,
    // check if each other person in the group
    // answered that question yes
    for (const auto& letter: comparison) {
        bool letterInAll = true;

        for (const auto& person: group) {
            if (!person.contains(letter)) {
                letterInAll = false;
                break;
            }
        }

        if (letterInAll) {
            sum++;
        }
    }

    return sum;
}

int sumAnswers() {
    std::string line;
    std::fstream inputFile {"input"};

    int sum = 0;
    std::vector<std::set<char>> group;

    if (inputFile.is_open()) {

        while (getline(inputFile, line)) {
            if (line == "") { // Group finished
                sum += sumGroup(group);
                group.clear();
            }
            else { // Add person to group
                std::set<char> personAnswers (line.begin(), line.end());
                group.push_back(personAnswers);
            }
        }

        // No empty line at end so need to sum the last group
        sum += sumGroup(group);
    }

    return sum;
}

int main(int argc, char const *argv[])
{
    auto sum = sumAnswers();
    std::cout << sum << std::endl;
    return 0;
}
