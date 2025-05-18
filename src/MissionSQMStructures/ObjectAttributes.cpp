#include "MissionSQMStructures/ObjectAttributes.h"

std::string Attributes::toString(int indentLevel) const
{
	std::stringstream outStream;

	auto indStr{ indent(indentLevel) };
	auto declIndStr{ indent(indentLevel - 1) };

	outStream << declIndStr << "class Attributes" << '\n';
	outStream << declIndStr << "{\n";
	if (rank.has_value())
		outStream << indStr << "rank=" << quoteStr(*rank) << ";\n";
	if (init.has_value())
		outStream << indStr << "init=" << quoteStr(*init) << ";\n";
	if (name.has_value())
		outStream << indStr << "name=" << quoteStr(*name) << ";\n";
	if (description.has_value())
		outStream << indStr << "description=" << quoteStr(*description) << ";\n";
	if (isPlayable.has_value())
		outStream << indStr << "isPlayable" << *isPlayable << ";\n";

	outStream << declIndStr << "};\n";

	return outStream.str();
}
