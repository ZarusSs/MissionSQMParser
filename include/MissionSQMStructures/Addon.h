#pragma once

#include "stringUtils/stringFuncs.h"

#include <string>
#include <sstream>
#include <optional>

struct Addon
{
	std::string className;
	std::string name;
	std::optional<std::string> author;
	std::optional<std::string> url;

	[[nodiscard]] std::string toString(int indentLevel, short addonIndex) const;
};