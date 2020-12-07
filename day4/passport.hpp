#pragma once

#include <regex>
#include <string>
#include <unordered_map>

class Passport
{
public:
    void parseString(std::string&& input);
    bool valid() const;

private:
    void addDetail(std::string key, std::string value);
    bool verifyWithRegex(const std::string& key, std::string&& regexString) const;

    std::unordered_map<std::string, std::string> details;
};
