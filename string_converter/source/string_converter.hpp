#pragma once

#ifndef __STRING_CONVERTER_HPP__
#define __STRING_CONVERTER_HPP__


#include <string>


/// @brief Convert the string to a character set '(' and ')'.
void ConvertString(std::string& str);

/// @brief Convert a string to a character set '(' and ')' using STL algorithms.
void ConvertStringWithSTL(std::string& str);

/// @brief Converts a string to a character set '(' and ')' with a bypass on both sides.
void ConvertStringTwice(std::string& str);

/// @brief Converts a string into a set of characters '(' and ')' using recursion.
void ConvertStringRecursive(std::string& str);

#endif // !defined(__STRING_CONVERTER_HPP__)
