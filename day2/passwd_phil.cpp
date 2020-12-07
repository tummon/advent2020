#include <string>
#include <vector>
#include <iostream>
#include <fstream>

std::vector<std::string> readInput() {
    std::vector<std::string> result;
    std::string line;
    std::fstream inputFile {"input"};

    if (inputFile.is_open()) {
        while (getline(inputFile, line)) {
            result.push_back(line);
        }
    }

    return result;
}

struct Password
{
    int low;
    int high;
    std::string policy_char;
    std::string password;

    bool valid()
    {
        int num = num_policy_char_in_password();
        return num <= high && num >= low;
    }

private:
    int num_policy_char_in_password()
    {
        int count = 0;
        for (int i=0; i<password.length(); i++) {
            if (password.at(i) == policy_char.at(0))
                count++;
        }
        return count;
    }

};

Password tokenize(std::string const &str)
{
    Password pass;

    int last = 0;
    int next = str.find_first_of('-');
    pass.low = std::stoi(str.substr(last, next));

    last = next+1;
    next = str.substr(last).find_first_of(' ');
    pass.high = std::stoi(str.substr(last, next));

    pass.policy_char = str.at(str.find(':')-1);

    pass.password = str.substr(str.find_last_of(' ')+1);

    return pass;
}

int main(int argc, char const *argv[])
{
    auto input = readInput();
    int counter = 0;

    for (const auto& i: input) {
        auto pass =tokenize(i);
        if (pass.valid())
            counter++;
    }

    std::cout << "Count: " << counter << "\n";

    return 0;
}
