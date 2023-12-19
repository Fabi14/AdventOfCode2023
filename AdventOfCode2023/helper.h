#pragma once
#include <istream>
#include <string>
#include <ranges>
#include <vector>

inline auto isDigit()
{
    return [](const char c)
        {
            return std::isdigit(c);
        };
}

inline auto toNumber()
{
    return [](auto&& range)
        {
            std::string s = range | std::ranges::to<std::string>();
            return std::stoi(s);
        };
}

inline auto notEmpty()
{
    return [](auto&& range) {return std::ranges::distance(range) > 0; };
}

inline auto parseNumbersToVector() {
    return [](const std::string& s)
        {
            using namespace  std::views;
            return s | split(' ') | filter(notEmpty()) | transform(toNumber()) | std::ranges::to<std::vector>();
        };
}


inline auto splitLine()
{
    using namespace  std::views;
    return [](auto&& view) { return view | split('*'); };
}

auto splitLine(auto firstdelimiter, auto... delimiters) {
    return [firstdelimiter, delimiters...](auto&& view)
        {
            using namespace  std::views;
            return view 
                | split(firstdelimiter)  
                | transform(splitLine(delimiters...)) 
                | join 
                | std::views::transform(std::ranges::to<std::string>()) ;
        };
}