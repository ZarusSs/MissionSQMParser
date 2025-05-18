#include "entities/MarkerEntity.h"

std::string MarkerEntity::toString(int indentLevel, short entityIndex) const
{
	std::stringstream outStream;

	auto indStr{ indent(indentLevel) };
	auto declIndStr{ indent(indentLevel - 1) };

	outStream << declIndStr << "class Item" << std::to_string(entityIndex) << '\n';
	outStream << declIndStr << "{\n";
	outStream << indStr << "dataType=" << quoteStr(getDataType()) << ";\n";
	outStream << indStr << "position[]=" << strArray<double>(position) << ";\n";
	outStream << indStr << "name=" << quoteStr(name) << ";\n";
	outStream << indStr << "text=" << quoteStr(*text) << ";\n";
	outStream << indStr << "type=" << quoteStr(type) << ";\n";
	outStream << indStr << "colorName=" << quoteStr(*colorName) << ";\n";
	outStream << indStr << "a=" << *a << ";\n";
	outStream << indStr << "b=" << *b << ";\n";
	outStream << indStr << "angle=" << *angle << ";\n";
	outStream << indStr << "id=" << getId() << ";\n";
	outStream << indStr << "atlOffset=" << getAtlOffset() << ";\n";
	outStream << declIndStr << "};\n";

	return outStream.str();
}

void MarkerEntity::setPosition(const std::array<double, 3> &valueToSet)
{
	position = valueToSet;
}

void MarkerEntity::setName(const std::string &valueToSet)
{
	name = valueToSet;
}

void MarkerEntity::setText(const std::optional<std::string> &valueToSet)
{
	text = valueToSet;
}

void MarkerEntity::setType(const std::string &valueToSet)
{
	type = valueToSet;
}

void MarkerEntity::setColorName(const std::optional<std::string> &valueToSet)
{
	colorName = valueToSet;
}

void MarkerEntity::setA(const std::optional<double> &valueToSet)
{
	a = valueToSet;
}

void MarkerEntity::setB(const std::optional<double> &valueToSet)
{
	b = valueToSet;
}

void MarkerEntity::setAngle(const std::optional<double> &valueToSet)
{
	angle = valueToSet;
}
