#include "Parser.h"

EntityType Parser::toEntityType(std::string_view typeStr)
{
	if (typeStr == "Group")
		return EntityType::Group;
	if (typeStr == "Object")
		return EntityType::Object;
	if (typeStr == "Marker")
		return EntityType::Marker;
	if (typeStr == "Logic")
		return EntityType::Logic;
	if (typeStr == "Trigger")
		return EntityType::Trigger;
	return EntityType::Unknown;
}

std::optional<std::string_view> Parser::parseField(std::string_view codeBlock, const std::string &fieldToParse)
{
	std::string search{ fieldToParse + '=' };

	if (codeBlock.size() <= fieldToParse.size())
		return std::nullopt;

	int depth{};

	size_t pos{ std::string::npos };

	for (size_t i{}; i <= codeBlock.size() - search.size(); ++i)
	{
		auto ch{ codeBlock[i] };

		if (ch == '{')
			++depth;
		else if (ch == '}')
		{
			if (depth != 0)
				--depth;
		}
		else if (depth == 0 && codeBlock.substr(i, search.size()) == search)
		{
			pos = i;
			break;
		}
	}

	if (pos == std::string::npos)
		return std::nullopt;

	auto valuePos{ pos + search.size() };

	while (valuePos < codeBlock.size() && std::isspace(codeBlock[valuePos]))
		++valuePos;

	auto semicolonPos{ codeBlock.find(';', valuePos) };
	if (semicolonPos == std::string::npos)
	{
		std::cerr << "Missing ';' after field \"" + fieldToParse + "\"\n";
		return std::nullopt;
	}

	return codeBlock.substr(valuePos, semicolonPos - valuePos);
}

std::optional<bool> Parser::parseBoolField(std::string_view codeBlock, const std::string &fieldToParse)
{
	auto optStrValue{ parseField(codeBlock, fieldToParse) };

	if (!optStrValue.has_value())
		return std::nullopt;

	return static_cast<bool>(std::stoi(std::string{ optStrValue.value() }));
}

std::optional<int> Parser::parseIntField(std::string_view codeBlock, const std::string &fieldToParse)
{

	auto optStrValue{ parseField(codeBlock, fieldToParse) };

	if (!optStrValue.has_value())
		return std::nullopt;

	return std::stoi(std::string{ optStrValue.value() });
}

std::optional<short> Parser::parseShortField(std::string_view codeBlock, const std::string &fieldToParse)
{
	auto optStrValue{ parseField(codeBlock, fieldToParse) };

	if (!optStrValue.has_value())
		return std::nullopt;

	return static_cast<short>(std::stoi(std::string{ optStrValue.value() }));
}

std::optional<double> Parser::parseDoubleField(std::string_view codeBlock, const std::string &fieldToParse)
{
	auto optStrValue{ parseField(codeBlock, fieldToParse) };

	if (!optStrValue.has_value())
		return std::nullopt;

	return std::stod(std::string{ optStrValue.value() });
}

std::optional<long long> Parser::parseLongLongField(std::string_view codeBlock, const std::string &fieldToParse)
{
	auto optStrValue{ parseField(codeBlock, fieldToParse) };

	if (!optStrValue.has_value())
		return std::nullopt;

	return std::stoll(std::string{ optStrValue.value() });
}

std::optional<std::string> Parser::parseStringField(std::string_view codeBlock, const std::string &fieldToParse)
{
	auto optStrValue{ parseField(codeBlock, fieldToParse) };

	if (!optStrValue.has_value())
		return std::nullopt;

	auto strValue{ optStrValue.value() };

	if (strValue.front() == '"' && strValue.back() == '"')
	{
		strValue.remove_prefix(1);
		strValue.remove_suffix(1);
	}
	return std::string{ strValue };
}

