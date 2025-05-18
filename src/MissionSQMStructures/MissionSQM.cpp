#include "MissionSQMStructures/MissionSQM.h"

std::string MissionSQM::toStringAddons(int indentLevel) const
{
	std::stringstream outStream;

	auto indStr{ indent(indentLevel) };
	// TODO
	//  fix addons[] parsing
	outStream << "addons[]=\n";
	outStream << "{\n";
	for (size_t i{}; i < addons.size(); ++i)
	{
		outStream << indStr << quoteStr(addons.at(i)) << (i < addons.size() - 1 ? ",\n" : "\n");
	}
	outStream << "};\n";

	return outStream.str();
}

std::string MissionSQM::toStringCustomAttributes(int indentLevel) const
{
	std::stringstream outStream;

	auto indStr{ indent(indentLevel) };
	auto declIndStr{ indent(indentLevel - 1) };

	outStream << "class CustomAttributes" << '\n';
	outStream << "{\n";
	outStream << customAttributes.classData;
	outStream << "};\n";

	return outStream.str();
}

std::string MissionSQM::toString(int indentLevel) const
{
	std::stringstream outStream;

	auto indStr{ indent(indentLevel) };

	outStream << indStr << "version=" << version << ";\n";
	outStream << indStr << editorData.toString(indentLevel + 1);
	outStream << indStr << "binarizationWanted=" << binarizationWanted << ";\n";
	outStream << indStr << "sourceName=" << quoteStr(sourceName) << ";\n";
	outStream << toStringAddons(1);
	outStream << addonsMetaData.toString(1);
	outStream << indStr << "randomSeed=" << randomSeed << ";\n";
	outStream << indStr << scenarioData.toString(1);
	outStream << indStr << toStringCustomAttributes(indentLevel + 1);
	outStream << indStr << mission.toString(1);

	return outStream.str();
}

void MissionSQM::setVersion(short valueToSet)
{
	version = valueToSet;
}

void MissionSQM::setEditorData(const EditorData &valueToSet)
{
	editorData = valueToSet;
}

void MissionSQM::setBinarizationWanted(bool valueToSet)
{
	binarizationWanted = valueToSet;
}

void MissionSQM::setSourceName(const std::string &valueToSet)
{
	sourceName = valueToSet;
}

void MissionSQM::setAddons(const std::vector<std::string> &valueToSet)
{
	addons = valueToSet;
}

void MissionSQM::setAddonsMetaData(const AddonsMetaData &valueToSet)
{
	addonsMetaData = valueToSet;
}

void MissionSQM::setRandomSeed(long long int valueToSet)
{
	randomSeed = valueToSet;
}

void MissionSQM::setScenarioData(const ScenarioData &valueToSet)
{
	scenarioData = valueToSet;
}

void MissionSQM::setCustomAttributes(const CustomAttributes &valueToSet)
{
	customAttributes = valueToSet;
}

void MissionSQM::setMission(const Mission &valueToSet)
{
	mission = valueToSet;
}

void MissionSQM::removeEntity(int entityId)
{
	mission.missionEntities.removeEntity(entityId);
}
