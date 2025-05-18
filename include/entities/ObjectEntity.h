#pragma once

#include "entities/BaseEntity.h"
#include "MissionSQMStructures/PositionInfo.h"
#include "MissionSQMStructures/ObjectAttributes.h"
#include "MissionSQMStructures/CustomAttributes.h"

class ObjectEntity : public BaseEntity
{
	PositionInfo positionInfo;
	std::string side;
	std::optional<short> flags;
	Attributes attributes;
	std::string type;
	std::optional<CustomAttributes> customAttributes;

	[[nodiscard]] std::string strCustomAttributes(int indentLevel) const;

public:

	void setPositionInfo(const PositionInfo &valueToSet);

	void setSide(const std::string_view &valueToSet);

	void setFlags(const std::optional<short> &valueToSet);

	void setAttributes(const Attributes &valueToSet);

	void setType(const std::string_view &valueToSet);

	void setCustomAttributes(const std::optional<CustomAttributes> &valueToSet);

	[[nodiscard]] std::string toString(int indentLevel, short entityIndex) const;
};