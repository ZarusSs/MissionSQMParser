#include "MissionSQMStructures/EditorData.h"

std::string EditorData::toStringItemProvider(int indentLevel) const
{
	std::stringstream outStream;

	auto indStr{ indent(indentLevel) };
	auto declIndStr{ indent(indentLevel - 1) };

	outStream << declIndStr << "class ItemIDProvider\n";
	outStream << declIndStr << "{\n";
	outStream << indStr << "nextID=" << *nextItemIDProvider << ";\n";
	outStream << declIndStr << "};\n";

	return outStream.str();
}

std::string EditorData::toStringMarkerProvider(int indentLevel) const
{
	std::stringstream outStream;

	auto indStr{ indent(indentLevel) };
	auto declIndStr{ indent(indentLevel - 1) };

	outStream << declIndStr << "class MarkerIDProvider\n";
	outStream << declIndStr << "{\n";
	outStream << indStr << "nextID=" << *nextMarkerIDProvider << ";\n";
	outStream << declIndStr << "};\n";

	return outStream.str();
}

std::string EditorData::toString(int indentLevel) const
{
	std::stringstream outStream;

	auto indStr{ indent(indentLevel) };

	outStream << "class EditorData\n{\n";
	outStream << indStr << "moveGridStep=" << moveGridStep << ";\n";
	outStream << indStr << "angleGridStep=" << angleGridStep << ";\n";
	outStream << indStr << "scaleGridStep=" << scaleGridStep << ";\n";
	outStream << indStr << "autoGroupingDist=" << autoGroupingDist << ";\n";
	outStream << indStr << "toggles=" << toggles << ";\n";
	if (nextItemIDProvider.has_value())
		outStream << toStringItemProvider(indentLevel + 1);
	if (nextMarkerIDProvider.has_value())
		outStream << toStringMarkerProvider(indentLevel + 1);
	outStream << camera.toString(indentLevel + 1);
	outStream << "};\n";

	return outStream.str();
}

