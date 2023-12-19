#include "pch.h"
#include "../AdventOfCode2023/Days.h"
#include "../AdventOfCode2023/helper.h"

#include <vector>
#include <string>
#include <ranges>


namespace aoc {
	TEST(Day01, Part1) {

		std::string input{
			"1abc2\npqr3stu8vwx\na1b2c3d4e5f\ntreb7uchet"
		};

		EXPECT_EQ(142, day01::part1(std::istringstream{ input }));
	}

	TEST(Day01, Part2) {

		std::string input{
			"two1nine\neightwothree\nabcone2threexyz\nxtwone3four\n4nineeightseven2\nzoneight234\n7pqrstsixteen"
		};

		EXPECT_EQ(281, day01::part2(std::istringstream{ input }));
	}


	auto getInputDay04()
	{
		return std::string{
"Card 1: 41 48 83 86 17 | 83 86  6 31 17  9 48 53\n\
Card 2: 13 32 20 16 61 | 61 30 68 82 17 32 24 19\n\
Card 3 : 1 21 53 59 44 | 69 82 63 72 16 21 14  1\n\
Card 4 : 41 92 73 84 69 | 59 84 76 51 58  5 54 83\n\
Card 5 : 87 83 26 28 32 | 88 30 70 12 93 22 82 36\n\
Card 6 : 31 18 13 56 72 | 74 77 10 23 35 67 36 11"
		};
	}


	TEST(Day04, parseNumbersToVector) {
		std::string s{ "41 48 83 86 17" };
		std::vector<int> vec = parseNumbersToVector()(s);

		EXPECT_EQ(41, vec.at(0));
		EXPECT_EQ(48, vec.at(1));
		EXPECT_EQ(83, vec.at(2));
		EXPECT_EQ(86, vec.at(3));
		EXPECT_EQ(17, vec.at(4));
		EXPECT_EQ(5, vec.size());
	}


	TEST(Day04, splitLine_oneDelimiter) {
		std::string s{ "a,b,c" };
		
		auto vec = splitLine(',')(s)  | std::ranges::to<std::vector>();

		EXPECT_EQ(std::string{ "a" }, vec.at(0));
		EXPECT_EQ(std::string{ "b" }, vec.at(1));
		EXPECT_EQ(std::string{ "c" }, vec.at(2));
	}

	TEST(Day04, splitLine_twoDelimiters) {
		std::string s{ "a,b,c|x,y,z" };

		auto vec = splitLine('|',',')(s)  | std::ranges::to<std::vector>();

		EXPECT_EQ(std::string{ "a" }, vec.at(0));
		EXPECT_EQ(std::string{ "b" }, vec.at(1));
		EXPECT_EQ(std::string{ "c" }, vec.at(2));
		EXPECT_EQ(std::string{ "x" }, vec.at(3));
		EXPECT_EQ(std::string{ "y" }, vec.at(4));
		EXPECT_EQ(std::string{ "z" }, vec.at(5));
	}
	TEST(Day04, splitLine_twoDelimiters_02) {
		std::string s{ "a|b,c|x,y,z" };

		auto vec = splitLine('|', ',')(s) | std::ranges::to<std::vector>();

		EXPECT_EQ(std::string{ "a" }, vec.at(0));
		EXPECT_EQ(std::string{ "b" }, vec.at(1));
		EXPECT_EQ(std::string{ "c" }, vec.at(2));
		EXPECT_EQ(std::string{ "x" }, vec.at(3));
		EXPECT_EQ(std::string{ "y" }, vec.at(4));
		EXPECT_EQ(std::string{ "z" }, vec.at(5));
	}

	TEST(Day04, Part1) {
		EXPECT_EQ(13, day04::part1(std::istringstream{ getInputDay04() }));
	}

	TEST(Day04, Part2) {
		EXPECT_EQ(30, day04::part2(std::istringstream{ getInputDay04() }));
	}


}