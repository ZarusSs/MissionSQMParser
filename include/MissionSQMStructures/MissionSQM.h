#pragma once

#include "EditorData.h"
#include "AddonsMetaData.h"
#include "ScenarioData.h"
#include "Mission.h"
#include "CustomAttributes.h"

#include <sstream>

class MissionSQM
{
	short version;
	EditorData editorData;
	bool binarizationWanted;
	std::string sourceName;
	std::vector<std::string> addons;
	AddonsMetaData addonsMetaData;
	long long randomSeed;
	ScenarioData scenarioData;
	CustomAttributes customAttributes;
	Mission mission;

public:

	void setVersion(short valueToSet);

	void setEditorData(const EditorData &valueToSet);

	void setBinarizationWanted(bool valueToSet);

	void setSourceName(const std::string &valueToSet);

	void setAddons(const std::vector<std::string> &valueToSet);

	void setAddonsMetaData(const AddonsMetaData &valueToSet);

	void setRandomSeed(long long int valueToSet);

	void setScenarioData(const ScenarioData &valueToSet);

	void setCustomAttributes(const CustomAttributes &valueToSet);

	void setMission(const Mission &valueToSet);

	[[nodiscard]] std::string toStringAddons(int indentLevel) const;

	[[nodiscard]] std::string toStringCustomAttributes(int indentLevel) const;

	[[nodiscard]] std::string toString(int indentLevel) const;

	void removeEntity(int entityId);
};