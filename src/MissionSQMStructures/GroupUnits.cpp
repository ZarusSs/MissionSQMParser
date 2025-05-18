#include "MissionSQMStructures/GroupUnits.h"

std::string GroupUnits::toString(int indentLevel) const
{
	std::stringstream outStream;

	auto indStr{ indent(indentLevel) };
	auto declIndStr{ indent(indentLevel - 1) };

	outStream << declIndStr << "class Entities" << '\n';
	outStream << declIndStr << "{\n";
	outStream << indStr << "items=" << items << ";\n";
	for (short i{}; i < items; ++i)
	{
		outStream << units.at(i).toString(indentLevel + 1, i);
	}

	outStream << declIndStr << "};\n";

	return outStream.str();
}
