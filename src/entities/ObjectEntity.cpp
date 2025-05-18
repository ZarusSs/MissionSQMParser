#include "entities/ObjectEntity.h"

std::string ObjectEntity::strCustomAttributes(int indentLevel) const
{
	std::stringstream outStream;

	auto indStr{ indent(indentLevel) };
	auto declIndStr{ indent(indentLevel - 1) };

	outStream << declIndStr << "class CustomAttributes" << '\n';
	outStream << declIndStr << "{\n";
	outStream << customAttributes->classData;
	outStream << "};\n";

	return outStream.str();
}

std::string ObjectEntity::toString(int indentLevel, short entityIndex) const
{
	std::stringstream outStream;

	auto indStr{ indent(indentLevel) };
	auto declIndStr{ indent(indentLevel - 1) };

	outStream << declIndStr << "class Item" << std::to_string(entityIndex) << "\n";
	outStream << declIndStr << "{\n";
	outStream << indStr << "dataType=" << quoteStr(getDataType()) << ";\n";
	outStream << positionInfo.toString(indentLevel + 1);
	outStream << indStr << "side=" << quoteStr(side) << ";\n";
	if (flags.has_value())
		outStream << indStr << "flags=" << *flags << ";\n";
	outStream << attributes.toString(indentLevel + 1);
	outStream << indStr << "id=" << getId() << ";\n";
	outStream << indStr << "type=" << quoteStr(type) << ";\n";
	outStream << indStr << "atlOffset=" << getAtlOffset() << ";\n";
	outStream << strCustomAttributes(indentLevel + 1);
	outStream << declIndStr << "};\n";

	return outStream.str();
}

void ObjectEntity::setPositionInfo(const PositionInfo &valueToSet)
{
	positionInfo = valueToSet;
}

void ObjectEntity::setSide(const std::string_view &valueToSet)
{
	side = std::string{ valueToSet };
}

void ObjectEntity::setFlags(const std::optional<short> &valueToSet)
{
	flags = valueToSet;
}

void ObjectEntity::setAttributes(const Attributes &valueToSet)
{
	attributes = valueToSet;
}

void ObjectEntity::setType(const std::string_view &valueToSet)
{
	type = valueToSet;
}

void ObjectEntity::setCustomAttributes(const std::optional<CustomAttributes> &valueToSet)
{
	customAttributes = valueToSet;
}
