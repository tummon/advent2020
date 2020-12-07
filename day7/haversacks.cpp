#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <regex>

using SubBags = std::unordered_map<std::string, int>;
using RuleMap = std::unordered_map<std::string, SubBags>;

/*
    Basically just grab the first two words
*/
std::string getRuleMainBag(const std::string& rule)
{
    auto firstSpacePos = rule.find_first_of(" ");
    auto secondSpacePos = rule.find(" ", firstSpacePos+1);
    return rule.substr(0, secondSpacePos);
}


SubBags getRuleSubBags(const std::string& rule)
{
    // rule = pale salmon bags contain 2 mirrored cyan bags, 4 vibrant blue bags.

    SubBags result;

    // Get everything after contain
    // e.g. 2 mirrored cyan bags, 4 vibrant blue bags.
    std::string subRuleDelmiter = "contain ";
    auto startPos = rule.find(subRuleDelmiter);
    auto subBagsStr = rule.substr(startPos + subRuleDelmiter.length());

    // This regex will pull out the number of bags, and the 2 word colour
    // and insert them into our SubBags hash map.
    std::regex regx("(\\d) (\\w* \\w*) bags?[.,]");
    std::smatch sm;
    while (std::regex_search(subBagsStr, sm, regx)) {
        if (sm.ready()) {
            result.insert({sm[2].str(), std::stoi(sm[1].str())});
            subBagsStr = sm.suffix().str();
        }
    }
    return result;
}

void buildRuleMap(RuleMap& ruleMap, const std::string& rule)
{
    std::string mainBag = getRuleMainBag(rule);
    SubBags subBags = getRuleSubBags(rule);

    ruleMap.insert({mainBag, subBags});
}

/*
    Recursive function to find out if carryBag is in bagToCheck.
    Using memoization to avoid recalculating some bags.
    Would possibly overload this so it could be called without passing
    in the previous bags sets, which would just instantiate them and pass it in.
*/
bool isValidBag(std::unordered_set<std::string>& previousValidBags,
                std::unordered_set<std::string>& previousInvalidBags,
                const RuleMap& ruleMap,
                std::string bagToCheck,
                std::string carryBag)
{
    // Collection of bags within the current bagToCheck
    SubBags subBags = ruleMap.at(bagToCheck);

    if (subBags.contains(carryBag)) {
        previousValidBags.insert(bagToCheck);
        return true;
    }

    // If carryBag not directly within bagToCheck, recursively check
    // the bags within bagToCheck. Using memoization to cache the bags
    // we've already checked.
    for (const auto& subBag: subBags) {
        if (previousValidBags.contains(subBag.first)) {
            return true;
        }
        else if (previousInvalidBags.contains(subBag.first)) {
            continue;
        }
        else if (isValidBag(previousValidBags, previousInvalidBags, ruleMap, subBag.first, carryBag)){
            return true;
        }
    }

    previousInvalidBags.insert(bagToCheck);
    return false;
}

/*
    Iterate through rules, and calculate the amount which contain carryBag
*/
int findNumValidBags(std::unordered_set<std::string>& previousValidBags,
                     std::unordered_set<std::string>& previousInvalidBags,
                     const RuleMap& ruleMap,
                     std::string carryBag)
{
    int numValidBags = 0;
    for (const auto& rule: ruleMap) {
        if (isValidBag(previousValidBags, previousInvalidBags, ruleMap, rule.first, carryBag)) {
            numValidBags++;
        }
    }
    return numValidBags;
}

/*
    Recursive function to count the amount of bags within.
    Using memoization to avoid recalculating some bags.
    Would possibly overload this so it could be called without passing in memo,
    which would just instantiate memo and pass it in.
*/
int calculateBagsWithin(std::unordered_map<std::string, int>& memo, const RuleMap& ruleMap, std::string bagToCheck)
{
    SubBags subBags = ruleMap.at(bagToCheck);
    int sum = 0;
    if (subBags.empty()) {
        return 0;
    }
    for (const auto& bag: subBags) {
        if (memo.contains(bag.first)) {
            sum += (memo.at(bag.first) * bag.second) + bag.second;
        } else {
            int bagsWithin = calculateBagsWithin(memo, ruleMap, bag.first);
            memo.insert({bag.first, bagsWithin});
            sum += (bagsWithin * bag.second) + bag.second;
        }
    }

    return sum;
}

/*
    Take the input from a text file and build the map of rules.
*/
RuleMap readInput()
{
    RuleMap ruleMap;
    std::string line;
    std::fstream inputFile {"input"};

    if (inputFile.is_open()) {
        while (getline(inputFile, line)) {
            buildRuleMap(ruleMap, line);
        }
    }

    return ruleMap;
}

int main(int argc, char const *argv[])
{
    const auto& ruleMap = readInput();

    std::unordered_set<std::string> previousValidBags {};
    std::unordered_set<std::string> previousInvalidBags {};
    int validbags = findNumValidBags(previousValidBags, previousInvalidBags, ruleMap, "shiny gold");
    std::cout << "Number of bags with shiny gold = " << validbags << "\n";

    std::unordered_map<std::string, int> memo {};
    int bagsWithin = calculateBagsWithin(memo, ruleMap, "shiny gold");
    std::cout << "Bags within shiny gold = " << bagsWithin << "\n";

    return 0;
}
