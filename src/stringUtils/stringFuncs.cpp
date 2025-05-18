#include "stringUtils/stringFuncs.h"

size_t findClosingBracePos(std::string_view fileContent, size_t openingBracePos)
{
	auto bracesCounter{ 1 };
	auto currentPos{ openingBracePos + 1 };

	while (bracesCounter > 0 && currentPos < fileContent.size())
	{
		auto ch{ fileContent[currentPos] };
		if (ch == '{')
			++bracesCounter;
		else if (ch == '}')
			--bracesCounter;

		++currentPos;
	}

	if (bracesCounter != 0)
		throw std::runtime_error{ "Closing brace not found, last checked position: " + std::to_string
				(currentPos) };

	return currentPos - 1;
}

std::string_view findClassBlock(std::string_view fileContent, const std::string &className)
{

	if (fileContent.size() <= className.size())
		throw std::runtime_error{ "Field \"" + className + "\" not found" };

	int depth{};

	size_t pos{ std::string::npos };

	for (size_t i{}; i <= fileContent.size() - className.size(); ++i)
	{
		auto ch{ fileContent[i] };

		if (ch == '{')
			++depth;
		else if (ch == '}')
		{
			if (depth != 0)
				--depth;
		}
		else if (depth == 0 && fileContent.substr(i, className.size()) == className)
		{
			pos = i;
			break;
		}
	}

	if (pos == std::string::npos)
		throw std::runtime_error{ "Class " + className + " not found" };

	auto openingBracePos{ fileContent.find('{', pos) };

	if (openingBracePos == std::string::npos)
		throw std::runtime_error{ "Opening brace not found for class " + className };

	auto closingBracePos{ findClosingBracePos(fileContent, openingBracePos) };
	return fileContent.substr(openingBracePos + 1, closingBracePos - openingBracePos - 1);
}

std::string indent(int level)
{
	return std::string(level, '\t');
}

std::string quoteStr(const std::string &str)
{
	return '"' + str + '"';
}