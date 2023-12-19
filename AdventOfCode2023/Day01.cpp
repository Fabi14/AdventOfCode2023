#include <fstream>
#include <string>
#include <ranges>
#include <numeric>
#include <print>
#include <vector>
#include <functional>
#include <algorithm>
#include "Days.h"

#include "helper.h"

namespace {
    using namespace  std::views;

    const auto toInt = [](const char c) {return c - '0'; };
    const auto getCalibrationValueFromString()
    {
        return [&](const std::string& s)
            {
                auto numbers = s | filter(isDigit()) | transform(toInt);
                return (numbers | transform([](int i) {return 10 * i; })).front() + (numbers | reverse).front();
            };
    }
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

    const auto getCalibrationValueFromStringWithSpelledOutDigits() {
        return [&](const std::string& s)
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
    }
}


int day01::part1(std::istream&& input)
{
    const auto calibrationValues = istream<std::string>(input) | transform(getCalibrationValueFromString()) | std::ranges::to<std::vector>();
    return std::reduce(calibrationValues.begin(), calibrationValues.end(), 0, std::plus{});
}

int day01::part2(std::istream&& input)
{
    const auto calibrationValues2 = istream<std::string>(input) | transform(getCalibrationValueFromStringWithSpelledOutDigits()) | std::ranges::to<std::vector>();
    return std::reduce(calibrationValues2.begin(), calibrationValues2.end(), 0l, std::plus{});
}



void aoc::day01()
{
    //Part 1
    std::println("Sum of all calibration values: {}", day01::part1(std::ifstream{ "Day01\\01.txt" }));

    //Part 2
    std::println("Sum of all calibration values Part 2: {}", day01::part2(std::ifstream{ "Day01\\01.txt" }));
}

