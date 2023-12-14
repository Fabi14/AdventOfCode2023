#include <fstream>
#include <string>
#include <ranges>
#include <numeric>
#include <print>
#include <vector>
#include <functional>


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
    }
}

int main()
{
    std::println("Day 1:");
    day01();
    std::println("----------------------------");
}





