#include "entities/TriggerEntity.h"

std::string TriggerEntity::toString(int indentLevel, short entityIndex) const
{
	std::stringstream outStream;

	auto indStr{ indent(indentLevel) };
	auto declIndStr{ indent(indentLevel - 1) };

	outStream << declIndStr << "class Item" << std::to_string(entityIndex) << '\n';
	outStream << declIndStr << "{\n";
	outStream << indStr << "dataType=" << quoteStr(getDataType()) << ";\n";
	outStream << indStr << "position[]=" << strArray<double>(position) << ";\n";
	if (angle.has_value())
		outStream << indStr << "angle=" << *angle << ";\n";
	outStream << attributes.toString(indentLevel + 1);
	outStream << indStr << "id=" << getId() << ";\n";
	outStream << indStr << "type=" << quoteStr(type) << ";\n";
	outStream << indStr << "atlOffset=" << getAtlOffset() << ";\n";
	outStream << declIndStr << "};\n";

	return outStream.str();
}

void TriggerEntity::setPosition(const std::array<double, 3> &valueToSet)
{
	position = valueToSet;
}

void TriggerEntity::setAngle(const std::optional<double> &valueToSet)
{
	angle = valueToSet;
}

void TriggerEntity::setAttributes(const Attributes &valueToSet)
{
	attributes = valueToSet;
}

void TriggerEntity::setType(const std::string &valueToSet)
{
	type = valueToSet;
}