template <typename arrayType>
std::optional<std::array<arrayType, 3>>
Parser::parseArrayFieldOrDefault(std::string_view codeBlock, const std::string &fieldToParse)
{
	auto optStrValue{ parseField(codeBlock, fieldToParse) };

	if (!optStrValue.has_value())
		return std::nullopt;

	auto strValue{ optStrValue.value() };

	if (strValue.front() != '{' || strValue.back() != '}')
	{
		std::cerr << "Invalid array format for field \"" + fieldToParse + "\"\n";
		return std::nullopt;
	}
	else
	{
		strValue.remove_prefix(1);
		strValue.remove_suffix(1);
	}

	std::array<arrayType, 3> result;

	size_t currentPos{};

	size_t arrPos{};
	while (currentPos < strValue.size())
	{
		while (std::isspace(strValue[currentPos]))
			++currentPos;

		auto comma{ strValue.find(',', currentPos) };
		if (comma == std::string::npos)
			comma = strValue.size();

		auto arrayElement{ strValue.substr(currentPos, comma - currentPos) };

		if constexpr (std::is_same_v<arrayType, double>)
			result.at(arrPos) = std::stod(std::string{ arrayElement });
		else if constexpr (std::is_same_v<arrayType, int>)
			result.at(arrPos) = std::stoi(std::string{ arrayElement });
		else if constexpr (std::is_same_v<arrayType, std::string>)
		{
			if (arrayElement.size() >= 2 && arrayElement.front() == '"' && arrayElement.back() == '"')
			{
				arrayElement.remove_prefix(1);
				arrayElement.remove_suffix(1);
			}
			result.at(arrPos) = std::string{ arrayElement };
		}
		else
			static_assert(std::is_same_v<arrayType, void>, "Unsupported array element type");

		currentPos = comma + 1;
		++arrPos;
	}

	return result;
}

Camera Parser::parseCamera(std::string_view codeBlock)
{
	Camera result{};

	result.pos = parseArrayFieldOrDefault<double>(codeBlock, "pos[]").value();
	result.dir = parseArrayFieldOrDefault<double>(codeBlock, "dir[]").value();
	result.up = parseArrayFieldOrDefault<double>(codeBlock, "up[]").value();
	result.aside = parseArrayFieldOrDefault<double>(codeBlock, "aside[]").value();

	return result;
}

EditorData Parser::parseEditorData(std::string_view codeBlock)
{
	EditorData result{};

	try
	{
		auto ItemIDProviderCodeBlock{ findClassBlock(codeBlock, "ItemIDProvider") };
		auto MarkerIDProviderCodeBlock{ findClassBlock(codeBlock, "MarkerIDProvider") };
		auto CameraCodeBlock{ findClassBlock(codeBlock, "Camera") };

		result.moveGridStep = parseShortField(codeBlock, "moveGridStep").value();
		result.angleGridStep = parseDoubleField(codeBlock, "angleGridStep").value();
		result.scaleGridStep = parseShortField(codeBlock, "scaleGridStep").value();
		result.autoGroupingDist = parseShortField(codeBlock, "autoGroupingDist").value();
		result.toggles = parseShortField(codeBlock, "toggles").value();

		result.nextItemIDProvider = parseIntField(ItemIDProviderCodeBlock, "nextID");
		result.nextMarkerIDProvider = parseIntField(MarkerIDProviderCodeBlock, "nextID");

		result.camera = parseCamera(CameraCodeBlock);

		return result;
	}
	catch (std::runtime_error &ex)
	{
		std::cerr << ex.what() << '\n';
		return result;
	}
}

std::optional<std::vector<std::string>> Parser::parseAddons(std::string_view codeBlock)
{
	auto optStrValue{ parseField(codeBlock, "addons[]") };

	if (!optStrValue.has_value())
		return std::nullopt;

	auto strValue{ optStrValue.value() };

	if (strValue.front() != '{' || strValue.back() != '}')
	{
		std::cerr << "Invalid array format for field \"addons[]\"\n";
		return std::nullopt;
	}
	else
	{
		strValue.remove_prefix(1);
		strValue.remove_suffix(1);
	}

	std::vector<std::string> result;

	size_t currentPos{};

	while (currentPos < strValue.size())
	{
		while (std::isspace(strValue.at(currentPos)))
			++currentPos;

		auto comma{ strValue.find(',', currentPos) };

		if (comma == std::string::npos)
			comma = strValue.size();

		while (std::isspace(strValue.at(comma - 1)))
			--comma;

		auto arrayElement{ strValue.substr(currentPos, comma - currentPos) };

		if (arrayElement.front() == '"' && arrayElement.back() == '"')
		{
			arrayElement.remove_prefix(1);
			arrayElement.remove_suffix(1);
		}

		result.emplace_back(arrayElement);

		currentPos = comma + 1;
	}

	return result;
}

Addon Parser::parseAddon(std::string_view codeBlock)
{
	Addon result{};

	result.className = parseStringField(codeBlock, "className").value();
	result.name = parseStringField(codeBlock, "name").value();
	result.author = parseStringField(codeBlock, "author");
	result.url = parseStringField(codeBlock, "url");

	return result;
}

