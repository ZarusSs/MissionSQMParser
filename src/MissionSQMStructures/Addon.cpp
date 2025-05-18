#include "MissionSQMStructures/Addon.h"

std::string Addon::toString(int indentLevel, short addonIndex) const
{
	std::stringstream outStream;

	auto indStr{ indent(indentLevel) };
	auto declIndStr{ indent(indentLevel - 1) };

	outStream << declIndStr << "class Item" << std::to_string(addonIndex) << "\n";
	outStream << declIndStr << "{\n";
	outStream << indStr << "className=" << quoteStr(className) << ";\n";
	outStream << indStr << "name=" << quoteStr(name) << ";\n";
	if (author.has_value())
		outStream << indStr << "author=" << quoteStr(*author) << ";\n";
	if (url.has_value())
		outStream << indStr << "url=" << quoteStr(*url) << ";\n";
	outStream << declIndStr << "};\n";

	return outStream.str();
}
