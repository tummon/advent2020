#include <vector>
#include <iostream>
#include <fstream>
#include <string>

struct Command {
    std::string str;
    bool visited = false;
};

std::vector<Command> readInput() {
    std::vector<Command> result;
    std::string line;
    std::fstream inputFile {"input"};

    if (inputFile.is_open()) {
        while (getline(inputFile, line)) {
            result.push_back(Command{line, false});
        }
    }

    return result;
}

/*
    Uses a simple bool to detect if a command was already visited.
    Iterators fit nicely for the jmp command.
*/
int main(int argc, char const *argv[])
{
    int accum = 0;
    auto input = readInput();

    for (auto it = input.begin(); it != input.end(); it++) {
        // Break if loop detected
        if (it->visited)
            break;

        it->visited = true;

        const std::string& command = it->str;

        if (command.find("nop") != std::string::npos) {
            continue;
        }
        if (command.find("acc") != std::string::npos) {
            accum += std::stoi(command.substr(4));
        }
        if (command.find("jmp") != std::string::npos) {
            std::advance(it, std::stoi(command.substr(4))-1);
        }

    }

    std::cout << "Accum = " << accum << std::endl;
    return 0;
}
