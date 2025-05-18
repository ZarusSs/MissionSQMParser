#pragma once

#include "entities/ObjectEntity.h"

#include <vector>

struct GroupUnits
{
	short items;
	std::vector<ObjectEntity> units;

	[[nodiscard]] std::string toString(int indentLevel) const;
};