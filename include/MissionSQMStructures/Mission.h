#pragma once

#include "Intel.h"
#include "MissionEntities.h"
#include "stringUtils/stringFuncs.h"

#include <sstream>

struct Mission
{
	Intel intel;
	MissionEntities missionEntities;

	[[nodiscard]] std::string toString(int indentLevel) const;
};