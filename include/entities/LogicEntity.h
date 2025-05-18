#pragma once

#include "entities/BaseEntity.h"
#include "MissionSQMStructures/PositionInfo.h"


class LogicEntity : public BaseEntity
{
	PositionInfo positionInfo;
	std::string type;
	std::optional<std::string> init;
	std::optional<std::string> name;

public:

	void setPositionInfo(const PositionInfo &valueToSet);

	void setType(const std::string &valueToSet);

	void setInit(const std::optional<std::string> &valueToSet);

	void setName(const std::optional<std::string> &valueToSet);

	[[nodiscard]] std::string toString(int indentLevel, short entityIndex) const;
};