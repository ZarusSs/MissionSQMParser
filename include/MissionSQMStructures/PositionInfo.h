#pragma once

#include "stringUtils/stringFuncs.h"

#include <array>
#include <sstream>

#include <optional>

struct PositionInfo
{
	std::array<double, 3> position;
	std::optional<std::array<double, 3>> angles;

	[[nodiscard]] std::string toString(int indentLevel) const;
};