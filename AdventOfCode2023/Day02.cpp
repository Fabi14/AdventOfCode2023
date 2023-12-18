#include <fstream>
#include <string>
#include <ranges>
#include <numeric>
#include <print>
#include <vector>
#include <functional>
#include <algorithm>

#include "Day02.h"
using namespace  std::views;
namespace
{
    enum class CubeColor
    {
        blue, red, green
    };

    auto isDigit = [](char c)
        {
            return std::isdigit(c);
        };

    const auto createCube = [&](auto&& s)
        {
            const auto numbers = std::stoi(s | filter(isDigit) | std::ranges::to<std::string>());
            if ((s | std::ranges::to<std::string>()).contains("red"))
            {
                return std::make_pair(CubeColor::red, numbers);
            }

            if ((s | std::ranges::to<std::string>()).contains("blue"))
            {
                return std::make_pair(CubeColor::blue, numbers);
            }

            if ((s | std::ranges::to<std::string>()).contains("green"))
            {
                return std::make_pair(CubeColor::green, numbers);
            }
            return std::make_pair(CubeColor::green, numbers);
        };

    constexpr auto createCubes = [&](auto&& s)
        {
            return s | lazy_split(',') | transform(createCube);
        };

    const auto isNumberOfCubesPossible = [](std::pair<CubeColor, int>&& s)
        {
            return s.first == CubeColor::blue && s.second <= 14 ||
                s.first == CubeColor::green && s.second <= 13 ||
                s.first == CubeColor::red && s.second <= 12;
        };

    const auto isPossibleGame = [&](const std::string& input)
        {
            auto games = input | drop_while([](char c) {return c != ':'; }) | lazy_split(';') | std::ranges::to<std::vector>();
            auto cubesOfGames = games | transform(createCubes) | join;
            auto areGamesPosible = cubesOfGames | transform(isNumberOfCubesPossible) | std::ranges::to<std::vector>();

            return std::reduce(areGamesPosible.begin(), areGamesPosible.end(), true, std::logical_and{});
        };

    const auto getGameNumber = [&](auto&& s)
        {
            const auto gameNumberString = s | drop(std::string{ "Game" }.size() - 1) | take_while([](char c) {return c != ':'; }) | filter(isDigit) | std::ranges::to<std::string>();
            return std::stoi(gameNumberString);
        };

    const auto powerOfMinValues = [&](const std::string& input) ->int
        {
            auto games = input | drop_while([](char c) {return c != ':'; }) | lazy_split(';') | std::ranges::to<std::vector>();
            auto cubesOfGames = games | transform(createCubes) | join;
            auto vecCubesOfGames = cubesOfGames | std::ranges::to<std::vector>();
            
            const auto endRed = std::partition(vecCubesOfGames.begin(), vecCubesOfGames.end(), [](const std::pair<CubeColor, int>& s) {return  s.first == CubeColor::red; });
            const auto endGreen = std::partition(endRed, vecCubesOfGames.end(), [](const std::pair<CubeColor, int>& s) {return  s.first == CubeColor::green; });

            const auto max = [](int max, const std::pair<CubeColor, int>& s) {return  s.second > max ? s.second : max;  };

            const int minRed = std::reduce(vecCubesOfGames.begin(), endRed, 0, max);
            const int minGreen = std::reduce(endRed, endGreen, 0, max);
            const int minBlue = std::reduce(endGreen, vecCubesOfGames.end(), 0, max);


            return minRed * minGreen * minBlue;
        };
     

    int part1(const std::string& inputString)
    {
        const std::vector<std::string> inputStringSplitedPerGame = inputString | lazy_split('G') | drop(1) | transform([](auto&& s) {return s | std::ranges::to<std::string>(); }) | std::ranges::to<std::vector>();
        const std::vector<int>  numbersOfPossibleGames = inputStringSplitedPerGame | filter(isPossibleGame) | transform(getGameNumber) | std::ranges::to<std::vector>();
        return std::reduce(numbersOfPossibleGames.begin(), numbersOfPossibleGames.end(), 0, std::plus{});
    }

    int part2(const std::string& inputString)
    {
        const std::vector<std::string> inputStringSplitedPerGame = inputString | lazy_split('G') | drop(1) | transform([](auto&& s) {return s | std::ranges::to<std::string>(); }) | std::ranges::to<std::vector>();
        const auto powers = inputStringSplitedPerGame | transform(powerOfMinValues) | std::ranges::to<std::vector>();
        return std::reduce(powers.begin(), powers.end(), 0, std::plus{});
    }
}



void day02()
{
    std::ifstream inputFile("02.txt");
    const auto inputString = istream<std::string>(inputFile) | join_with(' ') | std::ranges::to<std::string>();
    
    std::println("Sum of the IDs of possible games : {}", part1(inputString));

    std::println("Sum of the pover of these sets : {}", part2(inputString));
}