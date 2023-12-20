#include "Days.h"
#include <istream>
#include <string>
#include <ranges>
#include <vector>
#include <print>
#include <algorithm>
#include <numeric>
#include <fstream>
#include <functional>
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

    auto getWinsFromLine()
    {
        return [](auto&& line) ->int {
            const auto lineParts = splitLine(':', '|')(line) 
                | drop(1) 
                | transform(parseNumbersToVector()) 
                | std::ranges::to<std::vector>();
            const std::vector<int>& winningNumbers{ lineParts.at(0) };
            const std::vector<int>& yourNumbers{ lineParts.at(1) };
            return getWins(winningNumbers, yourNumbers);
            };
    }

}

int day04::part1(std::istream&& input)
{
    using namespace  std::views;
    const std::vector<int> wins = istream<Line>(input) 
        | transform([](Line l) {return std::string{ l }; }) 
        | transform(getWinsFromLine()) 
        | std::ranges::to<std::vector>();

    return std::reduce(std::begin(wins), std::end(wins), 0, [](int sum, int points)
        {
            return sum + std::pow(2, points -1);
        });
}

int day04::part2(std::istream&& input)
{
    using namespace  std::views;
    auto vecLines = istream<Line>(input) | std::ranges::to<std::vector>();

    using ScratchcardCounts = std::vector<int>;
    std::pair<int, ScratchcardCounts> startvalue{ 0,{} };
    return std::reduce(std::begin(vecLines), std::end(vecLines), startvalue, [](auto sum, std::string str)
        {
            const auto lineParts = splitLine(':', '|')(str) | drop(1) | transform(parseNumbersToVector()) | std::ranges::to<std::vector>();
            const std::vector<int>& winningNumbers{ lineParts.at(0) };
            const std::vector<int>& yourNumbers{ lineParts.at(1) };

            auto& [totalCount, scratchcardCounts] = sum;

            if (scratchcardCounts.empty())
            {
                scratchcardCounts = ScratchcardCounts(winningNumbers.size(), 1);
            }

            const int currentScratchcardCount = scratchcardCounts.front();
            std::ranges::rotate(scratchcardCounts, std::next(std::begin(scratchcardCounts), 1));
            scratchcardCounts.back() = 1;

            totalCount += currentScratchcardCount;
            const auto wins = getWins(winningNumbers, yourNumbers);
            std::transform(std::begin(scratchcardCounts), std::next(std::begin(scratchcardCounts), wins),
                std::begin(scratchcardCounts), std::bind_front(std::plus{}, currentScratchcardCount));

            return sum;
        }).first;
}

void aoc::day04()
{
    //Part 1
    std::println("Points: {}", day04::part1(std::ifstream{ "04.txt" }));

    //Part 2
    std::println("Total scratchcard count: {}", day04::part2(std::ifstream{ "04.txt"  }));
}