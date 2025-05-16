#pragma once

#include "stringUtils/stringFuncs.h"

#include <string>
#include <sstream>
#include <optional>

struct Attributes
{
	std::optional<std::string> rank;
	std::optional<std::string> init;
	std::optional<std::string> name;
	std::optional<std::string> description;
	std::optional<bool> isPlayable;

	[[nodiscard]] std::string toString(int indentLevel) const;
};