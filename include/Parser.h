#pragma once

#include "MissionSQMStructures/MissionSQM.h"
#include "stringUtils/stringFuncs.h"

#include <sstream>
#include <fstream>
#include <string_view>
#include <stdexcept>
#include <functional>
#include <tuple>
#include <optional>
#include <iostream>

class Parser
{
	static EntityType toEntityType(std::string_view typeStr);

	static std::optional<std::string_view> parseField(std::string_view codeBlock, const std::string &fieldToParse);

	static std::optional<bool> parseBoolField(std::string_view codeBlock, const std::string &fieldToParse);

	static std::optional<int> parseIntField(std::string_view codeBlock, const std::string &fieldToParse);

	static std::optional<short> parseShortField(std::string_view codeBlock, const std::string &fieldToParse);

	static std::optional<double> parseDoubleField(std::string_view codeBlock, const std::string &fieldToParse);

	static std::optional<long long> parseLongLongField(std::string_view codeBlock, const std::string &fieldToParse);

	static std::optional<std::string> parseStringField(std::string_view codeBlock, const std::string &fieldToParse);

	template <typename arrayType>
	static std::optional<std::array<arrayType, 3>>
	parseArrayFieldOrDefault(std::string_view codeBlock, const std::string &fieldToParse);

	static Camera parseCamera(std::string_view codeBlock);

	static EditorData parseEditorData(std::string_view codeBlock);

	static std::optional<std::vector<std::string>> parseAddons(std::string_view codeBlock);

	static Addon parseAddon(std::string_view codeBlock);

	static AddonsMetaData parseAddonsMetaData(std::string_view codeBlock);

	static ScenarioData parseScenarioData(std::string_view codeBlock);
	// TODO
	//  refactor func to proper class data parsing
	static CustomAttributes parseCustomAttributes(std::string_view codeBlock);

	static Intel parseIntel(std::string_view codeBlock);

	static Attributes parseObjectAttributes(std::string_view codeBlock);

	static PositionInfo parsePositionInfo(std::string_view codeBlock);

	static std::tuple<std::string, int, double> parseBaseFields(std::string_view codeBlock);

	static ObjectEntity parseObjectEntity(std::string_view codeBlock);

	static GroupUnits parseGroupUnits(std::string_view codeBlock);

	static GroupEntity parseGroupEntity(std::string_view codeBlock);

	static LogicEntity parseLogicEntity(std::string_view codeBlock);

	static MarkerEntity parseMarkerEntity(std::string_view codeBlock);

	static TriggerEntity parseTriggerEntity(std::string_view codeBlock);

	static EntityVariant parseEntity(std::string_view codeBlock);

	static MissionEntities parseMissionEntities(std::string_view codeBlock);

	static Mission parseMission(std::string_view codeBlock);

public:
	virtual ~Parser() = 0;

	static MissionSQM parseFromFile(const std::string &filePath);

	static void writeMissionSQMToFile(MissionSQM &missionSqm, const std::string &copyName, const std::string &filePath);
};