#include "MissionSQMStructures/AddonsMetaData.h"

std::string AddonsMetaData::toString(int indentLevel) const
{
	std::stringstream outStream;

	auto indStr{ indent(indentLevel) };
	auto listIndStr{ indent(indentLevel + 1) };

	outStream << "class AddonsMetaData\n";
	outStream << "{\n";
	outStream << indStr << "class List\n";
	outStream << indStr << "{\n";
	outStream << listIndStr << "items=" << items << ";\n";

	for (short i{}; i < items; ++i)
	{
		outStream << addons.at(i).toString(indentLevel + 2, i);
	}

	outStream << indStr << "};\n";
	outStream << "};\n";

	return outStream.str();
}
