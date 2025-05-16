#pragma once

#include "entities/BaseEntity.h"
#include "MissionSQMStructures/ObjectAttributes.h"
#include "MissionSQMStructures/GroupUnits.h"

#include <algorithm>

class GroupEntity : public BaseEntity
{
	std::string side;
	GroupUnits groupUnits;
	Attributes attributes;

	[[nodiscard]] bool hasEntityWithId(const ObjectEntity &objectEntity, int id) const;

public:

	void setSide(const std::string &valueToSet);

	void setGroupUnits(const GroupUnits &valueToSet);

	void setAttributes(const Attributes &valueToSet);

	[[nodiscard]] bool isGroupEmpty() const;

	void removeUnitFromGroup(int id);

	[[nodiscard]] std::string toString(int indentLevel, short entityIndex) const;
};