AddonsMetaData Parser::parseAddonsMetaData(std::string_view codeBlock)
{
	AddonsMetaData result{};

	try
	{
		auto listCodeBlock{ findClassBlock(codeBlock, "List") };

		result.items = parseShortField(listCodeBlock, "items").value();

		for (short i{}; i < result.items; ++i)
		{
			std::string addonClassName{ "Item" + std::to_string(i) };

			auto addonCodeBlock{ findClassBlock(listCodeBlock, addonClassName) };

			Addon addon{ parseAddon(addonCodeBlock) };

			result.addons.push_back(addon);
		}

		return result;
	}
	catch (std::runtime_error &ex)
	{
		std::cerr << ex.what() << '\n';
		return result;
	}
}

ScenarioData Parser::parseScenarioData(std::string_view codeBlock)
{
	ScenarioData result{};

	result.author = parseStringField(codeBlock, "author").value();
	result.respawn = parseShortField(codeBlock, "respawn");

	return result;
}

CustomAttributes Parser::parseCustomAttributes(std::string_view codeBlock)
{
	return { std::string{ codeBlock }};
}

Intel Parser::parseIntel(std::string_view codeBlock)
{
	Intel result{};

	result.timeOfChanges = parseDoubleField(codeBlock, "timeOfChanges").value();

	result.startWeather = parseDoubleField(codeBlock, "startWeather").value();
	result.startWind = parseDoubleField(codeBlock, "startWind").value();
	result.startWaves = parseDoubleField(codeBlock, "startWaves").value();

	result.forecastWeather = parseDoubleField(codeBlock, "forecastWeather").value();
	result.forecastWind = parseDoubleField(codeBlock, "forecastWind").value();
	result.forecastWaves = parseDoubleField(codeBlock, "forecastWaves").value();
	result.forecastLightnings = parseDoubleField(codeBlock, "forecastLightnings").value();

	result.wavesForced = parseIntField(codeBlock, "wavesForced").value();
	result.windForced = parseIntField(codeBlock, "windForced").value();

	result.year = parseShortField(codeBlock, "year").value();
	result.month = parseShortField(codeBlock, "month").value();
	result.day = parseShortField(codeBlock, "day").value();
	result.hour = parseShortField(codeBlock, "hour").value();
	result.minute = parseShortField(codeBlock, "minute").value();

	result.startFogBase = parseDoubleField(codeBlock, "startFogBase");
	result.forecastFogBase = parseDoubleField(codeBlock, "forecastFogBase");
	result.startFogDecay = parseDoubleField(codeBlock, "startFogDecay").value();
	result.forecastFogDecay = parseDoubleField(codeBlock, "forecastFogDecay").value();

	return result;
}

Attributes Parser::parseObjectAttributes(std::string_view codeBlock)
{
	Attributes result{};

	result.rank = parseStringField(codeBlock, "rank");
	result.init = parseStringField(codeBlock, "init");
	result.name = parseStringField(codeBlock, "name");
	result.description = parseStringField(codeBlock, "description");
	result.isPlayable = parseBoolField(codeBlock, "isPlayable");

	return result;
}

PositionInfo Parser::parsePositionInfo(std::string_view codeBlock)
{
	PositionInfo result{};

	result.position = parseArrayFieldOrDefault<double>(codeBlock, "position[]").value();

	result.angles = parseArrayFieldOrDefault<double>(codeBlock,
													 "angles[]");
	return result;
}

std::tuple<std::string, int, double> Parser::parseBaseFields(std::string_view codeBlock)
{
	auto dataType{ parseStringField(codeBlock, "dataType").value() };
	auto id{ parseIntField(codeBlock, "id").value() };
	auto atlOffset{ parseDoubleField(codeBlock, "atlOffset").value() };

	return { dataType, id, atlOffset };
}

