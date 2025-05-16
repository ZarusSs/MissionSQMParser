#pragma once

#include "entities/BaseEntity.h"

#include <array>

class MarkerEntity : public BaseEntity
{
	std::array<double, 3> position;
	std::string name;
	std::optional<std::string> text;
	std::string type;
	std::optional<std::string> colorName;
	std::optional<double> a;
	std::optional<double> b;
	std::optional<double> angle;

public:

	void setPosition(const std::array<double, 3> &valueToSet);

	void setName(const std::string &valueToSet);

	void setText(const std::optional<std::string> &valueToSet);

	void setType(const std::string &valueToSet);

	void setColorName(const std::optional<std::string> &valueToSet);

	void setA(const std::optional<double> &valueToSet);

	void setB(const std::optional<double> &valueToSet);

	void setAngle(const std::optional<double> &valueToSet);

	[[nodiscard]] std::string toString(int indentLevel, short entityIndex) const;
};