#pragma once

#include "Camera.h"
#include "stringUtils/stringFuncs.h"

#include <sstream>
#include <optional>

struct EditorData
{
	short moveGridStep;
	double angleGridStep;
	short scaleGridStep;
	short autoGroupingDist;
	short toggles;
	std::optional<int> nextItemIDProvider;
	std::optional<int> nextMarkerIDProvider;
	Camera camera;

	[[nodiscard]] std::string toStringItemProvider(int indentLevel) const;

	[[nodiscard]] std::string toStringMarkerProvider(int indentLevel) const;

	[[nodiscard]] std::string toString(int indentLevel) const;
};