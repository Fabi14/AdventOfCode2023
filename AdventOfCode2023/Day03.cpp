#include <fstream>
#include <string>
#include <ranges>
#include <numeric>
#include <print>
#include <vector>
#include <functional>
#include <algorithm>

#include "Days.h"
using namespace  std::views;
namespace
{
    //bool isPart(char c)
    //{
    //    return !std::isdigit(c) && c != '.';
    //}


    //int part1(const std::vector<std::string>& inputString)
    //{
    //    auto getSumOfOneLine = [](const std::string& top, const std::string& middel, const std::string& bottom) -> int
    //        {
    //            auto isDigit = [](const auto charWithIndex) -> bool
    //                {
    //                    auto [idx, c] = charWithIndex;
    //                    return std::isdigit(c);
    //                };

    //            auto endOfNumber = [](const auto& l, const auto& r) -> bool
    //                {
    //                    auto [leftIdx, leftChar] = l;
    //                    auto [rightCharIdx, rightChar] = r;
    //                    return leftIdx != rightCharIdx - 1;
    //                };


    //            auto hasPartNearby = [&top, &bottom,&middel](auto&& charWithIndex) ->bool
    //                {
    //                    auto [idx, c] = charWithIndex;

    //                    auto checkLineForPart = [idx](const std::string& line) {
    //                        return isPart(line.at(idx))
    //                            || isPart(line.at(idx - 1 >= 0 ? idx - 1 : idx))
    //                            || isPart(line.at(idx + 1 < line.size() ? idx + 1 : idx));
    //                        };

    //                    return checkLineForPart(top) || checkLineForPart(middel) || checkLineForPart(bottom);
    //                };


    //            auto isValidPartNumber = [](auto&& number) -> bool
    //                {
    //                    auto hasPartNearby = number | transform([]()-> bool {return true; } /*hasPartNearby*/);
    //                    return std::reduce(hasPartNearby.begin(), hasPartNearby.end(), false, std::logical_or{});
    //                };


    //            std::vector<std::tuple<std::ptrdiff_t,char>> numbersWithIndex = middel | std::views::enumerate | filter(isDigit) | std::views::chunk_by(endOfNumber) | std::ranges::to<std::vector>();
    //            auto numbers = numbersWithIndex | filter(isValidPartNumber) | transform([](auto&& chunk) -> int
    //                {
    //                    auto numberString = chunk | std::ranges::to<std::string>();
    //                    return std::stoi(numberString);
    //                }) | std::ranges::to<std::vector>();
    //                return std::reduce(numbers.begin(), numbers.end(), 0, std::plus{});
    //        };


    //    std::vector<int> view = inputString | adjacent_transform<3>(getSumOfOneLine) | std::ranges::to<std::vector>();

    //    return std::accumulate(view.begin(), view.end(),0);
    //}

    //int part2(const std::vector<std::string>& inputString)
    //{
    //    return 0;
    //}
}


void aoc::day03()
{
    //std::ifstream inputFile("03.txt");
    //const auto inputString = istream<std::string>(inputFile) | transform([](auto&& s) {return s | std::ranges::to<std::string>(); }) | std::ranges::to<std::vector>();

    //std::println("Sum of all of the part numbers : {}", part1(inputString));


    //std::println("??? : {}", part2(inputString));
}