#include "Days.h"
#include <istream>
#include <string>
#include <ranges>
#include <vector>
#include <print>
#include <algorithm>
#include <numeric>
#include <fstream>
#include "helper.h"

namespace {
    using namespace  std::views;
    struct Line {
        std::string line;

        operator std::string() {
            return line;
        }
    };
    std::istream& operator>>(std::istream& os, Line& l)
    {
        std::getline(os, l.line);
        return os;
    }

    int getWins(const std::vector<int>& winningNumbers, const std::vector<int>& yourNumbers)
    {
        return std::reduce(winningNumbers.begin(), winningNumbers.end(), 0, [&](int totalPoints, int winningNumber)
            {
                if (std::ranges::contains(yourNumbers, winningNumber))
                {
                    return ++totalPoints;
                }
                return totalPoints;
            });
    }

}

int day04::part1(std::istream&& input)
{
    using namespace  std::views;
    auto splitedLines = istream<Line>(input) | std::ranges::to<std::vector>();
    std::vector<std::string> s = splitedLines | transform([](Line& l)->std::string {return  l.line; }) | std::ranges::to<std::vector>();



    return std::reduce(std::begin(s), std::end(s), 0, [](int sum, std::string& str)
        {
            std::vector<std::string> lineParts = splitLine(':', '|')(str) | std::ranges::to<std::vector>();
            const std::vector<int> winningNumbers{  parseNumbersToVector()(lineParts.at(1)) };
            std::vector<int> yourNumbers{ parseNumbersToVector()(lineParts.at(2)) };

            return sum + std::pow(2, getWins(winningNumbers, yourNumbers)-1);
        });
}

int day04::part2(std::istream&& input)
{
    using namespace  std::views;
    auto splitedLines = istream<Line>(input) | std::ranges::to<std::vector>();
    std::vector<std::string> s = splitedLines | transform([](Line& l)->std::string {return  l.line; }) | std::ranges::to<std::vector>();


    std::pair<int, std::vector<int>> startvalue{ 0,{} };
    return std::reduce(std::begin(s), std::end(s), startvalue, [](auto sum, std::string& str)
        {
            std::vector<std::string> lineParts = splitLine(':', '|')(str) | std::ranges::to<std::vector>();
             std::vector<int> winningNumbers{ parseNumbersToVector()(lineParts.at(1)) };
            std::vector<int> yourNumbers{ parseNumbersToVector()(lineParts.at(2)) };

            int factor = 1;
            if (sum.second.empty())
            {
                sum.second = std::vector<int>(winningNumbers.size(),1);
            }
            else
            {
                factor = sum.second.front();
                sum.second.erase(sum.second.begin());
                sum.second.push_back(1);
            }
            sum.first += factor;
            auto wins = getWins(winningNumbers, yourNumbers);
            for (int i = 0; i < wins; ++i)
            {
                sum.second.at(i) += factor;
            }
            return sum;
        }).first;
}



void aoc::day04()
{
    //Part 1
    std::println(" {}", day04::part1(std::ifstream{ "04.txt" }));

    ////Part 2
    std::println("{}", day04::part2(std::ifstream{ "04.txt"  }));
}