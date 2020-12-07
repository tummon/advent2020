#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include <unordered_set>

int sumAnswers() {
    std::string line;
    std::fstream inputFile {"input"};

    int sum = 0;

    if (inputFile.is_open()) {
        std::unordered_set<char> answers;
        while (getline(inputFile, line)) {
            if (line == "") {
                sum += answers.size();
                answers.clear();
            }
            else {
                for (const auto& letter: line) {
                    answers.insert(letter);
                }
            }
        }

        // No empty line at end
        sum += answers.size();
    }

    return sum;
}

int main(int argc, char const *argv[])
{
    auto input = sumAnswers();
    std::cout << input << std::endl;
    return 0;
}