ObjectEntity Parser::parseObjectEntity(std::string_view codeBlock)
{
	ObjectEntity result{};

	try
	{
		std::tie(result.getDataTypeRef(), result.getIdRef(), result.getAtlOffsetRef()) = parseBaseFields(codeBlock);

		result.setDataType(parseStringField(codeBlock, "dataType").value());
		result.setId(parseIntField(codeBlock, "id").value());
		result.setAtlOffset(parseDoubleField(codeBlock, "atlOffset").value());

		auto positionInfoCodeBlock{ findClassBlock(codeBlock, "PositionInfo") };
		auto attributesCodeBlock{ findClassBlock(codeBlock, "Attributes") };

		result.setPositionInfo(parsePositionInfo(positionInfoCodeBlock));
		result.setSide(parseStringField(codeBlock, "side").value());
		result.setFlags(parseShortField(codeBlock, "flags"));
		result.setAttributes(parseObjectAttributes(attributesCodeBlock));
		result.setType(parseStringField(codeBlock, "type").value());

		auto customAttributesCodeBlock{ findClassBlock(codeBlock, "CustomAttributes") };
		result.setCustomAttributes(parseCustomAttributes(customAttributesCodeBlock));

		return result;
	}
	catch (std::runtime_error &ex)
	{
		std::cerr << ex.what() << '\n';
		return result;
	}
}

GroupUnits Parser::parseGroupUnits(std::string_view codeBlock)
{
	GroupUnits result{};

	try
	{
		result.items = parseShortField(codeBlock, "items").value();

		for (short i{}; i < result.items; ++i)
		{
			std::string unitClassName{ "Item" + std::to_string(i) };

			auto unitCodeBlock{ findClassBlock(codeBlock, unitClassName) };

			ObjectEntity unit{ parseObjectEntity(unitCodeBlock) };

			result.units.push_back(unit);
		}

		return result;
	}
	catch (std::runtime_error &ex)
	{
		std::cerr << ex.what() << '\n';
		return result;
	}
}

GroupEntity Parser::parseGroupEntity(std::string_view codeBlock)
{
	GroupEntity result{};

	try
	{
		std::tie(result.getDataTypeRef(), result.getIdRef(), result.getAtlOffsetRef()) = parseBaseFields(codeBlock);

		result.setSide(parseStringField(codeBlock, "side").value());

		auto attributesCodeBlock{ findClassBlock(codeBlock, "Attributes") };
		auto entitiesCodeBlock{ findClassBlock(codeBlock, "Entities") };


		result.setAttributes(parseObjectAttributes(attributesCodeBlock));

		result.setGroupUnits(parseGroupUnits(entitiesCodeBlock));

		return result;
	}
	catch (std::runtime_error &ex)
	{
		std::cerr << ex.what() << '\n';
		return result;
	}
}

LogicEntity Parser::parseLogicEntity(std::string_view codeBlock)
{
	LogicEntity result{};

	try
	{
		std::tie(result.getDataTypeRef(), result.getIdRef(), result.getAtlOffsetRef()) = parseBaseFields(codeBlock);

		auto positionInfoCodeBlock{ findClassBlock(codeBlock, "PositionInfo") };

		result.setPositionInfo(parsePositionInfo(positionInfoCodeBlock));

		result.setType(parseStringField(codeBlock, "type").value());

		result.setInit(parseStringField(codeBlock, "init"));

		result.setName(parseStringField(codeBlock, "name"));

		return result;
	}
	catch (std::runtime_error &ex)
	{
		std::cerr << ex.what() << '\n';
		return result;
	}
}

MarkerEntity Parser::parseMarkerEntity(std::string_view codeBlock)
{
	MarkerEntity result{};

	std::tie(result.getDataTypeRef(), result.getIdRef(), result.getAtlOffsetRef()) = parseBaseFields(codeBlock);

	result.setPosition(parseArrayFieldOrDefault<double>(codeBlock, "position[]").value());
	result.setName(parseStringField(codeBlock, "name").value());
	result.setText(parseStringField(codeBlock, "text"));
	result.setType(parseStringField(codeBlock, "type").value());
	result.setColorName(parseStringField(codeBlock, "colorName"));
	result.setA(parseDoubleField(codeBlock, "a"));
	result.setB(parseDoubleField(codeBlock, "b"));
	result.setAngle(parseDoubleField(codeBlock, "angle"));

	return result;
}

TriggerEntity Parser::parseTriggerEntity(std::string_view codeBlock)
{
	TriggerEntity result{};

	try
	{
		std::tie(result.getDataTypeRef(), result.getIdRef(), result.getAtlOffsetRef()) = parseBaseFields(codeBlock);

		result.setPosition(parseArrayFieldOrDefault<double>(codeBlock, "position[]").value());

		result.setAngle(parseDoubleField(codeBlock, "angle"));

		auto attributesCodeBlock{ findClassBlock(codeBlock, "Attributes") };

		result.setAttributes(parseObjectAttributes(attributesCodeBlock));

		result.setType(parseStringField(codeBlock, "type").value());

		return result;
	}
	catch (std::runtime_error &ex)
	{
		std::cerr << ex.what() << '\n';
		return result;
	}
}

