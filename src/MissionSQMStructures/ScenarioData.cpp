#include "MissionSQMStructures/ScenarioData.h"

std::string ScenarioData::toString(int indentLevel) const
{
	std::stringstream outStream;

	auto indStr{ indent(indentLevel) };

	outStream << "class ScenarioData\n";
	outStream << "{\n";
	outStream << indStr << "author=" << quoteStr(author) << ";\n";
	if (respawn.has_value())
		outStream << indStr << "respawn=" << *respawn << ";\n";
	outStream << "};\n";

	return outStream.str();
}
