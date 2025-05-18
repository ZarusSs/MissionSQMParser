#include "MissionSQMStructures/PositionInfo.h"

std::string PositionInfo::toString(int indentLevel) const
{
	std::stringstream outStream;

	auto indStr{ indent(indentLevel) };
	auto declIndStr{ indent(indentLevel - 1) };

	outStream << declIndStr << "class PositionInfo" << "\n";
	outStream << declIndStr << "{\n";
	outStream << indStr << "position[]=" << strArray<double>(position) << ";\n";
	if (angles.has_value())
		outStream << indStr << "angles[]=" << strArray<double>(*angles) << ";\n";
	outStream << declIndStr << "};\n";

	return outStream.str();
}