EntityVariant Parser::parseEntity(std::string_view codeBlock)
{
	auto entityType{ toEntityType(parseStringField(codeBlock, "dataType").value()) };

	EntityVariant result{};

	switch (entityType)
	{
		case EntityType::Group:
		{
			result = parseGroupEntity(codeBlock);
			break;
		}
		case EntityType::Object:
		{
			result = parseObjectEntity(codeBlock);
			break;
		}
		case EntityType::Logic:
		{
			result = parseLogicEntity(codeBlock);
			break;
		}
		case EntityType::Marker:
		{
			result = parseMarkerEntity(codeBlock);
			break;
		}
		case EntityType::Trigger:
		{
			result = parseTriggerEntity(codeBlock);
			break;
		}
		case EntityType::Unknown:
		{
			break;
		}
	}

	return result;
}

MissionEntities Parser::parseMissionEntities(std::string_view codeBlock)
{
	MissionEntities result{};

	try
	{
		result.items = parseShortField(codeBlock, "items").value();

		for (short i{}; i < result.items; ++i)
		{
			std::string enitityClassName{ "Item" + std::to_string(i) };

			auto entityCodeBlock{ findClassBlock(codeBlock, enitityClassName) };

			EntityVariant entityVariant{ parseEntity(entityCodeBlock) };

			result.missionEntities.push_back(entityVariant);
		}

		return result;
	}
	catch (std::runtime_error &ex)
	{
		std::cerr << ex.what() << '\n';
		return result;
	}
}

Mission Parser::parseMission(std::string_view codeBlock)
{
	Mission result{};

	try
	{
		auto IntelCodeBlock{ findClassBlock(codeBlock, "Intel") };
		auto missionEntitiesCodeBlock{ findClassBlock(codeBlock, "Entities") };

		result.intel = parseIntel(IntelCodeBlock);

		result.missionEntities = parseMissionEntities(missionEntitiesCodeBlock);

		return result;
	}
	catch (std::runtime_error &ex)
	{
		std::cerr << ex.what() << '\n';
		return result;
	}
}

Parser::~Parser() = default;

MissionSQM Parser::parseFromFile(const std::string &filePath)
{
	std::ifstream readFileStream{ filePath };

	if (!readFileStream.is_open())
		throw std::ios_base::failure{ "Error opening file: " + filePath };

	MissionSQM result{};

	try
	{
		std::stringstream buffer;

		buffer << readFileStream.rdbuf();

		std::string fileContent{ buffer.str() };

		auto editorDataCodeBlock{ findClassBlock(fileContent, "EditorData") };
		auto addonsMetaDataCodeBlock{ findClassBlock(fileContent, "AddonsMetaData") };
		auto scenarioDataCodeBlock{ findClassBlock(fileContent, "ScenarioData") };
		auto missionCodeBlock{ findClassBlock(fileContent, "Mission") };
		auto customAttributesCodeBlock{ findClassBlock(fileContent, "CustomAttributes") };

		result.setVersion(parseShortField(fileContent, "version").value());
		result.setEditorData(parseEditorData(editorDataCodeBlock));
		result.setBinarizationWanted(parseBoolField(fileContent, "binarizationWanted").value());
		result.setSourceName(parseStringField(fileContent, "sourceName").value());
		result.setAddons(parseAddons(fileContent).value());
		result.setAddonsMetaData(parseAddonsMetaData(addonsMetaDataCodeBlock));
		result.setRandomSeed(parseLongLongField(fileContent, "randomSeed").value());
		result.setScenarioData(parseScenarioData(scenarioDataCodeBlock));
		result.setCustomAttributes(parseCustomAttributes(customAttributesCodeBlock));
		result.setMission(parseMission(missionCodeBlock));

		readFileStream.close();

		return result;
	}
	catch (std::runtime_error &ex)
	{
		std::cerr << ex.what() << '\n';
		return result;
	}
}

void Parser::writeMissionSQMToFile(MissionSQM &missionSqm, const std::string &copyName, const std::string &filePath)
{
	std::ofstream outputFileStream{ filePath + "\\" + copyName, std::ios::out };

	if (!outputFileStream.is_open())
		throw std::ios_base::failure{ "Error opening file: " + filePath + "\\" + copyName };

	outputFileStream << missionSqm.toString(0);

	outputFileStream.close();
}
