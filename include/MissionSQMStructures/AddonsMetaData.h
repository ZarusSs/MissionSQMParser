#pragma once

#include "MissionSQMStructures/Addon.h"

#include <vector>

struct AddonsMetaData
{
	short items;
	std::vector<Addon> addons;

	[[nodiscard]] std::string toString(int indentLevel) const;
};