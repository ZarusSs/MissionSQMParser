#pragma once

#include "stringUtils/stringFuncs.h"

#include <array>
#include <sstream>

struct Camera
{
	std::array<double, 3> pos;
	std::array<double, 3> dir;
	std::array<double, 3> up;
	std::array<double, 3> aside;

	[[nodiscard]] std::string toString(int indentLevel) const;
};