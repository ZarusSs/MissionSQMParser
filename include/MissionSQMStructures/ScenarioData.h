#pragma once

#include "stringUtils/stringFuncs.h"

#include <string>
#include <sstream>
#include <optional>

struct ScenarioData
{
	std::string author;
	std::optional<short> respawn;

	[[nodiscard]] std::string toString(int indentLevel) const;
};