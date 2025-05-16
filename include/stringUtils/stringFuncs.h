#pragma once

#include <cstdio>
#include <string_view>
#include <stdexcept>
#include <string>
#include <array>
#include <sstream>

size_t findClosingBracePos(std::string_view fileContent, size_t openingBracePos);

std::string_view findClassBlock(std::string_view fileContent, const std::string &className);

std::string indent(int level);

std::string quoteStr(const std::string &str);

template <typename arrayType>
std::string strArray(const std::array<arrayType, 3> &array)
{
	std::stringstream outStream;

	if constexpr (std::is_same_v<arrayType, double>)
		outStream << "{" << array.at(0) << ", " << array.at(1) << ", " << array.at(2) << "}";
	else if constexpr (std::is_same_v<arrayType, std::string>)
	{
		outStream << "{"
				  << quoteStr(array.at(0)) << ", "
				  << quoteStr(array.at(1)) << ", "
				  << quoteStr(array.at(2)) << "}";
	}
	else
		static_assert(std::is_same_v<arrayType, void>, "Unsupported array element type");

	return outStream.str();
}