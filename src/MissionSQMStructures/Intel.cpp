#include "MissionSQMStructures/Intel.h"

std::string Intel::toString(int indentLevel) const
{
	std::stringstream outStream;

	auto indStr{ indent(indentLevel) };
	auto declIndStr{ indent(indentLevel - 1) };

	outStream << declIndStr << "class Intel\n";
	outStream << declIndStr << "{\n";
	outStream << indStr << "timeOfChanges=" << timeOfChanges << ";\n";
	outStream << indStr << "startWeather=" << startWeather << ";\n";
	outStream << indStr << "startWind=" << startWind << ";\n";
	outStream << indStr << "startWaves=" << startWaves << ";\n";
	outStream << indStr << "forecastWeather=" << forecastWeather << ";\n";
	outStream << indStr << "forecastWind=" << forecastWind << ";\n";
	outStream << indStr << "forecastWaves=" << forecastWaves << ";\n";
	outStream << indStr << "forecastLightnings=" << forecastLightnings << ";\n";
	outStream << indStr << "wavesForced=" << wavesForced << ";\n";
	outStream << indStr << "windForced=" << windForced << ";\n";
	outStream << indStr << "year=" << year << ";\n";
	outStream << indStr << "month=" << month << ";\n";
	outStream << indStr << "day=" << day << ";\n";
	outStream << indStr << "hour=" << hour << ";\n";
	outStream << indStr << "minute=" << minute << ";\n";
	if (startFogBase.has_value())
		outStream << indStr << "startFogBase=" << *startFogBase << ";\n";
	if (forecastFogBase.has_value())
		outStream << indStr << "forecastFogBase=" << *forecastFogBase << ";\n";
	outStream << indStr << "startFogDecay=" << startFogDecay << ";\n";
	outStream << indStr << "forecastFogDecay=" << forecastFogDecay << ";\n";

	outStream << declIndStr << "};\n";

	return outStream.str();
}
