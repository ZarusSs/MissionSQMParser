#include "entities/LogicEntity.h"

std::string LogicEntity::toString(int indentLevel, short entityIndex) const
{
	std::stringstream outStream;

	auto indStr{ indent(indentLevel) };
	auto declIndStr{ indent(indentLevel - 1) };

	outStream << declIndStr << "class Item" << std::to_string(entityIndex) << '\n';
	outStream << declIndStr << "{\n";
	outStream << indStr << "dataType=" << quoteStr(getDataType()) << ";\n";
	outStream << positionInfo.toString(indentLevel + 1);
	outStream << indStr << "name=" << quoteStr(*name) << ";\n";
	outStream << indStr << "init=" << quoteStr(*init) << ";\n";
	outStream << indStr << "id=" << getId() << ";\n";
	outStream << indStr << "type=" << quoteStr(type) << ";\n";
	outStream << indStr << "atlOffset=" << getAtlOffset() << ";\n";
	outStream << declIndStr << "};\n";

	return outStream.str();
}

void LogicEntity::setPositionInfo(const PositionInfo &valueToSet)
{
	positionInfo = valueToSet;
}

void LogicEntity::setType(const std::string &valueToSet)
{
	type = valueToSet;
}

void LogicEntity::setInit(const std::optional<std::string> &valueToSet)
{
	init = valueToSet;
}

void LogicEntity::setName(const std::optional<std::string> &valueToSet)
{
	name = valueToSet;
}
