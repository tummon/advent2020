#include "passport.hpp"
#include <vector>
#include <iostream>
#include <string>
#include <fstream>

std::vector<Passport> readInput()
{
    std::vector<Passport> result;
    std::string line;
    std::fstream inputFile {"input"};

    if (inputFile.is_open()) {
        Passport passport;

        while (getline(inputFile, line)) {
            if (line == "") {
                // Finished passport, push to vector and set new passport
                result.push_back(passport);
                passport = Passport{};
            } else {
                passport.parseString(std::move(line));
            }
        }

        // Last passport won't have a new line
        result.push_back(passport);
    }

    return result;
}

int main(int argc, char const *argv[])
{
    auto input = readInput();

    int counter = 0;
    for (const auto& passport: input) {
        if (passport.valid())
            counter ++;
    }

    std::cout << "Valid passports: " << counter << "\n";
    return 0;
}
