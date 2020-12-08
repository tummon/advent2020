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

bool isInfiniteLoop(std::vector<Command> commandInput) {
    for (auto it = commandInput.begin(); it != commandInput.end(); it++) {
        if (it->visited)
            return true;

        it->visited = true;

        const std::string& command = it->str;

        if (command.find("nop") != std::string::npos) {
            continue;
        }
        else if (command.find("jmp") != std::string::npos) {
            std::advance(it, std::stoi(command.substr(4))-1);
        }
    }

    return false;
}

/*
    Find out what command needs to be swapped from nop to jmp or vice versa
    to break the infinite loop.
    Brute force by running through the list and checking if an infinite loop
    is detected when we swap a nop/jmp.
*/
int main(int argc, char const *argv[])
{
    auto input = readInput();

    int lineNum = 0;
    for (auto& command: input) {
        if (command.str.find("nop") != std::string::npos) {
            // Swap nop to jmp
            command.str.replace(0, 3, "jmp");

            if (!isInfiniteLoop(input)) {
                std::cout<< "Loop broken by changing line " << lineNum << std::endl;
                std::cout<< "New command: " << command.str << std::endl;
                break;
            }

            // return command to original state if it's still an infinite loop
            command.str.replace(0, 3, "nop");
        }
        else if (command.str.find("jmp") != std::string::npos) {
            // Swap jmp to nop
            command.str.replace(0, 3, "nop");

            if (!isInfiniteLoop(input)) {
                std::cout<< "Loop broken by changing line " << lineNum << std::endl;
                std::cout<< "New command: " << command.str << std::endl;
                break;
            }

            // return command to original state if it's still an infinite loop
            command.str.replace(0, 3, "jmp");
        }
        lineNum++;
    }

    // Calculate accum on newly fixed list of commands
    int accum = 0;
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
