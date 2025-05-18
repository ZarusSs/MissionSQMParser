#pragma once

#include "entities/BaseEntity.h"
#include "MissionSQMStructures/ObjectAttributes.h"

#include <array>

class TriggerEntity : public BaseEntity
{
	std::array<double, 3> position;
	std::optional<double> angle;
	Attributes attributes;
	std::string type;

public:

	void setPosition(const std::array<double, 3> &valueToSet);

	void setAngle(const std::optional<double> &valueToSet);

	void setAttributes(const Attributes &valueToSet);

	void setType(const std::string &valueToSet);

	[[nodiscard]] std::string toString(int indentLevel, short entityIndex) const;
};