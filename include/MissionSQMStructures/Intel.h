#pragma once

#include "stringUtils/stringFuncs.h"

#include <sstream>
#include <optional>

struct Intel
{
	double timeOfChanges;

	double startWeather;
	double startWind;
	double startWaves;

	double forecastWeather;
	double forecastWind;
	double forecastWaves;
	double forecastLightnings;

	int wavesForced;
	int windForced;

	short year;
	short month;
	short day;
	short hour;
	short minute;

	std::optional<double> startFogBase;
	std::optional<double> forecastFogBase;
	double startFogDecay;
	double forecastFogDecay;

	[[nodiscard]] std::string toString(int indentLevel) const;
};