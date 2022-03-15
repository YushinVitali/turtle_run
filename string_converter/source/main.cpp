#include <iostream>
#include <string>
#include <vector>

#include "string_converter.hpp"

void TestConvertString(std::vector<std::string> testStrings);
void TestConvertStringWithSTL(std::vector<std::string> testStrings);
void TestConvertStringTwice(std::vector<std::string> testStrings);
void TestConvertStringRecursive(std::vector<std::string> testStrings);


int main()
{
	const std::vector<std::string> testStrings{
		"din",
		"recede",
		"Success",
		")) @"
	};

	TestConvertString(testStrings);

	std::cout << std::endl;

	TestConvertStringWithSTL(testStrings);

	std::cout << std::endl;

	TestConvertStringTwice(testStrings);

	std::cout << std::endl;

	TestConvertStringRecursive(testStrings);

	return 0;
}


void TestConvertString(std::vector<std::string> testStrings) {

	for(auto& testString : testStrings) {
		std::cout << testString << " - ";

		ConvertString(testString);

		std::cout << testString << std::endl;
	}
}


void TestConvertStringWithSTL(std::vector<std::string> testStrings) {
	for(auto& testString : testStrings) {
		std::cout << testString << " - ";

		ConvertStringWithSTL(testString);

		std::cout << testString << std::endl;
	}
}


void TestConvertStringTwice(std::vector<std::string> testStrings) {
	for(auto& testString : testStrings) {
		std::cout << testString << " - ";

		ConvertStringTwice(testString);

		std::cout << testString << std::endl;
	}
}


void TestConvertStringRecursive(std::vector<std::string> testStrings) {
	for(auto& testString : testStrings) {
		std::cout << testString << " - ";

		ConvertStringRecursive(testString);

		std::cout << testString << std::endl;
	}
}
