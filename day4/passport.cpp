#include "passport.hpp"

#include <regex>
#include <sstream>


std::vector<std::string> splitStringOnSpaces(std::string&& string)
{
    std::istringstream iss(string);
    std::vector<std::string> vect(std::istream_iterator<std::string>{iss},
                                    std::istream_iterator<std::string>());
    return vect;
}

void Passport::parseString(std::string&& input)
{
    auto vect = splitStringOnSpaces(std::move(input));

    for (auto& keyVal: vect) {
        std::string key = keyVal.substr(0, keyVal.find(":"));
        std::string value = keyVal.substr(keyVal.find(":")+1);

        addDetail(key, value);
    }

}

bool Passport::valid() const
{
    if (details.size() == 8 || details.size() == 7) {
        return verifyWithRegex("byr", "^(19[2-9][0-9]|200[0-2])$")
                && verifyWithRegex("iyr", "^20(1[0-9]|20)$")
                && verifyWithRegex("eyr", "^20(2[0-9]|30)$")
                && verifyWithRegex("hgt", "(^(1[5-8][0-9]|19[0-3])cm$)|(^(59|6[0-9]|7[0-6])in$)")
                && verifyWithRegex("hcl", "^#[a-f0-9]{6}$")
                && verifyWithRegex("ecl", "^(amb|blu|brn|gry|grn|hzl|oth)$")
                && verifyWithRegex("pid", "^[0-9]{9}$");
    }

    return false;
}

void Passport::addDetail(std::string key, std::string value)
{
    details.insert({key, value});
}

bool Passport::verifyWithRegex(const std::string& key, std::string&& regexString)  const
{
    if (!details.contains(key)) {
        return false;
    }

    const std::regex regex{regexString};
    return std::regex_match(details.at(key), regex);
}
