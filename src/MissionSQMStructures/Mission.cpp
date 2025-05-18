#include "MissionSQMStructures/Mission.h"

std::string Mission::toString(int indentLevel) const
{
	std::stringstream outStream;

	auto indStr{ indent(indentLevel) };

	outStream << "class Mission\n";
	outStream << "{\n";
	outStream << intel.toString(indentLevel + 1);
	outStream << missionEntities.toString(indentLevel + 1);
	outStream << "};\n";
	return outStream.str();
}
