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
}

int main()
{
    std::println("Day 1:");
    day01();
    std::println("----------------------------");
}





