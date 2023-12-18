#include <fstream>
#include <string>
#include <ranges>
#include <numeric>
#include <print>
#include <vector>
#include <functional>
#include <algorithm>

namespace {
    void day01()
    {
        //Part 1
        using namespace  std::views;

        const auto isDigit = [](const char c) {return std::isdigit(c); };
        const auto toInt = [](const char c) {return c - '0'; };
        const auto getCalibrationValueFromString = [&](const std::string& s)
            {
                auto numbers = s | filter(isDigit) | transform(toInt);
                return (numbers | transform([](int i) {return 10 * i; })).front() + (numbers | reverse).front();
            };

        std::ifstream inputFile("Day01\\01.txt");
        const auto calibrationValues = istream<std::string>(inputFile) | transform(getCalibrationValueFromString) | std::ranges::to<std::vector>();
        const int sum = std::reduce(calibrationValues.begin(), calibrationValues.end(), 0, std::plus{});

        std::println("Sum of all calibration values: {}", sum);

        //Part 2
        const std::vector<std::tuple<std::string, std::string, long>> vec{
            {"one","1",1}
            ,{"two","2",2}
            ,{"three","3",3}
            ,{"four","4",4}
            ,{"five","5",5}
            ,{"six","6",6}
            ,{"seven","7",7}
            ,{"eight","8",8}
            ,{"nine","9",9}
        };

        const auto getCalibrationValueFromStringWithSpelledOutDigits = [&](const std::string& s)
            {
                auto view = vec | transform([&](const auto& tuple) {return std::min(s.find(std::get<0>(tuple)), s.find(std::get<1>(tuple))); });
                const int firstIndex = std::ranges::min_element(view) - std::begin(view);

                auto viewLast = vec | transform([&](const auto& tuple)
                    {
                        auto lastIndex = [&s](const std::string& subString) -> int
                            {
                                const auto index{ (s).rfind(subString) };
                                return  index == s.npos ? -1 : index;
                            };
                        return std::max(lastIndex(std::get<0>(tuple)), lastIndex(std::get<1>(tuple))); }
                );
                const int last = std::ranges::max_element(viewLast) - std::begin(viewLast);

                return std::get<2>(vec.at(firstIndex)) * 10 + std::get<2>(vec.at(last));
            };

        std::ifstream inputFile2("Day01\\01.txt");
        const auto calibrationValues2 = istream<std::string>(inputFile2) | transform(getCalibrationValueFromStringWithSpelledOutDigits) | std::ranges::to<std::vector>();
        const long sum2 = std::reduce(calibrationValues2.begin(), calibrationValues2.end(), 0l, std::plus{});
        std::println("Sum of all calibration values Part 2: {}", sum2);
    }

    void day02()
        {
            using namespace  std::views;

            enum class CubeColor
            {
                blue, red, green
            };

            const auto isDigit = [](char c) {return std::isdigit(c); };
            auto createCube = [&](auto&& s)
                {
                    const auto numbers = std::stoi(s | filter(isDigit) | std::ranges::to<std::string>());
                    if ((s | std::ranges::to<std::string>()).contains("red"))
                    {
                        return std::make_pair(CubeColor::red, numbers) ;
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

            auto createCubes = [&](auto&& s)
                {
                    return s | lazy_split(',') | transform(createCube);
                };

            auto isNumberOfCubesPossible = [&](std::pair<CubeColor, int>&& s)
                {
                   return s.first == CubeColor::blue && s.second <= 14 ||
                        s.first == CubeColor::green && s.second <= 13 ||
                       s.first == CubeColor::red && s.second <= 12;
                };

            const auto isPossibleGame = [&](const std::string& input)
                {
                    auto games = input | drop_while([](char c) {return c != ':'; }) | lazy_split(';') | std::ranges::to<std::vector>();
                    auto cubesOfGames = games | transform(createCubes) | join;
                    auto test = cubesOfGames  | std::ranges::to<std::vector>();
                    auto areGamesPosible = cubesOfGames  | transform(isNumberOfCubesPossible) | std::ranges::to<std::vector>();

                    return std::reduce(areGamesPosible.begin(), areGamesPosible.end(), true, std::logical_and{});
                };

            auto getGameNumber = [&](auto&& s)
                {
                    const auto gameNumberString = s | drop(std::string{ "Game" }.size()-1) | take_while([](char c) {return c != ':'; }) | filter(isDigit) | std::ranges::to<std::string>();
                    return std::stoi(gameNumberString);
                };

            std::ifstream inputFile("02.txt");
            const auto test = istream<std::string>(inputFile) | join_with(' ') | std::ranges::to<std::string>();
            std::vector<std::string> numbersOfPossibleGamesSritng = test | lazy_split('G') | drop(1) | take_while([](auto&& view) {return view.begin() != view.end(); }) | transform([](auto&& s) {return s | std::ranges::to<std::string>(); }) | std::ranges::to<std::vector>();
                
              auto  numbersOfPossibleGames =  numbersOfPossibleGamesSritng | filter(isPossibleGame) | transform(getGameNumber) | std::ranges::to<std::vector>();
            const int sum =  std::reduce(numbersOfPossibleGames.begin(), numbersOfPossibleGames.end(), 0, std::plus{});

            std::println("Sum of the IDs of possible games : {}", sum);
        }
}

int main()
{
    std::println("Day 1:");
    day01();
    std::println("----------------------------");

    std::println("Day 2:");
    day02();
    std::println("----------------------------");
}





